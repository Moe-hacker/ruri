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
char *container_info_to_k2v(const struct CONTAINER *_Nonnull container)
{
	/*
	 * Format container info to k2v format.
	 * return the config as string.
	 */
	char *ret = NULL;
	// drop_caplist.
	char *drop_caplist[CAP_LAST_CAP + 1] = { NULL };
	char *cap_tmp = NULL;
	int len = 0;
	for (int i = 0; true; i++) {
		if (container->drop_caplist[i] == INIT_VALUE) {
			len = i;
			break;
		}
		cap_tmp = cap_to_name(container->drop_caplist[i]);
		if (cap_tmp == NULL) {
			drop_caplist[i] = malloc(114);
			sprintf(drop_caplist[i], "%d", container->drop_caplist[i]);
		} else {
			drop_caplist[i] = strdup(cap_tmp);
			cap_free(cap_tmp);
			cap_tmp = NULL;
		}
	}
	ret = k2v_add_comment(ret, "The capability to drop.");
	ret = k2v_add_config(char_array, ret, "drop_caplist", drop_caplist, len);
	// Make ASAN happy.
	for (int i = 0; i < len; i++) {
		free(drop_caplist[i]);
	}
	// no_new_privs.
	ret = k2v_add_comment(ret, "Set NO_NEW_PRIVS bit.");
	ret = k2v_add_config(bool, ret, "no_new_privs", container->no_new_privs);
	// enable_unshare.
	ret = k2v_add_comment(ret, "Enable unshare feature.");
	ret = k2v_add_config(bool, ret, "enable_unshare", container->enable_unshare);
	// rootless.
	ret = k2v_add_comment(ret, "Run rootless container.");
	ret = k2v_add_config(bool, ret, "rootless", container->rootless);
	// mount_host_runtime.
	ret = k2v_add_comment(ret, "Mount runtime dirs from the host.");
	ret = k2v_add_config(bool, ret, "mount_host_runtime", container->mount_host_runtime);
	// ro_root.
	ret = k2v_add_comment(ret, "Make / read-only.");
	ret = k2v_add_config(bool, ret, "ro_root", container->ro_root);
	// no_warnings.
	ret = k2v_add_comment(ret, "Disable warnings.");
	ret = k2v_add_config(bool, ret, "no_warnings", container->no_warnings);
	// cross_arch.
	ret = k2v_add_comment(ret, "The arch for running cross-arch container.");
	ret = k2v_add_config(char, ret, "cross_arch", container->cross_arch);
	// qemu_path.
	ret = k2v_add_comment(ret, "The path of qemu-user static binary.");
	ret = k2v_add_config(char, ret, "qemu_path", container->qemu_path);
	// use_rurienv.
	ret = k2v_add_comment(ret, "If enable using .rurienv file.");
	ret = k2v_add_config(bool, ret, "use_rurienv", container->use_rurienv);
	// enable_seccomp.
	ret = k2v_add_comment(ret, "Enable built-in seccomp profile.");
	ret = k2v_add_config(bool, ret, "enable_seccomp", container->enable_seccomp);
	// cpuset.
	ret = k2v_add_comment(ret, "Cgroup cpuset limit.");
	ret = k2v_add_config(char, ret, "cpuset", container->cpuset);
	// memory.
	ret = k2v_add_comment(ret, "Cgroup memory limit.");
	ret = k2v_add_config(char, ret, "memory", container->memory);
	// just_chroot.
	ret = k2v_add_comment(ret, "Just chroot, do not create runtime dirs.");
	ret = k2v_add_config(bool, ret, "just_chroot", container->just_chroot);
	// work_dir.
	ret = k2v_add_comment(ret, "Work directory.");
	ret = k2v_add_config(char, ret, "work_dir", container->work_dir);
	// rootfs_source.
	ret = k2v_add_comment(ret, "Rootfs source, will be mount to / as first mountpoint.");
	ret = k2v_add_config(char, ret, "rootfs_source", container->rootfs_source);
	// unmask_dirs.
	ret = k2v_add_comment(ret, "Unmask dirs in /proc and /sys.");
	ret = k2v_add_config(bool, ret, "unmask_dirs", container->unmask_dirs);
	// user.
	ret = k2v_add_comment(ret, "The user to run command in the container.");
	ret = k2v_add_config(char, ret, "user", container->user);
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
	// command.
	for (int i = 0; true; i++) {
		if (container->command[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Default comand to run.");
	ret = k2v_add_config(char_array, ret, "command", container->command, len);
	// container_dir.
	ret = k2v_add_comment(ret, "The CONTAINER_DIR.");
	ret = k2v_add_config(char, ret, "container_dir", container->container_dir);
	return ret;
}
void read_config(struct CONTAINER *_Nonnull container, const char *_Nonnull path)
{
	/*
	 * Read k2v format config file,
	 * and set container config.
	 */
	int fd = open(path, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		error("{red}No such file or directory:%s\n{clear}", path);
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	close(fd);
	char *buf = k2v_open_file(path, (size_t)size);
	// Get drop_caplist.
	char *drop_caplist[CAP_LAST_CAP + 1] = { NULL };
	int caplen = k2v_get_key(char_array, "drop_caplist", buf, drop_caplist, CAP_LAST_CAP);
	drop_caplist[caplen] = NULL;
	for (int i = 0; true; i++) {
		if (drop_caplist[i] == NULL) {
			break;
		}
		if (atoi(drop_caplist[i]) > 0) {
			container->drop_caplist[i] = atoi(drop_caplist[i]);
		} else {
			cap_from_name(drop_caplist[i], &(container->drop_caplist[i]));
		}
		free(drop_caplist[i]);
		container->drop_caplist[i + 1] = INIT_VALUE;
	}
	// Get no_new_privs.
	container->no_new_privs = k2v_get_key(bool, "no_new_privs", buf);
	// Get enable_seccomp.
	container->enable_seccomp = k2v_get_key(bool, "enable_seccomp", buf);
	// Get container_dir.
	container->container_dir = k2v_get_key(char, "container_dir", buf);
	// Get qemu_path.
	container->qemu_path = k2v_get_key(char, "qemu_path", buf);
	// Get cross_arch.
	container->cross_arch = k2v_get_key(char, "cross_arch", buf);
	// Get rootless.
	container->rootless = k2v_get_key(bool, "rootless", buf);
	// Get mount_host_runtime.
	container->mount_host_runtime = k2v_get_key(bool, "mount_host_runtime", buf);
	// Get ro_root.
	container->ro_root = k2v_get_key(bool, "ro_root", buf);
	// Get no_warnings.
	container->no_warnings = k2v_get_key(bool, "no_warnings", buf);
	// Get use_rurienv.
	container->use_rurienv = k2v_get_key(bool, "use_rurienv", buf);
	// Get cpuset.
	container->cpuset = k2v_get_key(char, "cpuset", buf);
	// Get memory.
	container->memory = k2v_get_key(char, "memory", buf);
	// Get just_chroot.
	container->just_chroot = k2v_get_key(bool, "just_chroot", buf);
	// Get work_dir.
	container->work_dir = k2v_get_key(char, "work_dir", buf);
	// Get rootfs_source.
	container->rootfs_source = k2v_get_key(char, "rootfs_source", buf);
	// Get unmask_dirs.
	container->unmask_dirs = k2v_get_key(bool, "unmask_dirs", buf);
	// Get user.
	if (container->user == NULL) {
		container->user = k2v_get_key(char, "user", buf);
	}
	// Get env.
	int envlen = k2v_get_key(char_array, "env", buf, container->env, MAX_ENVS);
	container->env[envlen] = NULL;
	container->env[envlen + 1] = NULL;
	// Get extra_mountpoint.
	int mlen = k2v_get_key(char_array, "extra_mountpoint", buf, container->extra_mountpoint, MAX_MOUNTPOINTS);
	container->extra_mountpoint[mlen] = NULL;
	container->extra_mountpoint[mlen + 1] = NULL;
	// Get extra_ro_mountpoint.
	mlen = k2v_get_key(char_array, "extra_ro_mountpoint", buf, container->extra_ro_mountpoint, MAX_MOUNTPOINTS);
	container->extra_ro_mountpoint[mlen] = NULL;
	container->extra_ro_mountpoint[mlen + 1] = NULL;
	free(buf);
	buf = container_info_to_k2v(container);
	log("{base}Container config in %s:{cyan}\n%s", path, buf);
	free(buf);
}
