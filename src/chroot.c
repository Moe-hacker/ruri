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
#ifdef __RURI_DEV__
// Dev log.
static void devlog(struct CONTAINER_INFO *container_info)
{
	printf("\033[1;38;2;254;228;208mRun chroot container:\n");
	printf("%s%s\n", "container_dir: \033[1;38;2;152;245;225m", container_info->container_dir);
	if (container_info->no_new_privs) {
		printf("%s\n", "\033[1;38;2;254;228;208mno_new_privs: \033[1;38;2;152;245;225mtrue");
	} else {
		printf("%s\n", "\033[1;38;2;254;228;208mno_new_privs: \033[1;38;2;152;245;225mfalse");
	}
	if (container_info->enable_seccomp) {
		printf("%s\n", "\033[1;38;2;254;228;208menable_seccomp: \033[1;38;2;152;245;225mtrue");
	} else {
		printf("%s\n", "\033[1;38;2;254;228;208menable_seccomp: \033[1;38;2;152;245;225mfalse");
	}
	printf("\033[1;38;2;254;228;208minit command : \033[1;38;2;152;245;225m");
	for (int i = 0; true; i++) {
		if (container_info->command[i] == NULL) {
			printf("\n");
			break;
		}
		printf("%s%s", container_info->command[i], " ");
	}
	printf("\033[1;38;2;254;228;208mdrop caplist: \033[1;38;2;152;245;225m");
	for (int i = 0; true; i++) {
		if (container_info->drop_caplist[i] == INIT_VALUE) {
			printf("\n");
			break;
		}
		printf("%s%s", cap_to_name(container_info->drop_caplist[i]), " ");
	}
	printf("\033[1;38;2;254;228;208mMountpoints: \033[1;38;2;152;245;225m\n");
	for (int i = 0; true; i += 2) {
		if (container_info->mountpoint[i] == NULL) {
			printf("\n");
			break;
		}
		printf("%s%s", container_info->mountpoint[i], " \033[1;38;2;123;104;238mto \033[1;38;2;152;245;225m");
		printf("%s%s", container_info->mountpoint[i + 1], "\n");
	}
	printf("\033[1;38;2;254;228;208mEnvs: \033[1;38;2;152;245;225m\n");
	for (int i = 0; true; i += 2) {
		if (container_info->env[i] == NULL) {
			printf("\033[0m\n");
			break;
		}
		printf("%s%s", container_info->env[i], " \033[1;38;2;123;104;238m=\033[1;38;2;152;245;225m ");
		printf("%s%s", container_info->env[i + 1], "\n");
	}
}
#endif
// Run after chroot(2), called by run_chroot_container().
static void init_container(void)
{
	/*
	 * It'll be run after chroot(2), so `/` is the root dir of container now.
	 * The device list and permissions are based on common docker container.
	 */
	// umount /proc before we mount it.
	umount2("/proc", MNT_DETACH | MNT_FORCE);
	// Fix issues in archlinux containers.
	mount("/", "/", NULL, MS_BIND, NULL);
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
	mkdir("/dev/mqune", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("mqune", "/dev/mqune", "mqune", 0, NULL);
	// Protect some system runtime directories by mounting themselves as read-only.
	mount("/proc/bus", "/proc/bus", "proc", MS_BIND | MS_RDONLY, NULL);
	mount("/proc/fs", "/proc/fs", "proc", MS_BIND | MS_RDONLY, NULL);
	mount("/proc/irq", "/proc/irq", "proc", MS_BIND | MS_RDONLY, NULL);
	mount("/proc/sys", "/proc/sys", "proc", MS_BIND | MS_RDONLY, NULL);
	mount("/proc/asound", "/proc/asound", "proc", MS_BIND | MS_RDONLY, NULL);
	mount("/proc/scsi", "/proc/scsi", "proc", MS_BIND | MS_RDONLY, NULL);
	mount("/sys/firmware", "/sys/firmware", "sysfs", MS_BIND | MS_RDONLY, NULL);
	mount("tmpfs", "/sys/block", "tmpfs", MS_NOSUID, "size=65536k,mode=755");
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
	// Fix issues in archlinux containers.
	remove("/etc/mtab");
	unlink("/etc/mtab");
	symlink("/proc/mounts", "/etc/mtab");
}
// Return the same value as mkdir().
static int mkdirs(char *dir, mode_t mode)
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
// Mount other mountpoints.
// Run before chroot(2).
static void mount_mountpoints(struct CONTAINER_INFO *container_info)
{
	for (int i = 0; true; i += 2) {
		if (container_info->mountpoint[i] != NULL) {
			// Set the mountpoint to mount.
			char *mountpoint_dir = (char *)malloc(strlen(container_info->mountpoint[i + 1]) + strlen(container_info->container_dir) + 2);
			strcpy(mountpoint_dir, container_info->container_dir);
			strcat(mountpoint_dir, container_info->mountpoint[i + 1]);
			// Check if mountpoint exists.
			DIR *test = opendir(mountpoint_dir);
			if (test == NULL) {
				if (mkdirs(mountpoint_dir, 0755) != 0) {
					error("\033[31mCould not create mountpoint directory\n");
				}
			} else {
				closedir(test);
			}
			// Mount mountpoints.
			mount(container_info->mountpoint[i], mountpoint_dir, NULL, MS_BIND, NULL);
			free(mountpoint_dir);
		} else {
			break;
		}
	}
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
	// Set other envs.
	for (int i = 0; true; i += 2) {
		if (container_info->env[i] != NULL) {
			setenv(container_info->env[i], container_info->env[i + 1], 1);
		} else {
			break;
		}
	}
}
// Run chroot container.
void run_chroot_container(struct CONTAINER_INFO *container_info)
{
	/*
	 * It's called by main(), run_unshare_container() and daemon_init_unshare_container().
	 * It will chroot(2) to container_dir, call to init_container(), drop capabilities and exec(3) init command in container.
	 */
	// Ignore SIGTTIN, if we are running in the background, SIGTTIN may kill this process.
	sigset_t sigs;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGTTIN);
	sigprocmask(SIG_BLOCK, &sigs, 0);
#ifdef __RURI_DEV__
	devlog(container_info);
#endif
	// Mount mountpoints.
	mount_mountpoints(container_info);
	// Set default command for exec().
	if (container_info->command[0] == NULL) {
		container_info->command[0] = "/bin/su";
		container_info->command[1] = "-";
		container_info->command[2] = NULL;
	}
	// chroot(2) into container.
	chroot(container_info->container_dir);
	chdir("/");
	// Check if system runtime files are already created.
	DIR *direxist = opendir("/sys/kernel");
	if (direxist == NULL) {
		// Mount && create system runtime files.
		init_container();
	}
	// Avoid running closedir(NULL), we put it to else branch.
	else {
		closedir(direxist);
	}
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
	// Execute command in container.
	// Use exec(3) function because system(3) may be unavailable now.
	if (execv(container_info->command[0], container_info->command) == -1) {
		// Catch exceptions.
		error("\033[31mFailed to execute `%s`\nexecv() returned: %d\nerror reason: %s\033[0m\n", container_info->command[0], errno, strerror(errno));
	}
}
