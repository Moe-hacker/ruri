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
// Check if the running pid is ruri.
static bool is_ruri_pid(pid_t pid)
{
	/*
	 * /proc/pid/stat example:
	 * 24320 (bash) S 24317 24320 7406 34816 24392 4194560 365 262 0 0 0 0 0 0 10 -10 1 0 13729015 4689920 920 18446744073709551615 389493096448 389494178872 549307347392 0 0 0 3211264 3686404 1266761467 1 0 0 17 1 0 0 0 0 0 389494244512 389494276064 390520700928 549307350901 549307350907 549307350907 549307351022 0
	 * So we just get the process name wrapped by `()`,
	 * and check if it is `ruri`.
	 */
	char stat_path[PATH_MAX] = { '\0' };
	sprintf(stat_path, "/proc/%d/stat", pid);
	int fd = open(stat_path, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		return false;
	}
	char buf[4096] = { '\0' };
	char name[1024] = { '\0' };
	read(fd, buf, sizeof(buf));
	close(fd);
	// Get the process name wrapped by `()`.
	for (int i = 0; true; i++) {
		if (buf[i] == '(') {
			for (int j = 1; true; j++) {
				if (buf[i + j] == ')') {
					break;
				}
				name[j - 1] = buf[i + j];
				name[j] = '\0';
			}
			break;
		}
	}
	if (strcmp(name, "ruri") == 0) {
		return true;
	}
	return false;
}
// Format container info as k2v.
static char *build_container_info(const struct CONTAINER *container)
{
	/*
	 * Format container runtime info to k2v format,
	 * and return the formatted config.
	 */
	char *ret = NULL;
	// drop_caplist.
	char *drop_caplist[CAP_LAST_CAP + 1] = { NULL };
	int len = 0;
	for (int i = 0; true; i++) {
		if (container->drop_caplist[i] == INIT_VALUE) {
			len = i;
			break;
		}
		drop_caplist[i] = cap_to_name(container->drop_caplist[i]);
	}
	ret = k2v_add_comment(ret, "The capabilty to drop.");
	ret = k2v_add_config(char_array, ret, "drop_caplist", drop_caplist, len);
	// no_new_privs.
	ret = k2v_add_comment(ret, "Set NO_NEW_PRIVS bit.");
	ret = k2v_add_config(bool, ret, "no_new_privs", container->no_new_privs);
	// enable_seccomp.
	ret = k2v_add_comment(ret, "Enable built-in seccomp profile.");
	ret = k2v_add_config(bool, ret, "enable_seccomp", container->enable_seccomp);
	// ns_pid.
	ret = k2v_add_comment(ret, "PID owning unshare namespace.");
	ret = k2v_add_config(int, ret, "ns_pid", container->ns_pid);
	// container_id.
	ret = k2v_add_comment(ret, "Container ID.");
	ret = k2v_add_config(int, ret, "container_id", container->container_id);
	// extra_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Extra mountpoint.");
	ret = k2v_add_config(char_array, ret, "extra_mountpoint", container->extra_mountpoint, len);
	// extra_ro_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_ro_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Extra read-only mountpoint.");
	ret = k2v_add_config(char_array, ret, "extra_ro_mountpoint", container->extra_ro_mountpoint, len);
	// env.
	for (int i = 0; true; i++) {
		if (container->env[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Environment variable.");
	ret = k2v_add_config(char_array, ret, "env", container->env, len);
	log("{base}Container config in /.rurienv:{cyan}\n%s", ret);
	return ret;
}
// Store container info.
void store_info(const struct CONTAINER *container)
{
	/*
	 * Format the runtime info of container to k2v format.
	 * And store the info to container_dir/.rurienv .
	 *
	 * How to avoid security issue?
	 *
	 * The .rurienv file is set to be immutable, but the container
	 * will not have cap_linux_immutable by default,
	 * that means the file will always be read-only
	 * into the container. So even if ruri have memory overflow bugs,
	 * it can not be exploited by modifying the .rurienv file.
	 */
	// Format container info.
	char *info = build_container_info(container);
	char file[PATH_MAX] = { '\0' };
	sprintf(file, "%s/.rurienv", container->container_dir);
	int fd = open(file, O_RDONLY | O_CLOEXEC);
	// We know that it's not recommended to use bitwise operator on signed int.
	// But I found this code in man-doc:
	//
	//       int attr;
	//       fd = open("pathname", ...);
	//
	//       ioctl(fd, FS_IOC_GETFLAGS, &attr);  /* Place current flags
	//                                              in 'attr' */
	//       attr |= FS_NOATIME_FL;              /* Tweak returned bit mask */
	//       ioctl(fd, FS_IOC_SETFLAGS, &attr);  /* Update flags for inode
	//                                              referred to by 'fd' */
	// And FS_IMMUTABLE_FL (0x00000010) is also (int) by default.
	// So I leave the `attr` to int.
	int attr = 0;
	if (fd >= 0) {
		// Unset the immutable flag so that we can remove the file.
		ioctl(fd, FS_IOC_GETFLAGS, &attr);
		attr &= ~FS_IMMUTABLE_FL;
		ioctl(fd, FS_IOC_SETFLAGS, &attr);
		remove(file);
		close(fd);
	}
	// Creat .rurienv file and open it.
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IWUSR | S_IRUSR);
	// Write info to .rurienv file.
	write(fd, info, strlen(info));
	// Set immutable flag on .rurienv file.
	attr = 0;
	ioctl(fd, FS_IOC_GETFLAGS, &attr);
	attr |= FS_IMMUTABLE_FL;
	ioctl(fd, FS_IOC_SETFLAGS, &attr);
	close(fd);
	free(info);
}
// Read .rurienv file.
struct CONTAINER *read_info(struct CONTAINER *container, const char *container_dir)
{
	/*
	 * Get runtime info of container.
	 * And return the container struct back.
	 * For umount_container(), it will accept a NULL struct,
	 * and return a struct with malloced memory.
	 */
	char file[PATH_MAX] = { '\0' };
	sprintf(file, "%s/.rurienv", container_dir);
	int fd = open(file, O_RDONLY | O_CLOEXEC);
	// If .rurienv file does not exist, just return.
	if (fd < 0) {
		return container;
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	close(fd);
	// Read .rurienv file.
	char *buf = k2v_open_file(file, (size_t)size);
	log("{base}Container config in /.rurienv:{cyan}\n%s", buf);
	// Only umount_container() will give a NULL struct.
	if (container == NULL) {
		container = (struct CONTAINER *)malloc(sizeof(struct CONTAINER));
		int mlen = k2v_get_key(char_array, "extra_mountpoint", buf, container->extra_mountpoint);
		container->extra_mountpoint[mlen] = NULL;
		container->extra_mountpoint[mlen + 1] = NULL;
		mlen = k2v_get_key(char_array, "extra_ro_mountpoint", buf, container->extra_ro_mountpoint);
		container->extra_ro_mountpoint[mlen] = NULL;
		container->extra_ro_mountpoint[mlen + 1] = NULL;
		close(fd);
		free(buf);
		return container;
	}
	// Unset cgroup limits because it's already set.
	container->cpuset = NULL;
	container->memory = NULL;
	// Check if ns_pid is a ruri process.
	// If not, that means the container is not running.
	if (container->enable_unshare && !is_ruri_pid(k2v_get_key(int, "ns_pid", buf))) {
		// Unset immutable flag of .rurienv.
		fd = open(file, O_RDONLY | O_CLOEXEC);
		int attr = 0;
		ioctl(fd, FS_IOC_GETFLAGS, &attr);
		attr &= ~FS_IMMUTABLE_FL;
		ioctl(fd, FS_IOC_SETFLAGS, &attr);
		remove(file);
		close(fd);
		remove(file);
		return container;
	}
	// Get capabilities to drop.
	char *drop_caplist[CAP_LAST_CAP + 1] = { NULL };
	int caplen = k2v_get_key(char_array, "drop_caplist", buf, drop_caplist);
	drop_caplist[caplen] = NULL;
	for (int i = 0; true; i++) {
		if (drop_caplist[i] == NULL) {
			container->drop_caplist[i] = INIT_VALUE;
			break;
		}
		cap_from_name(drop_caplist[i], &(container->drop_caplist[i]));
		free(drop_caplist[i]);
		container->drop_caplist[i + 1] = INIT_VALUE;
	}
	// Get no_new_privs.
	container->no_new_privs = k2v_get_key(bool, "no_new_privs", buf);
	// Get enable_seccomp.
	container->enable_seccomp = k2v_get_key(bool, "enable_seccomp", buf);
	// Get ns_pid.
	container->ns_pid = k2v_get_key(int, "ns_pid", buf);
	// Get container_id.
	container->container_id = k2v_get_key(int, "container_id", buf);
	// Get env.
	int envlen = k2v_get_key(char_array, "env", buf, container->env);
	container->env[envlen] = NULL;
	container->env[envlen + 1] = NULL;
	// Get extra_mountpoint.
	int mlen = k2v_get_key(char_array, "extra_mountpoint", buf, container->extra_mountpoint);
	container->extra_mountpoint[mlen] = NULL;
	container->extra_mountpoint[mlen + 1] = NULL;
	// Get extra_ro_mountpoint.
	mlen = k2v_get_key(char_array, "extra_ro_mountpoint", buf, container->extra_ro_mountpoint);
	container->extra_ro_mountpoint[mlen] = NULL;
	container->extra_ro_mountpoint[mlen + 1] = NULL;
	return container;
}
