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
char *container_info_to_k2v(const struct CONTAINER *container)
{
	/*
	 * Format container info to k2v format.
	 * return the string type of config.
	 */
	// The HOMO way!
	size_t size = 114514;
	char *ret = (char *)malloc(size);
	ret[0] = '\0';
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
	ret = k2v_add_config(char_array, ret, "drop_caplist", drop_caplist, len);
	// Make ASAN happy.
	for (int i = 0; i < len; i++) {
		cap_free(drop_caplist[i]);
	}
	// no_new_privs.
	ret = k2v_add_config(bool, ret, "no_new_privs", container->no_new_privs);
	// enable_unshare.
	ret = k2v_add_config(bool, ret, "enable_unshare", container->enable_unshare);
	// rootless.
	ret = k2v_add_config(bool, ret, "rootless", container->rootless);
	// mount_host_runtime.
	ret = k2v_add_config(bool, ret, "mount_host_runtime", container->mount_host_runtime);
	// ro_root.
	ret = k2v_add_config(bool, ret, "ro_root", container->ro_root);
	// no_warnings.
	ret = k2v_add_config(bool, ret, "no_warnings", container->no_warnings);
	// cross_arch.
	ret = k2v_add_config(char, ret, "cross_arch", container->cross_arch);
	// qemu_path.
	ret = k2v_add_config(char, ret, "qemu_path", container->qemu_path);
	// use_rurienv.
	ret = k2v_add_config(bool, ret, "use_rurienv", container->use_rurienv);
	// enable_seccomp.
	ret = k2v_add_config(bool, ret, "enable_seccomp", container->enable_seccomp);
	// cpuset.
	ret = k2v_add_config(char, ret, "cpuset", container->cpuset);
	// memory.
	ret = k2v_add_config(char, ret, "memory", container->memory);
	// extra_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_config(char_array, ret, "extra_mountpoint", container->extra_mountpoint, len);
	// extra_ro_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_ro_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_config(char_array, ret, "extra_ro_mountpoint", container->extra_ro_mountpoint, len);
	// env.
	for (int i = 0; true; i++) {
		if (container->env[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_config(char_array, ret, "env", container->env, len);
	// command.
	for (int i = 0; true; i++) {
		if (container->command[i] == NULL) {
			len = i;
			break;
		}
	}
	ret = k2v_add_config(char_array, ret, "command", container->command, len);
	// container_dir.
	ret = k2v_add_config(char, ret, "container_dir", container->container_dir);
	return ret;
}
void read_config(struct CONTAINER *container, const char *path)
{
	/*
	 * Read k2v format config file,
	 * and set container config.
	 * Return the `container` struct back.
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
	int caplen = key_get_char_array("drop_caplist", buf, drop_caplist);
	drop_caplist[caplen] = NULL;
	for (int i = 0; true; i++) {
		if (drop_caplist[i] == NULL) {
			break;
		}
		cap_from_name(drop_caplist[i], &(container->drop_caplist[i]));
		free(drop_caplist[i]);
		container->drop_caplist[i + 1] = INIT_VALUE;
	}
	// Get no_new_privs.
	container->no_new_privs = key_get_bool("no_new_privs", buf);
	// Get enable_seccomp.
	container->enable_seccomp = key_get_bool("enable_seccomp", buf);
	// Get container_dir.
	container->container_dir = key_get_char("container_dir", buf);
	// Get qemu_path.
	container->qemu_path = key_get_char("qemu_path", buf);
	// Get cross_arch.
	container->cross_arch = key_get_char("cross_arch", buf);
	// Get rootless.
	container->rootless = key_get_bool("rootless", buf);
	// Get mount_host_runtime.
	container->mount_host_runtime = key_get_bool("mount_host_runtime", buf);
	// Get ro_root.
	container->ro_root = key_get_bool("ro_root", buf);
	// Get no_warnings.
	container->no_warnings = key_get_bool("no_warnings", buf);
	// Get use_rurienv.
	container->use_rurienv = key_get_bool("use_rurienv", buf);
	// Get cpuset.
	container->cpuset = key_get_char("cpuset", buf);
	// Get memory.
	container->memory = key_get_char("memory", buf);
	// Get env.
	int envlen = key_get_char_array("env", buf, container->env);
	container->env[envlen] = NULL;
	container->env[envlen + 1] = NULL;
	// Get extra_mountpoint.
	int mlen = key_get_char_array("extra_mountpoint", buf, container->extra_mountpoint);
	container->extra_mountpoint[mlen] = NULL;
	container->extra_mountpoint[mlen + 1] = NULL;
	// Get extra_ro_mountpoint.
	mlen = key_get_char_array("extra_ro_mountpoint", buf, container->extra_ro_mountpoint);
	container->extra_ro_mountpoint[mlen] = NULL;
	container->extra_ro_mountpoint[mlen + 1] = NULL;
	free(buf);
}
