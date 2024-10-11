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
__attribute__((aligned(32))) struct ID_MAP {
	// For `newuidmap` and `newgidmap`.
	uid_t uid;
	uid_t uid_lower;
	uid_t uid_count;
	gid_t gid;
	gid_t gid_lower;
	gid_t gid_count;
};
static void get_uid_map(char *user, struct ID_MAP *id_map)
{
	// Get uid_map.
	id_map->uid_lower = 0;
	id_map->uid_count = 0;
	// /etc/subuid format:
	//   foo:uid_lower:uid_count
	//   bar:uid_lower:uid_count
	int fd = open("/etc/subuid", O_RDONLY | O_CLOEXEC);
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = malloc(size + 1);
	read(fd, buf, size);
	close(fd);
	// Find username in /etc/subuid.
	char *map = strstr(buf, user);
	if (map == NULL) {
		// If username is not in /etc/subuid.
		id_map->uid_lower = -1;
		id_map->uid_count = -1;
		return;
	}
	// Get uid_lower and uid_count.
	for (int i = 0;; i++) {
		if (map[i] == ':') {
			for (int j = i + 1;; j++) {
				if (map[j] == ':') {
					for (int k = j + 1;; k++) {
						if (map[k] == '\n') {
							break;
						}
						// Minus '0' to convert char to number.
						id_map->uid_count = (id_map->uid_count) * 10 + map[k] - '0';
					}
					break;
				}
				id_map->uid_lower = (id_map->uid_lower) * 10 + map[j] - '0';
			}
			break;
		}
	}
	free(buf);
}
static void get_gid_map(char *user, struct ID_MAP *id_map)
{
	// Get gid_map.
	id_map->gid_lower = 0;
	id_map->gid_count = 0;
	int fd = open("/etc/subgid", O_RDONLY | O_CLOEXEC);
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = malloc(size + 1);
	read(fd, buf, size);
	close(fd);
	char *map = strstr(buf, user);
	if (map == NULL) {
		id_map->gid_lower = -1;
		id_map->gid_count = -1;
		return;
	}
	for (int i = 0;; i++) {
		if (map[i] == ':') {
			for (int j = i + 1;; j++) {
				if (map[j] == ':') {
					for (int k = j + 1;; k++) {
						if (map[k] == '\n') {
							break;
						}
						id_map->gid_count = (id_map->gid_count) * 10 + map[k] - '0';
					}
					break;
				}
				id_map->gid_lower = (id_map->gid_lower) * 10 + map[j] - '0';
			}
			break;
		}
	}
	free(buf);
}
static struct ID_MAP get_idmap(void)
{
	// Get uid_map and gid_map.
	// This function will return a ID_MAP struct for `newuidmap` and `newgidmap`.
	struct ID_MAP ret;
	ret.uid = getuid();
	ret.gid = getgid();
	struct passwd *pw = getpwuid(getuid());
	get_uid_map(pw->pw_name, &ret);
	get_gid_map(pw->pw_name, &ret);
	return ret;
}
static int try_execvp(char *argv[])
{
	// fork(2) and execvp(3).
	int pid = fork();
	if (pid == 0) {
		execvp(argv[0], argv);
		// If execvp(3) failed, exit as error status 114.
		exit(114);
	}
	int status = 0;
	waitpid(pid, &status, 0);
	return WEXITSTATUS(status);
}
static int try_setup_idmap(pid_t ppid)
{
	// Try to use `uidmap` suid binary to setup uid and gid map.
	struct ID_MAP id_map = get_idmap();
	// Failed to get /etc/subuid or /etc/subgid config for current user.
	if (id_map.gid_lower < 0 || id_map.uid_lower < 0) {
		return -1;
	}
	char pid[128] = { '\0' };
	char uid[128] = { '\0' };
	char uid_lower[128] = { '\0' };
	char uid_count[128] = { '\0' };
	char gid[128] = { '\0' };
	char gid_lower[128] = { '\0' };
	char gid_count[128] = { '\0' };
	sprintf(pid, "%d", ppid);
	sprintf(uid, "%d", id_map.uid);
	sprintf(uid_lower, "%d", id_map.uid_lower);
	sprintf(uid_count, "%d", id_map.uid_count);
	sprintf(gid, "%d", id_map.gid);
	sprintf(gid_lower, "%d", id_map.gid_lower);
	sprintf(gid_count, "%d", id_map.gid_count);
	char *newuidmap[] = { "newuidmap", pid, "0", uid, "1", "1", uid_lower, uid_count, NULL };
	if (try_execvp(newuidmap) != 0) {
		return -1;
	}
	char *newgidmap[] = { "newgidmap", pid, "0", gid, "1", "1", gid_lower, gid_count, NULL };
	if (try_execvp(newgidmap) != 0) {
		return -1;
	}
	return 0;
}
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
	// For rootless container, the way to create/mount runtime dir/files is different.
	chdir(container->container_dir);
	mkdir("./sys", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("/sys", "./sys", NULL, MS_BIND | MS_REC, NULL);
	mkdir("./proc", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("proc", "./proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
	mkdir("./dev", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("tmpfs", "./dev", "tmpfs", MS_NOSUID, "size=65536k,mode=755");
	close(open("./dev/tty", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
	mount("/dev/tty", "./dev/tty", NULL, MS_BIND, NULL);
	close(open("./dev/console", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
	mount("/dev/console", "./dev/console", NULL, MS_BIND, NULL);
	close(open("./dev/null", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
	mount("/dev/null", "./dev/null", NULL, MS_BIND, NULL);
	close(open("./dev/ptmx", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
	mount("/dev/ptmx", "./dev/ptmx", NULL, MS_BIND, NULL);
	close(open("./dev/random", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
	mount("/dev/random", "./dev/random", NULL, MS_BIND, NULL);
	close(open("./dev/urandom", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
	mount("/dev/urandom", "./dev/urandom", NULL, MS_BIND, NULL);
	close(open("./dev/zero", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP));
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
static void set_id_map(uid_t uid, gid_t gid)
{
	/*
	 * If try_setup_idmap() failed, this function will be called,
	 * to setup the uid and gid map.
	 * NOTE: command like `su` or `apt` will run failed if uid and gid map
	 * is not configured by `uidmap` suid binary.
	 */
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
}
void run_rootless_container(struct CONTAINER *container)
{
	uid_t uid = geteuid();
	gid_t gid = getegid();
	bool set_id_map_succeed = false;
	pid_t ppid = getpid();
	// We fork() a new child process, and then,
	// parent process will call unshare(2) to be the owner of a new user ns,
	// then, we can use the child process to call `newuidmap` and `newgidmap`,
	// to change the parent process's id map.
	pid_t pid_1 = fork();
	if (pid_1 > 0) {
		// Enable user namespace.
		try_unshare(CLONE_NEWUSER);
		int stat;
		waitpid(pid_1, &stat, 0);
		if (WEXITSTATUS(stat) == 0) {
			set_id_map_succeed = true;
		}
	} else {
		// To ensure that unshare(2) finished in parent process.
		usleep(1000);
		int stat = try_setup_idmap(ppid);
		exit(stat);
	}
	// We need to own mount namespace.
	try_unshare(CLONE_NEWNS);
	// Seems we need to own a new pid namespace for mount procfs.
	try_unshare(CLONE_NEWPID);
	pid_t pid = fork();
	if (pid > 0) {
		if (!set_id_map_succeed) {
			warning("\033[33mCheck if uidmap is installed on your host, command like su will run failed without uidmap.\n");
			set_id_map(uid, gid);
		}
		int stat = 0;
		waitpid(pid, &stat, 0);
		exit(stat);
	} else if (pid < 0) {
		error("{red}Fork error QwQ?\n");
	} else {
		// Init rootless container.
		init_rootless_container(container);
		run_rootless_chroot_container(container);
	}
}
