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
static void try_unshare(int flags)
{
	/*
	 * Try to use unshare(2).
	 */
	if (unshare(flags) == -1) {
		error("{red}Your device does not support some namespaces needed!\n");
	}
}
static void init_rootless_container(struct CONTAINER *container)
{
	chdir(container->container_dir);
	mkdir("./sys", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/sys", "./sys", NULL, MS_BIND | MS_REC, NULL);
	mkdir("./proc", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("proc", "./proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
	mkdir("./dev", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("tmpfs", "./dev", "tmpfs", MS_NOSUID, "size=65536k,mode=755");
	open("./dev/tty", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/tty", "./dev/tty", NULL, MS_BIND, NULL);
	open("./dev/console", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/console", "./dev/console", NULL, MS_BIND, NULL);
	open("./dev/null", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/null", "./dev/null", NULL, MS_BIND, NULL);
	open("./dev/ptmx", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/ptmx", "./dev/ptmx", NULL, MS_BIND, NULL);
	open("./dev/random", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/random", "./dev/random", NULL, MS_BIND, NULL);
	open("./dev/urandom", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/urandom", "./dev/urandom", NULL, MS_BIND, NULL);
	open("./dev/zero", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/dev/zero", "./dev/zero", NULL, MS_BIND, NULL);
	symlink("/proc/self/fd", "./dev/fd");
	symlink("/proc/self/fd/0", "./dev/stdin");
	symlink("/proc/self/fd/1", "./dev/stdout");
	symlink("/proc/self/fd/2", "./dev/stderr");
	symlink("/dev/null", "./dev/tty0");
	mkdir("./dev/pts", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("devpts", "./dev/pts", "devpts", 0, "gid=4,mode=620");
	mkdir("./dev/shm", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("tmpfs", "./dev/shm", "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, "mode=1777");
	mount("./proc/bus", "./proc/bus", NULL, MS_BIND | MS_REC, NULL);
	mount("./proc/bus", "./proc/bus", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
	mount("./proc/fs", "./proc/fs", NULL, MS_BIND | MS_REC, NULL);
	mount("./proc/fs", "./proc/fs", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
	mount("./proc/irq", "./proc/irq", NULL, MS_BIND | MS_REC, NULL);
	mount("./proc/irq", "./proc/irq", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
	mount("./proc/sys", "./proc/sys", NULL, MS_BIND | MS_REC, NULL);
	mount("./proc/sys", "./proc/sys", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
	mount("./proc/sys-trigger", "./proc/sys-trigger", NULL, MS_BIND | MS_REC, NULL);
	mount("./proc/sys-trigger", "./proc/sys-trigger", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
	mount("tmpfs", "./proc/asound", "tmpfs", MS_RDONLY, NULL);
	mount("tmpfs", "./proc/acpi", "tmpfs", MS_RDONLY, NULL);
	mount("/dev/null", "./proc/kcore", "", MS_BIND, NULL);
	mount("/dev/null", "./proc/keys", "", MS_BIND, NULL);
	mount("/dev/null", "./proc/latency_stats", "", MS_BIND, NULL);
	mount("/dev/null", "./proc/timer_list", "", MS_BIND, NULL);
	mount("/dev/null", "./proc/timer_stats", "", MS_BIND, NULL);
	mount("/dev/null", "./proc/sched_debug", "", MS_BIND, NULL);
	mount("tmpfs", "./proc/scsi", "tmpfs", MS_RDONLY, NULL);
	mount("tmpfs", "./sys/firmware", "tmpfs", MS_RDONLY, NULL);
	mount("tmpfs", "./sys/devices/virtual/powercap", "tmpfs", MS_RDONLY, NULL);
	mount("tmpfs", "./sys/block", "tmpfs", MS_RDONLY, NULL);
}
void run_rootless_container(struct CONTAINER *container)
{
	uid_t uid = geteuid();
	gid_t gid = getegid();
	// Enable user namespace.
	try_unshare(CLONE_NEWUSER);
	// We need to own mount namespace.
	try_unshare(CLONE_NEWNS);
	// Seems procfs need pid namespace.
	try_unshare(CLONE_NEWPID);
	pid_t pid = fork();
	if (pid > 0) {
		int stat = 0;
		waitpid(pid, &stat, 0);
		exit(stat);
	} else if (pid < 0) {
		error("{red}Fork error QwQ?\n");
	} else {
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
		// Init rootless container.
		init_rootless_container(container);
		run_rootless_chroot_container(container);
	}
}
