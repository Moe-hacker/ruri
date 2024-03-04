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
	char *ret = (char *)malloc(65536);
	ret[0] = '\0';
	char *buf = NULL;
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
	buf = char_array_to_k2v("drop_caplist", drop_caplist, len);
	strcat(ret, buf);
	free(buf);
	// no_new_privs.
	buf = bool_to_k2v("no_new_privs", container->no_new_privs);
	strcat(ret, buf);
	free(buf);
	// enable_unshare.
	buf = bool_to_k2v("enable_unshare", container->enable_unshare);
	strcat(ret, buf);
	free(buf);
	// rootless.
	buf = bool_to_k2v("rootless", container->rootless);
	strcat(ret, buf);
	free(buf);
	// mount_host_runtime.
	buf = bool_to_k2v("mount_host_runtime", container->mount_host_runtime);
	strcat(ret, buf);
	free(buf);
	// no_warnings.
	buf = bool_to_k2v("no_warnings", container->no_warnings);
	strcat(ret, buf);
	free(buf);
	// cross_arch.
	buf = char_to_k2v("cross_arch", container->cross_arch);
	strcat(ret, buf);
	free(buf);
	// qemu_path.
	buf = char_to_k2v("qemu_path", container->qemu_path);
	strcat(ret, buf);
	free(buf);
	// use_rurienv.
	buf = bool_to_k2v("use_rurienv", container->use_rurienv);
	strcat(ret, buf);
	free(buf);
	// enable_seccomp.
	buf = bool_to_k2v("enable_seccomp", container->enable_seccomp);
	strcat(ret, buf);
	free(buf);
	// extra_mountpoint.
	for (int i = 0; true; i++) {
		if (container->extra_mountpoint[i] == NULL) {
			len = i;
			break;
		}
	}
	buf = char_array_to_k2v("extra_mountpoint", container->extra_mountpoint, len);
	strcat(ret, buf);
	free(buf);
	// env.
	for (int i = 0; true; i++) {
		if (container->env[i] == NULL) {
			len = i;
			break;
		}
	}
	buf = char_array_to_k2v("env", container->env, len);
	strcat(ret, buf);
	free(buf);
	// command.
	for (int i = 0; true; i++) {
		if (container->command[i] == NULL) {
			len = i;
			break;
		}
	}
	buf = char_array_to_k2v("command", container->command, len);
	strcat(ret, buf);
	free(buf);
	// container_dir.
	buf = char_to_k2v("container_dir", container->container_dir);
	strcat(ret, buf);
	return ret;
}
struct CONTAINER *read_config(struct CONTAINER *container, const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0) {
		error("\033[31mNo such file or directory:%s\n\033[0m", path);
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
	// Get no_warnings.
	container->no_warnings = key_get_bool("no_warnings", buf);
	// Get use_rurienv.
	container->use_rurienv = key_get_bool("use_rurienv", buf);
	// Get env.
	int envlen = key_get_char_array("env", buf, container->env);
	container->env[envlen] = NULL;
	container->env[envlen + 1] = NULL;
	// Get extra_mountpoint.
	int mlen = key_get_char_array("extra_mountpoint", buf, container->extra_mountpoint);
	container->extra_mountpoint[mlen] = NULL;
	container->extra_mountpoint[mlen + 1] = NULL;
	return container;
}
