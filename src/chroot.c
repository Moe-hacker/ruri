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
static bool su_biany_exist(char *container_dir)
{
	/*
	 * Check if /bin/su exists in container.
	 * Because in some rootfs, /bin/su is not exist.
	 */
	char su_path[PATH_MAX] = { '\0' };
	sprintf(su_path, "%s/bin/su", container_dir);
	int fd = open(su_path, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		return false;
	}
	close(fd);
	return true;
}
static void check_binary(const struct CONTAINER *container)
{
	/*
	 * Check for binaries we need for starting the container.
	 */
	/*
	 * Since ruri use execvp() instead of execv(),
	 * we will not check for init binary here now.
	 */
	// Check QEMU path.
	if (container->cross_arch != NULL) {
		if (container->qemu_path == NULL) {
			umount_container(container->container_dir);
			error("{red}Error: path of QEMU is not set QwQ\n");
		}
		// Check if QEMU binary exists and is not a directory.
		char qemu_binary[PATH_MAX];
		strcpy(qemu_binary, container->container_dir);
		strcat(qemu_binary, container->qemu_path);
		struct stat qemu_binary_stat;
		// lstat(3) will return -1 while the init_binary does not exist.
		if (lstat(qemu_binary, &qemu_binary_stat) != 0) {
			umount_container(container->container_dir);
			error("{red}Please check if path of QEMU is correct QwQ\n");
		}
	}
}
// Run after chroot(2), called by run_chroot_container().
static void init_container(void)
{
	/*
	 * It'll be run after chroot(2), so `/` is the root dir of container now.
	 * The device list and permissions are based on common docker containers.
	 */
	// If /proc/1 exists, that means container is already initialized.
	// I used to check /sys/class/input, but in WSL1, /sys/class/input is not exist.
	// But /proc/1 is exist in all Linux systems, because it's the init process.
	char *test = realpath("/proc/1", NULL);
	if (test == NULL) {
		// Mount proc,sys and dev.
		mkdir("/sys", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mkdir("/proc", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mkdir("/dev", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
		mount("proc", "/proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
		mount("sysfs", "/sys", "sysfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
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
		// Mask some directories/files that we don't want the container modify it.
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
	} else {
		free(test);
	}
}
// Run before chroot(2), so that init_container() will not take effect.
static void mount_host_runtime(const struct CONTAINER *container)
{
	/*
	 * It's unsafe to mount /dev, /proc and /sys from the host.
	 * But in some cases, we have to do this.
	 * This function will be called before chroot(2),
	 * so it's before init_container().
	 */
	char buf[PATH_MAX] = { '\0' };
	// Mount /dev.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/dev", container->container_dir);
	mount("/dev", buf, NULL, MS_BIND, NULL);
	// mount /proc.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/proc", container->container_dir);
	mount("/proc", buf, NULL, MS_BIND, NULL);
	// Mount /sys.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/sys", container->container_dir);
	mount("/sys", buf, NULL, MS_BIND, NULL);
	// Mount binfmt_misc.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/proc/sys/fs/binfmt_misc", container->container_dir);
	mount("binfmt_misc", buf, "binfmt_misc", 0, NULL);
	// Mount devpts.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/dev/pts", container->container_dir);
	mkdir(buf, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("devpts", buf, "devpts", 0, NULL);
	// Mount devshm.
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s/dev/shm", container->container_dir);
	mkdir(buf, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	mount("tmpfs", buf, "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, "mode=1777");
}
// Drop capabilities.
// Use libcap.
static void drop_caps(const struct CONTAINER *container)
{
	/*
	 * Drop CapBnd and CapAmb as the config in container->drop_caplist[].
	 * And clear CapInh.
	 * It will be called after chroot(2).
	 */
	for (int i = 0; i < CAP_LAST_CAP + 1; i++) {
		// INIT_VALUE is the end of drop_caplist[].
		if (container->drop_caplist[i] == INIT_VALUE) {
			break;
		}
		// Check if the capability is supported in the kernel,
		// so that we can avoid unnecessary warnings.
		if (CAP_IS_SUPPORTED(container->drop_caplist[i])) {
			// Drop CapBnd.
			if (cap_drop_bound(container->drop_caplist[i]) != 0 && !container->no_warnings) {
				warning("{yellow}Warning: Failed to drop cap `%s`\n", cap_to_name(container->drop_caplist[i]));
				warning("{yellow}error reason: %s{clear}\n", strerror(errno));
			}
			// Drop CapAmb.
			prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_LOWER, container->drop_caplist[i], 0, 0);
		}
	}
	// Clear CapInh.
	// hrdp and datap are two pointers, so we malloc() to apply the memory for it first.
	cap_user_header_t hrdp = (cap_user_header_t)malloc(sizeof(typeof(*hrdp)));
	cap_user_data_t datap = (cap_user_data_t)malloc(sizeof(typeof(*datap)));
	hrdp->pid = getpid();
	hrdp->version = _LINUX_CAPABILITY_VERSION_3;
	capget(hrdp, datap);
	datap->inheritable = 0;
	capset(hrdp, datap);
// free(2) hrdp and datap here might cause ASAN error.
// I think it's because the kernel will write to the memory directly,
// but I don't know the behavior of ASAN to allocate memory, maybe after this,
// ASAN can not recognize the memory is allocated by it.
#ifndef RURI_DEBUG
	free(hrdp);
	free(datap);
#endif
}
// Set envs.
static void set_envs(const struct CONTAINER *container)
{
	/*
	 * A very useless feature, I hope it works as expected.
	 * $PATH and $TMPDIR will also be set here.
	 */
	// Set $PATH to the common value in GNU/Linux,
	// because $PATH in termux is not correct for common GNU/Linux containers.
	setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
	// Set $TMPDIR.
	setenv("TMPDIR", "/tmp", 1);
	// Set other envs.
	for (int i = 0; true; i += 2) {
		if (container->env[i] == NULL) {
			break;
		}
		setenv(container->env[i], container->env[i + 1], 1);
	}
}
// Run after init_container().
static void setup_binfmt_misc(const struct CONTAINER *container)
{
	/*
	 * For running multi-arch container.
	 * It need the kernel support binfmt_misc.
	 */
	// Get elf magic header.
	struct MAGIC *magic = get_magic(container->cross_arch);
	// Umount container if we get an error.
	if (magic == NULL) {
		warning("{red}Error: unknown architecture or same architecture as host: %s\n\nSupported architectures: aarch64, alpha, arm, armeb, cris, hexagon, hppa, i386, loongarch64, m68k, microblaze, mips, mips64, mips64el, mipsel, mipsn32, mipsn32el, ppc, ppc64, ppc64le, riscv32, riscv64, s390x, sh4, sh4eb, sparc, sparc32plus, sparc64, x86_64, xtensa, xtensaeb{clear}\n", container->cross_arch);
		umount_container(container->container_dir);
		error(" ");
	}
	char buf[1024] = { '\0' };
	// Format: ":name:type:offset:magic:mask:interpreter:flags".
	sprintf(buf, ":%s%d:M:0:%s:%s:%s:PCF", "ruri-", container->container_id, magic->magic, magic->mask, container->qemu_path);
	// Just to make clang-tidy happy.
	free(magic);
	// This needs CONFIG_BINFMT_MISC enabled in your kernel.
	int register_fd = open("/proc/sys/fs/binfmt_misc/register", O_WRONLY | O_CLOEXEC);
	if (register_fd < 0) {
		error("{red}Error: Failed to setup binfmt_misc, check your kernel config QwQ");
	}
	// Set binfmt_misc config.
	write(register_fd, buf, strlen(buf));
	close(register_fd);
}
// Mount other mountpoints.
// Run before chroot(2).
static void mount_mountpoints(const struct CONTAINER *container)
{
	/*
	 * Mount extra_mountpoint and extra_ro_mountpoint.
	 * It will be called before chroot(2).
	 */
	if (!container->rootless) {
		// '/' should be a mountpoint in container.
		mount(container->container_dir, container->container_dir, NULL, MS_BIND, NULL);
	}
	char *mountpoint_dir = NULL;
	// Mount extra_mountpoint.
	for (int i = 0; true; i += 2) {
		if (container->extra_mountpoint[i] == NULL) {
			break;
		}
		// Set the mountpoint to mount.
		mountpoint_dir = (char *)malloc(strlen(container->extra_mountpoint[i + 1]) + strlen(container->container_dir) + 2);
		strcpy(mountpoint_dir, container->container_dir);
		strcat(mountpoint_dir, container->extra_mountpoint[i + 1]);
		trymount(container->extra_mountpoint[i], mountpoint_dir, 0);
		free(mountpoint_dir);
	}
	// Mount extra_ro_mountpoint as read-only.
	for (int i = 0; true; i += 2) {
		if (container->extra_ro_mountpoint[i] == NULL) {
			break;
		}
		// Set the mountpoint to mount.
		mountpoint_dir = (char *)malloc(strlen(container->extra_ro_mountpoint[i + 1]) + strlen(container->container_dir) + 2);
		strcpy(mountpoint_dir, container->container_dir);
		strcat(mountpoint_dir, container->extra_ro_mountpoint[i + 1]);
		trymount(container->extra_ro_mountpoint[i], mountpoint_dir, MS_RDONLY);
		free(mountpoint_dir);
	}
}
// Run chroot container.
void run_chroot_container(struct CONTAINER *container)
{
	/*
	 * It's called by main() and run_unshare_container().
	 * It will run container as the config in CONTAINER struct.
	 */
	// Ignore SIGTTIN, if we are running in the background, SIGTTIN may kill this process.
	// This code is wrote when ruri had a daemon process,
	// now even the daemon mode is removed, I still keep this code here.
	sigset_t sigs;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGTTIN);
	sigaddset(&sigs, SIGTTOU);
	sigprocmask(SIG_BLOCK, &sigs, 0);
	// Check if system runtime files are already created.
	// container_dir shoud bind-mount before chroot(2),
	// mount_host_runtime() and store_info() will be called here.
	char buf[PATH_MAX] = { '\0' };
	sprintf(buf, "%s/sys/class/input", container->container_dir);
	char *test = realpath(buf, NULL);
	if (test == NULL) {
		// Mount mountpoints.
		mount_mountpoints(container);
		// Store container info.
		if (!container->enable_unshare && container->use_rurienv) {
			store_info(container);
		}
		// If `-R` option is set, make / read-only.
		if (container->ro_root) {
			mount(container->container_dir, container->container_dir, NULL, MS_BIND | MS_REMOUNT | MS_RDONLY, NULL);
		}
		// If `-S` option is set, bind-mount /dev/, /sys/ and /proc/ from host.
		if (container->mount_host_runtime) {
			mount_host_runtime(container);
		}
	}
	// If container already mounted, sync the config.
	else {
		free(test);
		// Read container info.
		if (container->use_rurienv) {
			read_info(container, container->container_dir);
		}
	}
	// Set default command for exec().
	if (container->command[0] == NULL) {
		if (su_biany_exist(container->container_dir)) {
			container->command[0] = "/bin/su";
			container->command[1] = "-";
			container->command[2] = NULL;
		} else {
			container->command[0] = "/bin/sh";
			container->command[1] = NULL;
		}
	}
	// Check binary used.
	check_binary(container);
	// chroot(2) into container.
	chdir(container->container_dir);
	chroot(".");
	chdir("/");
	// Mount/create system runtime dir/files.
	init_container();
	// Fix /etc/mtab.
	remove("/etc/mtab");
	unlink("/etc/mtab");
	symlink("/proc/mounts", "/etc/mtab");
	// Set up cgroup limit.
	set_limit(container);
	// Set up Seccomp BPF.
	if (container->enable_seccomp) {
		setup_seccomp(container);
	}
	// Drop caps.
	drop_caps(container);
	// Set envs.
	set_envs(container);
	// Fix a bug that the terminal is frozen.
	usleep(200000);
	// Set NO_NEW_PRIVS Flag.
	// It requires Linux3.5 or later.
	// It will make sudo unavailable in container.
	if (container->no_new_privs) {
		prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	}
	// Disallow raising ambient capabilities via the prctl(2) PR_CAP_AMBIENT_RAISE operation.
	prctl(PR_SET_SECUREBITS, SECBIT_NO_CAP_AMBIENT_RAISE);
	// We only need 0(stdin), 1(stdout), 2(stderr),
	// So we close the other fds to avoid security issues.
	// NOTE: this might cause unknown issues.
	for (int i = 3; i <= 10; i++) {
		close(i);
	}
	// Setup binfmt_misc.
	if (container->cross_arch != NULL) {
		setup_binfmt_misc(container);
	}
	// Fix console color.
	cprintf("{clear}");
	// Execute command in container.
	// Use exec(3) function because system(3) may be unavailable now.
	if (execvp(container->command[0], container->command) == -1) {
		// Catch exceptions.
		error("{red}Failed to execute `%s`\nexecv() returned: %d\nerror reason: %s\nNote: unset $LD_PRELOAD before running ruri might fix this{clear}\n", container->command[0], errno, strerror(errno));
	}
}
// Run chroot container.
void run_rootless_chroot_container(struct CONTAINER *container)
{
	/*
	 * It's called by run_rootless_container().
	 * It will run container as the config in CONTAINER struct.
	 *
	 * This function is modified from run_chroot_container().
	 */
	// Ignore SIGTTIN, if we are running in the background, SIGTTIN may kill this process.
	sigset_t sigs;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGTTIN);
	sigaddset(&sigs, SIGTTOU);
	sigprocmask(SIG_BLOCK, &sigs, 0);
	// Mount mountpoints.
	mount_mountpoints(container);
	// Store container info.
	if (container->use_rurienv) {
		store_info(container);
	}
	// Set default command for exec().
	if (container->command[0] == NULL) {
		if (su_biany_exist(container->container_dir)) {
			container->command[0] = "/bin/su";
			container->command[1] = "-";
			container->command[2] = NULL;
		} else {
			container->command[0] = "/bin/sh";
			container->command[1] = NULL;
		}
	}
	// Check binary used.
	check_binary(container);
	// chroot(2) into container.
	chdir(container->container_dir);
	chroot(".");
	chdir("/");
	// Fix /etc/mtab.
	remove("/etc/mtab");
	unlink("/etc/mtab");
	symlink("/proc/mounts", "/etc/mtab");
	// Set up Seccomp BPF.
	if (container->enable_seccomp) {
		setup_seccomp(container);
	}
	// Drop caps.
	drop_caps(container);
	// Set envs.
	set_envs(container);
	// Fix a bug that the terminal is frozen.
	usleep(200000);
	// Set NO_NEW_PRIVS Flag.
	// It requires Linux3.5 or later.
	// It will make sudo unavailable in container.
	if (container->no_new_privs) {
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
	if (container->cross_arch != NULL) {
		setup_binfmt_misc(container);
	}
	// Fix console color.
	cprintf("{clear}");
	// Execute command in container.
	// Use exec(3) function because system(3) may be unavailable now.
	if (execvp(container->command[0], container->command) == -1) {
		// Catch exceptions.
		error("{red}Failed to execute `%s`\nexecv() returned: %d\nerror reason: %s\nNote: unset $LD_PRELOAD before running ruri might fix this{clear}\n", container->command[0], errno, strerror(errno));
	}
}
