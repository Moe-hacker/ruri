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
// Umount container.
void umount_container(const char *container_dir)
{
	if (container_dir == NULL) {
		error("\033[31mError: container directory does not exist QwQ\n");
	}
	// Do not use '/' for container_dir.
	if (strcmp(container_dir, "/") == 0) {
		error("\033[31mError: `/` is not allowed to use as a container directory QwQ\n");
	}
	// Check if container_dir exist.
	DIR *direxist = opendir(container_dir);
	if (direxist == NULL) {
		error("\033[31mError: container directory does not exist QwQ\n");
	}
	closedir(direxist);
	struct CONTAINER *container = read_info(NULL, container_dir);
	char infofile[PATH_MAX] = { '\0' };
	sprintf(infofile, "%s/.rurienv", container_dir);
	remove(infofile);
	// Get path to umount.
	char sys_dir[PATH_MAX];
	char proc_dir[PATH_MAX];
	char dev_dir[PATH_MAX];
	char to_umountpoint[PATH_MAX];
	strcpy(sys_dir, container_dir);
	strcpy(proc_dir, container_dir);
	strcpy(dev_dir, container_dir);
	strcat(sys_dir, "/sys");
	strcat(proc_dir, "/proc");
	strcat(dev_dir, "/dev");
	// Umount other mountpoints.
	if (container != NULL) {
		// Umount extra_mountpoint.
		for (int i = 1; true; i += 2) {
			if (container->extra_mountpoint[i] != NULL) {
				strcpy(to_umountpoint, container_dir);
				strcat(to_umountpoint, container->extra_mountpoint[i]);
				for (int j = 0; j < 10; j++) {
					umount2(to_umountpoint, MNT_DETACH | MNT_FORCE);
					umount(to_umountpoint);
					usleep(20000);
				}
			} else {
				break;
			}
		}
		// Umount extra_ro_mountpoint.
		for (int i = 1; true; i += 2) {
			if (container->extra_ro_mountpoint[i] != NULL) {
				strcpy(to_umountpoint, container_dir);
				strcat(to_umountpoint, container->extra_ro_mountpoint[i]);
				for (int j = 0; j < 10; j++) {
					umount2(to_umountpoint, MNT_DETACH | MNT_FORCE);
					umount(to_umountpoint);
					usleep(20000);
				}
			} else {
				break;
			}
		}
	}
	// Force umount system runtime directories for 10 times.
	for (int i = 1; i < 10; i++) {
		umount2(sys_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(dev_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(proc_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(container_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
	}
}
