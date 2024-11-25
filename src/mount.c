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
/*
 * This file provides the mount functions for ruri.
 * It's used to mount disk devices, loop devices, and dir/files.
 * It also provides ruri_mkdirs() to create directories recursively.
 */
// Return the same value as mkdir().
int ruri_mkdirs(const char *_Nonnull dir, mode_t mode)
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
static int mount_device(const char *_Nonnull source, const char *_Nonnull target, unsigned long mountflags)
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
	if (fssfd < 0) {
		return -1;
	}
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
static char *losetup(const char *_Nonnull img)
{
	/*
	 * We return the loopfile we get for losetup,
	 * so that we can use the return value to mount the image.
	 */
	// Get a new loopfile for losetup.
	int loopctlfd = open("/dev/loop-control", O_RDWR | O_CLOEXEC);
	// It takes the same effect as `losetup -f`.
	int devnr = ioctl(loopctlfd, LOOP_CTL_GET_FREE);
	close(loopctlfd);
	static char loopfile[PATH_MAX] = { '\0' };
	sprintf(loopfile, "/dev/loop%d", devnr);
	usleep(200);
	int loopfd = open(loopfile, O_RDWR | O_CLOEXEC);
	if (loopfd < 0) {
		// On Android, loopfile is in /dev/block.
		memset(loopfile, 0, sizeof(loopfile));
		sprintf(loopfile, "/dev/block/loop%d", devnr);
		loopfd = open(loopfile, O_RDWR | O_CLOEXEC);
		if (loopfd < 0) {
			// Never mind, it works.
			// We know that 1145141919810 is hardly to be exist as a directory.
			// So use this string will cause mount(2) to fail, and then we just go ahead.
			return "1145141919810";
		}
	}
	// It takes the same efferct as `losetup` command.
	int imgfd = open(img, O_RDWR | O_CLOEXEC);
	ioctl(loopfd, LOOP_SET_FD, imgfd);
	close(loopfd);
	close(imgfd);
	ruri_log("{base}losetup {cyan}%s{base} ==> {cyan}%s{base}\n", img, loopfile);
	return loopfile;
}
static int mk_mountpoint_dir(const char *_Nonnull target)
{
	/*
	 * Just to mkdir(target).
	 */
	// remove the target if it exists as a file.
	// I know this can hardly be happen, just to avoid some unexpected errors.
	remove(target);
	// Check if mountpoint exists.
	char *test = realpath(target, NULL);
	if (test == NULL) {
		if (ruri_mkdirs(target, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH) != 0) {
			return -1;
		}
	} else {
		free(test);
		return 0;
	}
	return 0;
}
static int touch_mountpoint_file(const char *_Nonnull target)
{
	/*
	 * Create a common file at target.
	 */
	// We use ruri_mkdirs() to create the parent directory of the file,
	// And rmdir() target, so we will never get error that
	// the parent directory of the file is not exist.
	ruri_mkdirs(target, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
	rmdir(target);
	// Check if mountpoint exists.
	int fd = open(target, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		fd = open(target, O_CREAT | O_CLOEXEC | O_RDWR, S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
		if (fd < 0) {
			return -1;
		}
		close(fd);
	} else {
		close(fd);
	}
	return 0;
}
// Mount dev/dir/img to target.
int ruri_trymount(const char *_Nonnull source, const char *_Nonnull target, unsigned int mountflags)
{
	/*
	 * This function is designed to mount a device/dir/image/file to target.
	 * We support to mount:
	 * Block device
	 * Directory
	 * Image file
	 * Common file
	 * Char device
	 * FIFO
	 * Socket
	 * I hope it works as expected.
	 */
	// umount target before mount(2), to avoid `device or resource busy`.
	umount2(target, MNT_DETACH | MNT_FORCE);
	int ret = 0;
	ruri_log("{base}Mounting {cyan}%s{base} to {cyan}%s{base} with flags {cyan}%d{base}\n", source, target, mountflags);
	struct stat dev_stat;
	// If source does not exist, just return -1 as error.
	if (lstat(source, &dev_stat) != 0) {
		ruri_log("{red}Error: {base}Source {cyan}%s{base} does not exist.\n", source);
		return -1;
	}
	// Bind-mount dir.
	if (S_ISDIR(dev_stat.st_mode)) {
		ruri_log("{base}Bind-mounting {cyan}%s{base} to {cyan}%s{base}\n", source, target);
		if (mk_mountpoint_dir(target) != 0) {
			return -1;
		}
		mount(source, target, NULL, mountflags | MS_BIND, NULL);
		// For ro mount, we need a remount.
		ret = mount(source, target, NULL, mountflags | MS_BIND | MS_REMOUNT, NULL);
	}
	// Block device.
	else if (S_ISBLK(dev_stat.st_mode)) {
		ruri_log("{base}Mounting block device {cyan}%s{base} to {cyan}%s{base}\n", source, target);
		if (mk_mountpoint_dir(target) != 0) {
			return -1;
		}
		ret = mount_device(source, target, mountflags);
	}
	// Image and common file.
	// We cannot distinguish image file and common file by stat(2),
	// So we try to mount it as an image file first.
	// If it fails, we bind-mount it as a common file.
	else if (S_ISREG(dev_stat.st_mode)) {
		// Image file.
		if (mk_mountpoint_dir(target) != 0) {
			return -1;
		}
		ruri_log("{base}Mounting as image file {cyan}%s{base} to {cyan}%s{base}\n", source, target);
		ret = mount_device(losetup(source), target, mountflags);
		// Common file.
		if (ret != 0) {
			if (touch_mountpoint_file(target) != 0) {
				return -1;
			}
			ruri_log("{base}Bind-mounting as common file {cyan}%s{base} to {cyan}%s{base}\n", source, target);
			mount(source, target, NULL, mountflags | MS_BIND, NULL);
			ret = mount(source, target, NULL, mountflags | MS_BIND | MS_REMOUNT, NULL);
		}
	}
	// For char-device/FIFO/socket, we just bind-mount it.
	else if (S_ISCHR(dev_stat.st_mode) || S_ISFIFO(dev_stat.st_mode) || S_ISSOCK(dev_stat.st_mode)) {
		if (touch_mountpoint_file(target) != 0) {
			return -1;
		}
		ruri_log("{base}Bind-mounting {cyan}%s{base} to {cyan}%s{base}\n", source, target);
		mount(source, target, NULL, mountflags | MS_BIND, NULL);
		ret = mount(source, target, NULL, mountflags | MS_BIND | MS_REMOUNT, NULL);
	}
	// We do not support to mount other type of files.
	else {
		ruri_log("{red}Error: {base}Unsupported file type.\n");
		ret = -1;
	}
	return ret;
}
