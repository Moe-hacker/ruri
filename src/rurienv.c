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
	char *ret = (char *)malloc(65536);
	ret[0] = '\0';
	char buf[4096] = { '\0' };
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
	sprintf(buf, "no_new_privs=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->no_new_privs ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "enable_seccomp=");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, container->enable_seccomp ? "\"true\"\n" : "\"false\"\n");
	strcat(ret, buf);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "ns_pid=\"%d\"\n", container->ns_pid);
	strcat(ret, buf);
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
	return ret;
}
// Store container info.
void store_info(const struct CONTAINER *container)
{
	char *info = build_container_info(container);
	char file[PATH_MAX] = { '\0' };
	sprintf(file, "%s/.rurienv", container->container_dir);
	unlink(file);
	remove(file);
	int fd = creat(file, S_IWUSR | S_IRUSR);
	write(fd, info, strlen(info));
	close(fd);
	free(info);
}
// Read .rurienv file.
struct CONTAINER *read_info(struct CONTAINER *container, const char *container_dir)
{
	char file[PATH_MAX] = { '\0' };
	sprintf(file, "%s/.rurienv", container_dir);
	int fd = open(file, O_RDONLY);
	if (fd < 0) {
		return container;
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	close(fd);
	char *buf = k2v_open_file(file, (size_t)size);
	if (container == NULL) {
		container = (struct CONTAINER *)malloc(sizeof(struct CONTAINER));
		int mlen = key_get_char_array("extra_mountpoint", buf, container->extra_mountpoint);
		container->extra_mountpoint[mlen] = NULL;
		container->extra_mountpoint[mlen + 1] = NULL;
		close(fd);
		free(buf);
		return container;
	}
	if (container->enable_unshare && !is_ruri_pid(key_get_int("ns_pid", buf))) {
		remove(file);
		return container;
	}
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
	container->no_new_privs = key_get_bool("no_new_privs", buf);
	container->enable_seccomp = key_get_bool("enable_seccomp", buf);
	container->ns_pid = key_get_int("ns_pid", buf);
	int envlen = key_get_char_array("env", buf, container->env);
	container->env[envlen] = NULL;
	container->env[envlen + 1] = NULL;
	int mlen = key_get_char_array("extra_mountpoint", buf, container->extra_mountpoint);
	container->extra_mountpoint[mlen] = NULL;
	container->extra_mountpoint[mlen + 1] = NULL;
	return container;
}
