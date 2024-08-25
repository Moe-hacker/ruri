// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2024 Moe-hacker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 */
#include "include/ruri.h"
// For run_unshare_container().
static pid_t init_unshare_container(struct CONTAINER *container)
{
	/*
	 * Use unshare(2) to create new namespaces and fork(2) to join them.
	 * Return pid of forked process.
	 * unshare_pid in forked process is 0.
	 */
	pid_t unshare_pid = INIT_VALUE;
	// Create namespaces.
	if (unshare(CLONE_NEWNS) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that mount namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_NEWUTS) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that uts namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_NEWIPC) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that ipc namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_NEWPID) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that pid namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_NEWCGROUP) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that cgroup namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_NEWTIME) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that time namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_SYSVSEM) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that semaphore namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_FILES) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that we could not unshare file descriptors with child process QwQ{clear}\n");
	}
	if (unshare(CLONE_NEWUSER) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that user namespace is not supported on this device QwQ{clear}\n");
	}
	if (unshare(CLONE_FS) == -1 && !container->no_warnings) {
		warning("{yellow}Warning: seems that we could not unshare filesystem information with child process QwQ{clear}\n");
	}
	// Add uid and gid map, or it will be nobody(65534) by default.
	// Copied from `src/rootless.c`, removed geteuid() & getegid()
	uid_t uid = 0;
	gid_t gid = 0;
	// Set uid map.
	char uid_map[32] = { "\0" };
	sprintf(uid_map, "0 %d 1\n", uid);
	int uidmap_fd = open("/proc/self/uid_map", O_RDWR | O_CLOEXEC);
	write(uidmap_fd, uid_map, strlen(uid_map));
	close(uidmap_fd);
	// Set gid map.
	int setgroups_fd = open("/proc/self/setgroups", O_RDWR | O_CLOEXEC);
	write(setgroups_fd, "deny", 5);
	close(setgroups_fd);
	char gid_map[32] = { "\0" };
	sprintf(gid_map, "0 %d 1\n", gid);
	int gidmap_fd = open("/proc/self/gid_map", O_RDWR | O_CLOEXEC);
	write(gidmap_fd, gid_map, strlen(gid_map));
	close(gidmap_fd);
	// Maybe needless.
	setuid(0);
	setgid(0);
	setgroups_fd = open("/proc/self/setgroups", O_RDWR | O_CLOEXEC);
	write(setgroups_fd, "allow", 5);
	close(setgroups_fd);
	// Fork itself into namespace.
	// This can fix `can't fork: out of memory` issue.
	unshare_pid = fork();
	if (unshare_pid > 0) {
		// Store container info.
		if (container->use_rurienv) {
			container->ns_pid = getpid();
			store_info(container);
		}
		// Fix `can't access tty` issue.
		int stat = 0;
		waitpid(unshare_pid, &stat, 0);
		exit(stat);
	} else if (unshare_pid < 0) {
		error("{red}Fork error, QwQ?\n");
	}
	return unshare_pid;
}
// For run_unshare_container().
static pid_t join_ns(struct CONTAINER *container)
{
	pid_t unshare_pid = INIT_VALUE;
	// Use setns(2) to enter existing namespaces.
	char cgroup_ns_file[PATH_MAX] = { '\0' };
	char ipc_ns_file[PATH_MAX] = { '\0' };
	char mount_ns_file[PATH_MAX] = { '\0' };
	char user_ns_file[PATH_MAX] = { '\0' };
	char pid_ns_file[PATH_MAX] = { '\0' };
	char time_ns_file[PATH_MAX] = { '\0' };
	char uts_ns_file[PATH_MAX] = { '\0' };
	sprintf(cgroup_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/cgroup");
	sprintf(ipc_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/ipc");
	sprintf(mount_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/mnt");
	sprintf(pid_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/pid");
	sprintf(time_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/time");
	sprintf(user_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/user");
	sprintf(uts_ns_file, "%s%d%s", "/proc/", container->ns_pid, "/ns/uts");
	// Enter namespaces via setns(2).
	int ns_fd = INIT_VALUE;
	ns_fd = open(mount_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that mount namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	ns_fd = open(pid_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that pid namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	ns_fd = open(time_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that time namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	ns_fd = open(uts_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that uts namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	ns_fd = open(user_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that user namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	ns_fd = open(cgroup_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that cgroup namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	ns_fd = open(ipc_ns_file, O_RDONLY | O_CLOEXEC);
	if (ns_fd < 0 && !container->no_warnings) {
		warning("{yellow}Warning: seems that ipc namespace is not supported on this device QwQ{clear}\n");
	} else {
		setns(ns_fd, 0);
		close(ns_fd);
	}
	// Close fds after fork().
	unshare(CLONE_FILES);
	// Fork itself into namespace.
	// This can fix `can't fork: out of memory` issue.
	unshare_pid = fork();
	// Fix `can't access tty` issue.
	if (unshare_pid > 0) {
		// Wait until current process exit.
		int stat = 0;
		waitpid(unshare_pid, &stat, 0);
		exit(stat);
	}
	// Maybe this will never be run.
	else if (unshare_pid < 0) {
		error("{red}Fork error, QwQ?\n");
		return 1;
	}
	return unshare_pid;
}
// Run unshare container.
void run_unshare_container(struct CONTAINER *container)
{
	pid_t unshare_pid = INIT_VALUE;
	// unshare(2) itself into new namespaces.
	if (container->use_rurienv) {
		read_info(container, container->container_dir);
	}
	if (container->ns_pid < 0) {
		unshare_pid = init_unshare_container(container);
	} else {
		unshare_pid = join_ns(container);
	}
	// Check if we have joined the container's namespaces.
	if (unshare_pid == 0) {
		run_chroot_container(container);
	}
}
