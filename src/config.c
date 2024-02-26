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
	char buf[4096] = { '\0' };
	// drop_caplist.
	sprintf(buf, "drop_caplist=[");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	for (int i = 0; true; i++) {
		if (container->drop_caplist[i] == INIT_VALUE) {
			sprintf(buf, "]\n");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
			break;
		}
		sprintf(buf, "\"%s\"", cap_to_name(container->drop_caplist[i]));
		strcat(ret, buf);
		memset(buf, 0, sizeof(buf));
		if (container->drop_caplist[i + 1] != INIT_VALUE) {
			sprintf(buf, ",");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
		}
	}
	// no_new_privs.
	sprintf(buf, "no_new_privs=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->no_new_privs ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// enable_unshare.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "enable_unshare=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->enable_unshare ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// rootless.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "rootless=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->rootless ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// mount_host_runtime.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "mount_host_runtime=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->mount_host_runtime ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// no_warnings.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "no_warnings=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->no_warnings ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// cross_arch.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "cross_arch=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	if (container->cross_arch) {
		sprintf(buf, "\"%s\"\n", container->cross_arch);
	} else {
		sprintf(buf, "\"\"\n");
	}
	strcat(ret, buf);
	// qemu_path.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "qemu_path=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	if (container->qemu_path) {
		sprintf(buf, "\"%s\"\n", container->qemu_path);
	} else {
		sprintf(buf, "\"\"\n");
	}
	strcat(ret, buf);
	// use_rurienv.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "use_rurienv=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->use_rurienv ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// enable_seccomp.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "enable_seccomp=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->enable_seccomp ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	// extra_mountpoint.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "extra_mountpoint=[");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	for (int i = 0; true; i++) {
		if (container->extra_mountpoint[i] == NULL) {
			sprintf(buf, "]\n");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
			break;
		}
		sprintf(buf, "\"%s\"", container->extra_mountpoint[i]);
		strcat(ret, buf);
		memset(buf, 0, sizeof(buf));
		if (container->extra_mountpoint[i + 1] != NULL) {
			sprintf(ret, ",");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
		}
	}
	// env.
	sprintf(buf, "env=[");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	for (int i = 0; true; i++) {
		if (container->env[i] == NULL) {
			sprintf(buf, "]\n");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
			break;
		}
		sprintf(buf, "\"%s\"", container->env[i]);
		strcat(ret, buf);
		memset(buf, 0, sizeof(buf));
		if (container->env[i + 1] != NULL) {
			sprintf(buf, ",");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
		}
	}
	// command.
	sprintf(buf, "command=[");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	for (int i = 0; true; i++) {
		if (container->command[i] == NULL) {
			sprintf(buf, "]\n");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
			break;
		}
		sprintf(buf, "\"%s\"", container->command[i]);
		strcat(ret, buf);
		memset(buf, 0, sizeof(buf));
		if (container->command[i + 1] != NULL) {
			sprintf(buf, ",");
			strcat(ret, buf);
			memset(buf, 0, sizeof(buf));
		}
	}
	// container_dir.
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "container_dir=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "\"%s\"\n", container->container_dir);
	strcat(ret, buf);
	return ret;
}
struct CONTAINER *read_config(struct CONTAINER *container, const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "\033[31mNo such file or directory:%s\n\033[0m", path);
		exit(EXIT_FAILURE);
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
