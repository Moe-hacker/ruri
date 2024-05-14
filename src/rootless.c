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
static void init_rootless_container(void){

}
void run_rootless_container(struct CONTAINER *container)
{
	uid_t uid = geteuid();
	gid_t gid = getegid();
	/*
	 * Seems mount(2) for sysfs and procfs need all unshare option enabled.
	 */
	try_unshare(CLONE_NEWUSER);
	try_unshare(CLONE_NEWNS);
	try_unshare(CLONE_NEWPID);
	try_unshare(CLONE_NEWIPC);
	try_unshare(CLONE_NEWUTS);
	try_unshare(CLONE_NEWNET);
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
		run_chroot_container(container);
	}
}
