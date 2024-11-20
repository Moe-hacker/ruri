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
	// container_dir.
	ret = k2v_add_comment(ret, "The CONTAINER_DIR.");
	ret = k2v_add_comment(ret, "Should be an absolute path on host.");
	ret = k2v_add_comment(ret, "This can not be empty.");
	ret = k2v_add_config(char, ret, "container_dir", container->container_dir);
	ret = k2v_add_newline(ret);
	// user.
	ret = k2v_add_comment(ret, "The user to run command in the container.");
	ret = k2v_add_comment(ret, "Use username or uid is both valid.");
	ret = k2v_add_comment(ret, "Default is root, set it to empty to use default.");
	ret = k2v_add_config(char, ret, "user", container->user);
	ret = k2v_add_newline(ret);
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
	ret = k2v_add_comment(ret, "Format: \"capname1\",\"capname2\".");
	ret = k2v_add_comment(ret, "For example, [\"cap_sys_admin\",\"cap_sys_chroot\"] is valid.");
	ret = k2v_add_config(char_array, ret, "drop_caplist", drop_caplist, len);
	ret = k2v_add_newline(ret);
	// Make ASAN happy.
	for (int i = 0; i < len; i++) {
		free(drop_caplist[i]);
	}
	// no_new_privs.
	ret = k2v_add_comment(ret, "Set NO_NEW_PRIVS bit.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "no_new_privs", container->no_new_privs);
	ret = k2v_add_newline(ret);
	// enable_unshare.
	ret = k2v_add_comment(ret, "Enable unshare feature.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "enable_unshare", container->enable_unshare);
	ret = k2v_add_newline(ret);
	// rootless.
	ret = k2v_add_comment(ret, "Run rootless container.");
	ret = k2v_add_comment(ret, "Need user ns support.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "rootless", container->rootless);
	ret = k2v_add_newline(ret);
	// no_warnings.
	ret = k2v_add_comment(ret, "Disable warnings.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "no_warnings", container->no_warnings);
	ret = k2v_add_newline(ret);
	// cross_arch.
	ret = k2v_add_comment(ret, "The arch for running cross-arch container.");
	ret = k2v_add_comment(ret, "For example, x86_64.");
	ret = k2v_add_comment(ret, "Should also set qemu_path.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char, ret, "cross_arch", container->cross_arch);
	ret = k2v_add_newline(ret);
	// qemu_path.
	ret = k2v_add_comment(ret, "The path of qemu-user static binary.");
	ret = k2v_add_comment(ret, "For example, /usr/bin/qemu-x86_64-static.");
	ret = k2v_add_comment(ret, "Should also set cross_arch.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char, ret, "qemu_path", container->qemu_path);
	ret = k2v_add_newline(ret);
	// use_rurienv.
	ret = k2v_add_comment(ret, "Enable using .rurienv file.");
	ret = k2v_add_comment(ret, "Default is true.");
	ret = k2v_add_config(bool, ret, "use_rurienv", container->use_rurienv);
	ret = k2v_add_newline(ret);
	// enable_seccomp.
	ret = k2v_add_comment(ret, "Enable built-in seccomp profile.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "enable_seccomp", container->enable_seccomp);
	ret = k2v_add_newline(ret);
	// cpuset.
	ret = k2v_add_comment(ret, "Cgroup cpuset limit.");
	ret = k2v_add_comment(ret, "For example, 0-2 or 0 is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char, ret, "cpuset", container->cpuset);
	ret = k2v_add_newline(ret);
	// cpupercent.
	ret = k2v_add_comment(ret, "Cgroup cpu limit.");
	ret = k2v_add_comment(ret, "The value is in percentage, set it <=0 to disable.");
	ret = k2v_add_config(int, ret, "cpupercent", container->cpupercent);
	ret = k2v_add_newline(ret);
	// memory.
	ret = k2v_add_comment(ret, "Cgroup memory limit.");
	ret = k2v_add_comment(ret, "For example, 1G or 1024M is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char, ret, "memory", container->memory);
	ret = k2v_add_newline(ret);
	// just_chroot.
	ret = k2v_add_comment(ret, "Just chroot, do not create runtime dirs.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "just_chroot", container->just_chroot);
	ret = k2v_add_newline(ret);
	// unmask_dirs.
	ret = k2v_add_comment(ret, "Unmask dirs in /proc and /sys.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "unmask_dirs", container->unmask_dirs);
	ret = k2v_add_newline(ret);
	// mount_host_runtime.
	ret = k2v_add_comment(ret, "Mount runtime dirs from the host.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "mount_host_runtime", container->mount_host_runtime);
	ret = k2v_add_newline(ret);
	// work_dir.
	ret = k2v_add_comment(ret, "Work directory.");
	ret = k2v_add_comment(ret, "Should be an absolute path in the container.");
	ret = k2v_add_comment(ret, "Default is / , set it to empty to use default.");
	ret = k2v_add_config(char, ret, "work_dir", container->work_dir);
	ret = k2v_add_newline(ret);
	// rootfs_source.
	ret = k2v_add_comment(ret, "Rootfs source, will be mount to / as first mountpoint.");
	ret = k2v_add_comment(ret, "Should be an absolute path in the host.");
	ret = k2v_add_comment(ret, "/path/to/rootfs.img or /dev/sda1 is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to use container_dir as default.");
	ret = k2v_add_config(char, ret, "rootfs_source", container->rootfs_source);
	ret = k2v_add_newline(ret);
	// ro_root.
	ret = k2v_add_comment(ret, "Make / read-only.");
	ret = k2v_add_comment(ret, "Default is false.");
	ret = k2v_add_config(bool, ret, "ro_root", container->ro_root);
	ret = k2v_add_newline(ret);
	// extra_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Extra mountpoint.");
	ret = k2v_add_comment(ret, "Format: \"source\",\"target\".");
	ret = k2v_add_comment(ret, "For example, [\"/tmp\",\"/tmp\",\"/var\",\"/var\"] is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char_array, ret, "extra_mountpoint", container->extra_mountpoint, len);
	ret = k2v_add_newline(ret);
	// extra_ro_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_ro_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Extra read-only mountpoint.");
	ret = k2v_add_comment(ret, "Format: \"source\",\"target\".");
	ret = k2v_add_comment(ret, "For example, [\"/tmp\",\"/tmp\",\"/var\",\"/var\"] is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char_array, ret, "extra_ro_mountpoint", container->extra_ro_mountpoint, len);
	ret = k2v_add_newline(ret);
	// env.
	for (int i = 0; true; i++) {
		if (container->env[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Environment variable.");
	ret = k2v_add_comment(ret, "Format: \"key\",\"value\".");
	ret = k2v_add_comment(ret, "For example, [\"key1\",\"value1\",\"key2\",\"value2\"] is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to disable.");
	ret = k2v_add_config(char_array, ret, "env", container->env, len);
	ret = k2v_add_newline(ret);
	// command.
	for (int i = 0; true; i++) {
		if (container->command[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_comment(ret, "Default comand to run.");
	ret = k2v_add_comment(ret, "For example, [\"/bin/sh\",\"-c\",\"echo hello\"] is valid.");
	ret = k2v_add_comment(ret, "Set it to empty to use default (/bin/su - or /bin/sh).");
	ret = k2v_add_config(char_array, ret, "command", container->command, len);
	ret = k2v_add_newline(ret);
	// hostname.
	ret = k2v_add_comment(ret, "The hostname of the container.");
	ret = k2v_add_comment(ret, "This is only for unshare container.");
	ret = k2v_add_comment(ret, "Set it to empty to disable it.");
	ret = k2v_add_config(char, ret, "hostname", container->hostname);
	ret = k2v_add_newline(ret);
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
	// Check if config is valid.
	char *key_list[] = { "container_dir", "user", "drop_caplist", "no_new_privs", "enable_seccomp", "rootless", "no_warnings", "cross_arch", "qemu_path", "use_rurienv", "cpuset", "memory", "cpupercent", "just_chroot", "unmask_dirs", "mount_host_runtime", "work_dir", "rootfs_source", "ro_root", "extra_mountpoint", "extra_ro_mountpoint", "env", "command", "hostname", NULL };
	for (int i = 0; key_list[i] != NULL; i++) {
		if (!have_key(key_list[i], buf)) {
			error("{red}Invalid config file, there is no key:%s\n{clear}", key_list[i]);
		}
	}
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
			if (cap_from_name(drop_caplist[i], &(container->drop_caplist[i])) < 0) {
				error("{red}Invalid capability:%s\n{clear}", drop_caplist[i]);
			}
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
	// Get cpupercent.
	container->cpupercent = k2v_get_key(int, "cpupercent", buf);
	// Get just_chroot.
	container->just_chroot = k2v_get_key(bool, "just_chroot", buf);
	// Get work_dir.
	container->work_dir = k2v_get_key(char, "work_dir", buf);
	// Get rootfs_source.
	container->rootfs_source = k2v_get_key(char, "rootfs_source", buf);
	// Get unmask_dirs.
	container->unmask_dirs = k2v_get_key(bool, "unmask_dirs", buf);
	// Get hostname.
	container->hostname = k2v_get_key(char, "hostname", buf);
	// Get user.
	if (container->user == NULL) {
		container->user = k2v_get_key(char, "user", buf);
	}
	// Get env.
	int envlen = k2v_get_key(char_array, "env", buf, container->env, MAX_ENVS);
	if (envlen % 2 != 0) {
		error("{red}Invalid env format\n{clear}");
	}
	container->env[envlen] = NULL;
	container->env[envlen + 1] = NULL;
	// Get extra_mountpoint.
	int mlen = k2v_get_key(char_array, "extra_mountpoint", buf, container->extra_mountpoint, MAX_MOUNTPOINTS);
	if (mlen % 2 != 0) {
		error("{red}Invalid extra_mountpoint format\n{clear}");
	}
	container->extra_mountpoint[mlen] = NULL;
	container->extra_mountpoint[mlen + 1] = NULL;
	// Get extra_ro_mountpoint.
	mlen = k2v_get_key(char_array, "extra_ro_mountpoint", buf, container->extra_ro_mountpoint, MAX_MOUNTPOINTS);
	if (mlen % 2 != 0) {
		error("{red}Invalid extra_ro_mountpoint format\n{clear}");
	}
	container->extra_ro_mountpoint[mlen] = NULL;
	container->extra_ro_mountpoint[mlen + 1] = NULL;
	free(buf);
	buf = container_info_to_k2v(container);
	log("{base}Container config in %s:{cyan}\n%s", path, buf);
	free(buf);
}
