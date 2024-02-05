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
// Run after chroot(2), called by run_chroot_container().
static void init_container(void)
{
	/*
	 * It'll be run after chroot(2), so `/` is the root dir of container now.
	 * The device list and permissions are based on common docker container.
	 */
	// Check if system runtime files are already created.
	DIR *direxist = opendir("/sys/kernel");
	if (direxist == NULL) {
		// Mount && create system runtime files.
		// umount /proc before we mount it.
		// Maybe needless.
		umount2("/proc", MNT_DETACH | MNT_FORCE);
		// Mount proc,sys and dev.
		mkdir("/sys", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mkdir("/proc", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mkdir("/dev", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mount("proc", "/proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
		// For /sys,we make it read-only.
		mount("sysfs", "/sys", "sysfs", MS_NOSUID | MS_NOEXEC | MS_NODEV | MS_RDONLY, NULL);
		mount("tmpfs", "/dev", "tmpfs", MS_NOSUID, "size=65536k,mode=755");
		// Continue mounting some other directories in /dev.
		mkdir("/dev/pts", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mount("devpts", "/dev/pts", "devpts", 0, "gid=4,mode=620");
		mkdir("/dev/shm", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mount("tmpfs", "/dev/shm", "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, "mode=1777");
		// Protect some system runtime directories by mounting themselves as read-only.
		mount("/proc/bus", "/proc/bus", NULL, MS_BIND | MS_REC, NULL);
		mount("/proc/bus", "/proc/bus", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
		mount("/proc/fs", "/proc/fs", NULL, MS_BIND | MS_REC, NULL);
		mount("/proc/fs", "/proc/fs", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
		mount("/proc/irq", "/proc/irq", NULL, MS_BIND | MS_REC, NULL);
		mount("/proc/irq", "/proc/irq", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
		mount("/proc/sys", "/proc/sys", NULL, MS_BIND | MS_REC, NULL);
		mount("/proc/sys", "/proc/sys", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
		mount("/proc/sys-trigger", "/proc/sys-trigger", NULL, MS_BIND | MS_REC, NULL);
		mount("/proc/sys-trigger", "/proc/sys-trigger", NULL, MS_BIND | MS_RDONLY | MS_REMOUNT, NULL);
		// Mount binfmt_misc.
		mount("binfmt_misc", "/proc/sys/fs/binfmt_misc", "binfmt_misc", 0, NULL);
		// Create system runtime files in /dev and then fix permissions.
		mknod("/dev/null", S_IFCHR, makedev(1, 3));
		chmod("/dev/null", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		mknod("/dev/console", S_IFCHR, makedev(5, 1));
		chown("/dev/console", 0, 5);
		chmod("/dev/console", S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH);
		mknod("/dev/zero", S_IFCHR, makedev(1, 5));
		chmod("/dev/zero", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		mknod("/dev/ptmx", S_IFCHR, makedev(5, 2));
		chown("/dev/ptmx", 0, 5);
		chmod("/dev/ptmx", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		mknod("/dev/tty", S_IFCHR, makedev(5, 0));
		chown("/dev/tty", 0, 5);
		chmod("/dev/tty", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		mknod("/dev/random", S_IFCHR, makedev(1, 8));
		chmod("/dev/random", S_IRUSR | S_IRGRP | S_IROTH);
		mknod("/dev/urandom", S_IFCHR, makedev(1, 9));
		chmod("/dev/urandom", S_IRUSR | S_IRGRP | S_IROTH);
		mkdir("/dev/net", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mknod("/dev/net/tun", S_IFCHR, makedev(10, 200));
		// Create some system runtime link files in /dev.
		symlink("/proc/self/fd", "/dev/fd");
		symlink("/proc/self/fd/0", "/dev/stdin");
		symlink("/proc/self/fd/1", "/dev/stdout");
		symlink("/proc/self/fd/2", "/dev/stderr");
		symlink("/dev/null", "/dev/tty0");
		// Mask some directories/files.
		mount("tmpfs", "/proc/asound", "tmpfs", MS_RDONLY, NULL);
		mount("tmpfs", "/proc/acpi", "tmpfs", MS_RDONLY, NULL);
		mount("/dev/null", "/proc/kcore", "", MS_BIND, NULL);
		mount("/dev/null", "/proc/keys", "", MS_BIND, NULL);
		mount("/dev/null", "/proc/latency_stats", "", MS_BIND, NULL);
		mount("/dev/null", "/proc/timer_list", "", MS_BIND, NULL);
		mount("/dev/null", "/proc/timer_stats", "", MS_BIND, NULL);
		mount("/dev/null", "/proc/sched_debug", "", MS_BIND, NULL);
		mount("tmpfs", "/proc/scsi", "tmpfs", MS_RDONLY, NULL);
		mount("tmpfs", "/sys/firmware", "tmpfs", MS_RDONLY, NULL);
		mount("tmpfs", "/sys/devices/virtual/powercap", "tmpfs", MS_RDONLY, NULL);
		mount("tmpfs", "/sys/block", "tmpfs", MS_RDONLY, NULL);
	}
	// Avoid running closedir(NULL), we put it to else branch.
	else {
		closedir(direxist);
	}
}
// Run before chroot(2), so that init_container() will not take effect.
static void mount_host_runtime(struct CONTAINER_INFO *container_info)
{
	char buf[PATH_MAX] = { '\0' };
	// Mount /dev.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/dev", container_info->container_dir);
	mount("/dev", buf, NULL, MS_BIND, NULL);
	// mount /proc.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/proc", container_info->container_dir);
	mount("/proc", buf, NULL, MS_BIND, NULL);
	// Mount /sys.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/sys", container_info->container_dir);
	mount("/sys", buf, NULL, MS_BIND, NULL);
	// Mount binfmt_misc.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/proc/sys/fs/binfmt_misc", container_info->container_dir);
	mount("binfmt_misc", buf, "binfmt_misc", 0, NULL);
	// Mount devpts.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/dev/pts", container_info->container_dir);
	mkdir(buf, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("devpts", buf, "devpts", 0, NULL);
	// Mount devshm.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/dev/shm", container_info->container_dir);
	mkdir(buf, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("tmpfs", buf, "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, "mode=1777");
}
// Drop capabilities.
// Use libcap.
static void drop_caps(struct CONTAINER_INFO *container_info)
{
	for (int i = 0; i < CAP_LAST_CAP + 1; i++) {
		// INIT_VALUE is the end of drop_caplist[].
		if (container_info->drop_caplist[i] == INIT_VALUE) {
			break;
		}
		if (cap_drop_bound(container_info->drop_caplist[i]) != 0 && !container_info->no_warnings) {
			warning("\033[33mWarning: Failed to drop cap `%s`\n", cap_to_name(container_info->drop_caplist[i]));
			warning("\033[33merror reason: %s\033[0m\n", strerror(errno));
		}
	}
}
// Set envs.
static void set_envs(struct CONTAINER_INFO *container_info)
{
	// Set $PATH to the common value in GNU/Linux, because $PATH in termux will not work in GNU/Linux containers.
	setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
	// Set $TMPDIR.
	setenv("TMPDIR", "/tmp", 1);
	// Set other envs.
	for (int i = 0; true; i += 2) {
		if (container_info->env[i] == NULL) {
			break;
		}
		setenv(container_info->env[i], container_info->env[i + 1], 1);
	}
}
// Run after init_container().
static void setup_binfmt_misc(const char *cross_arch, const char *qemu_path)
{
	// Get elf magic header.
	struct MAGIC *magic = get_magic(cross_arch);
	char buf[1024] = { '\0' };
	// Format: ":name:type:offset:magic:mask:interpreter:flags".
	sprintf(buf, ":%s%s:M:0:%s:%s:%s:PCF", "ruri-", cross_arch, magic->magic, magic->mask, qemu_path);
	// Just to make clang-tidy happy.
	free(magic);
	// This needs CONFIG_BINFMT_MISC enabled in your kernel.
	int register_fd = open("/proc/sys/fs/binfmt_misc/register", O_WRONLY | O_CLOEXEC);
	if (register_fd < 0) {
		error("\033[31mError: Failed to setup binfmt_misc, check your kernel config QwQ");
	}
	// Set binfmt_misc config.
	write(register_fd, buf, strlen(buf));
	close(register_fd);
}
// Mount other mountpoints.
// Run before chroot(2).
void mount_mountpoints(struct CONTAINER_INFO *container_info)
{
	for (int i = 0; true; i += 2) {
		if (container_info->mountpoint[i] == NULL) {
			break;
		}
		// Set the mountpoint to mount.
		char *mountpoint_dir = (char *)malloc(strlen(container_info->mountpoint[i + 1]) + strlen(container_info->container_dir) + 2);
		strcpy(mountpoint_dir, container_info->container_dir);
		strcat(mountpoint_dir, container_info->mountpoint[i + 1]);
		trymount(container_info->mountpoint[i], mountpoint_dir, 0);
		free(mountpoint_dir);
	}
}
// Run chroot container.
void run_chroot_container(struct CONTAINER_INFO *container_info)
{
	/*
	 * It's called by main() and run_unshare_container().
	 * It will chroot(2) to container_dir, call to init_container(), drop capabilities and exec(3) init command in container.
	 */
	// Ignore SIGTTIN, if we are running in the background, SIGTTIN may kill this process.
	sigset_t sigs;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGTTIN);
	sigaddset(&sigs, SIGTTOU);
	sigprocmask(SIG_BLOCK, &sigs, 0);
	// Mount mountpoints.
	mount_mountpoints(container_info);
	// Check if system runtime files are already created.
	char buf[PATH_MAX] = { '\0' };
	sprintf(buf, "%s/sys/kernel", container_info->container_dir);
	DIR *direxist = opendir(buf);
	if (direxist == NULL) {
		// '/' should be a mountpoint in container.
		mount(container_info->container_dir, container_info->container_dir, NULL, MS_BIND, NULL);
		// If `-S` option is set, bind-mount /dev/, /sys/ and /proc/ from host.
		if (container_info->host_runtime_dir) {
			mount_host_runtime(container_info);
		}
	}
	// Avoid running closedir(NULL), we put it to else branch.
	else {
		closedir(direxist);
	}
	// Set default command for exec().
	if (container_info->command[0] == NULL) {
		container_info->command[0] = "/bin/su";
		container_info->command[1] = "-";
		container_info->command[2] = NULL;
	}
	// chroot(2) into container.
	chdir(container_info->container_dir);
	chroot(".");
	chdir("/");
	chroot("/");
	// Mount/create system runtime dir/files.
	init_container();
	// Fix /etc/mtab.
	remove("/etc/mtab");
	unlink("/etc/mtab");
	symlink("/proc/mounts", "/etc/mtab");
	// Set up Seccomp BPF.
	if (container_info->enable_seccomp) {
		setup_seccomp(container_info);
	}
	// Drop caps.
	drop_caps(container_info);
	// Set envs.
	set_envs(container_info);
	// Fix a bug that the terminal is frozen.
	usleep(200000);
	// Set NO_NEW_PRIVS Flag.
	// It requires Linux3.5 or later.
	// It will make sudo unavailable in container.
	if (container_info->no_new_privs) {
		prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	}
	// Disallow raising ambient capabilities via the prctl(2) PR_CAP_AMBIENT_RAISE operation.
	prctl(PR_SET_SECUREBITS, SECBIT_NO_CAP_AMBIENT_RAISE);
	// We only need 0(stdin), 1(stdout), 2(stderr),
	// So we close the other fds to avoid security issues.
	for (int i = 3; i <= 10; i++) {
		close(i);
	}
	// Setup binfmt_misc.
	if (container_info->cross_arch != NULL) {
		setup_binfmt_misc(container_info->cross_arch, container_info->qemu_path);
	}
	// Execute command in container.
	// Use exec(3) function because system(3) may be unavailable now.
	if (execv(container_info->command[0], container_info->command) == -1) {
		// Catch exceptions.
		error("\033[31mFailed to execute `%s`\nexecv() returned: %d\nerror reason: %s\033[0m\n", container_info->command[0], errno, strerror(errno));
	}
}
