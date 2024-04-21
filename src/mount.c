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
// Return the same value as mkdir().
static int mkdirs(const char *dir, mode_t mode)
{
	/*
	 * A very simple implementation of mkdir -p.
	 * I don't know why it seems that there isn't an existing function to do this...
	 */
	char buf[PATH_MAX];
	int ret = 0;
	/* If dir is path/to/mkdir
	 * We do:
	 * ret = mkdir("path",mode);
	 * ret = mkdir("path/to",mode);
	 * ret = mkdir("path/to/mkdir",mode);
	 * return ret;
	 */
	for (size_t i = 1; i < strlen(dir); i++) {
		if (dir[i] == '/') {
			for (size_t j = 0; j < i; j++) {
				buf[j] = dir[j];
				buf[j + 1] = '\0';
			}
			ret = mkdir(buf, mode);
		}
	}
	// If the end of `dir` is not '/', create the last level of the directory.
	if (dir[strlen(dir) - 1] != '/') {
		ret = mkdir(dir, mode);
	}
	return ret;
}
// Mount disk device.
static int mount_device(const char *source, const char *target, unsigned long mountflags)
{
	/*
	 * /proc/filesystems format just like:
	 *
	 * nodev'\t'sysfs'\n'
	 * '\t'ext4'\n'
	 *
	 * So, every time, we read the buf until we get '\t',
	 * check if we got before is "nodev" (that means it's not a filesystem type for devices),
	 * if we reached '\n', and nodev is not set,
	 * that means we got a true filesystem type to mount,
	 * so we try to use the type we get for mount(2);
	 */
	int ret = 0;
	// Get filesystems supported.
	int fssfd = open("/proc/filesystems", O_RDONLY | O_CLOEXEC);
	char buf[4096] = { '\0' };
	read(fssfd, buf, sizeof(buf));
	close(fssfd);
	char type[128] = { '\0' };
	char label[128] = { '\0' };
	char *out = label;
	int i = 0;
	bool nodev = false;
	for (size_t j = 0; j < sizeof(buf); j++) {
		// Reached the end of buf.
		if (buf[j] == '\0') {
			break;
		}
		// Check for nodev flag.
		if (buf[j] == '\t') {
			if (strcmp(label, "nodev") == 0) {
				nodev = true;
			}
			out = type;
			i = 0;
			memset(label, '\0', sizeof(label));
		}
		// The end of current line.
		else if (buf[j] == '\n') {
			if (!nodev) {
				ret = mount(source, target, type, mountflags, NULL);
				if (ret == 0) {
					// For ro mount, we need a remount.
					ret = mount(source, target, type, mountflags | MS_REMOUNT, NULL);
					// mount(2) succeed.
					return ret;
				}
				memset(type, '\0', sizeof(type));
			}
			out = label;
			i = 0;
			nodev = false;
		}
		// Read filesystems info.
		else {
			out[i] = buf[j];
			out[i + 1] = '\0';
			i++;
		}
	}
	return ret;
}
// Same as `losetup` command.
static char *losetup(const char *img)
{
	// Get a new loopfile for losetup.
	int loopctlfd = open("/dev/loop-control", O_RDWR | O_CLOEXEC);
	// It takes the same effect as `losetup -f`.
	int devnr = ioctl(loopctlfd, LOOP_CTL_GET_FREE);
	close(loopctlfd);
	static char loopfile[PATH_MAX] = { '\0' };
	sprintf(loopfile, "/dev/loop%d", devnr);
	usleep(20000);
	int loopfd = open(loopfile, O_RDWR | O_CLOEXEC);
	if (loopfd < 0) {
		// On Android, loopfile is in /dev/block.
		memset(loopfile, 0, sizeof(loopfile));
		sprintf(loopfile, "/dev/block/loop%d", devnr);
		loopfd = open(loopfile, O_RDWR | O_CLOEXEC);
		if (loopfd < 0) {
			error("{red}Error: losetup error!\n");
		}
	}
	// It takes the same efferct as `losetup` command.
	int imgfd = open(img, O_RDONLY | O_CLOEXEC);
	ioctl(loopfd, LOOP_SET_FD, imgfd);
	close(loopfd);
	close(imgfd);
	return loopfile;
}
// Mount dev/dir/img to target.
int trymount(const char *source, const char *target, unsigned int mountflags)
{
	int ret = 0;
	// Check if mountpoint exists.
	DIR *test = opendir(target);
	if (test == NULL) {
		if (mkdirs(target, 0755) != 0) {
			return -1;
		}
	} else {
		closedir(test);
	}
	struct stat dev_stat;
	if (lstat(source, &dev_stat) != 0) {
		return -1;
	}
	// Bind-mount dir.
	if (S_ISDIR(dev_stat.st_mode)) {
		mount(source, target, NULL, mountflags | MS_BIND, NULL);
		// For ro mount, we need a remount.
		ret = mount(source, target, NULL, mountflags | MS_BIND | MS_REMOUNT, NULL);
	}
	// Block device.
	else if (S_ISBLK(dev_stat.st_mode)) {
		ret = mount_device(source, target, mountflags);
	}
	// For image file, we run losetup first.
	else if (S_ISREG(dev_stat.st_mode)) {
		ret = mount_device(losetup(source), target, mountflags);
	}
	// We do not support to mount other type of files.
	else {
		ret = -1;
	}
	return ret;
}
