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
 *
 */
// Enable Linux features.
#ifndef __linux__
#error "This program is only for linux."
#else
#define _GNU_SOURCE
#endif
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <linux/sched.h>
#include <linux/securebits.h>
#include <linux/version.h>
#include <linux/loop.h>
#include <sys/mount.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/sendfile.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This program need to be linked with `-lseccomp`.
#include <seccomp.h>
// This program need to be linked with `-lcap`.
#include <sys/capability.h>
// Nullability attributes.
#ifndef _Nullable
#define _Nullable
#endif
#ifndef _Nonnull
#define _Nonnull
#endif
// We redefine CAP_LAST_CAP to 114,
// because for kernel in the fulture, there may be more capabilities than today.
#undef CAP_LAST_CAP
#define CAP_LAST_CAP 114
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0)
#warning "This program has not been tested on Linux 3.x or earlier."
#endif
// Bool!!!
#if __STDC_VERSION__ < 202000L
#ifndef bool
#define bool _Bool
#define true ((_Bool) + 1u)
#define false ((_Bool) + 0u)
#endif
#endif
// For initializing some variables.
#define INIT_VALUE (-114)
// Limitations.
#define MAX_COMMANDS (1024)
#define MAX_ENVS (512 * 2)
#define MAX_MOUNTPOINTS (512 * 2)
// Include other headers.
#include "elf-magic.h"
#include "version.h"
#include "k2v.h"
#include "cprintf.h"
// Info of a container to create.
struct __attribute__((aligned(128))) CONTAINER {
	// Container directory.
	char *_Nonnull container_dir;
	// Capabilities to drop.
	cap_value_t drop_caplist[CAP_LAST_CAP + 1];
	// Command for exec(2).
	char *_Nullable command[MAX_COMMANDS];
	// Extra mountpoints.
	char *_Nullable extra_mountpoint[MAX_MOUNTPOINTS];
	// Extra read-only mountpoints.
	char *_Nullable extra_ro_mountpoint[MAX_MOUNTPOINTS];
	// Environment variables.
	char *_Nullable env[MAX_ENVS];
	// Set NO_NEW_PRIV bit.
	bool no_new_privs;
	// Enable built-in seccomp profile.
	bool enable_seccomp;
	// Do not show warnings.
	bool no_warnings;
	// Unshare container.
	bool enable_unshare;
	// Useless rootless container support.
	bool rootless;
	// Mount host runtime.
	bool mount_host_runtime;
	// Container pid for setns(2).
	pid_t ns_pid;
	// Arch of multi-architecture container.
	char *_Nullable cross_arch;
	// Path of QEMU binary.
	char *_Nullable qemu_path;
	// Do not store .rurienv file.
	bool use_rurienv;
	// Mount / as read-only.
	bool ro_root;
	// Cpuset.
	char *_Nullable cpuset;
	// Memory.
	char *_Nullable memory;
	// A number based on the time when creating container.
	int container_id;
	// Do not create runtime directory.
	bool just_chroot;
	// Work directory.
	char *_Nullable work_dir;
};
// For get_magic().
#define magicof(x) (x##_magic)
#define maskof(x) (x##_mask)
struct __attribute__((aligned(16))) MAGIC {
	char *_Nonnull magic;
	char *_Nonnull mask;
};
// For get_idmap().
struct __attribute__((aligned(32))) ID_MAP {
	uid_t uid;
	uid_t uid_lower;
	uid_t uid_count;
	gid_t gid;
	gid_t gid_lower;
	gid_t gid_count;
};
// Warnings.
#define warning(...) cfprintf(stderr, ##__VA_ARGS__)
// Show error msg and exit.
#define error(...)                                                                                           \
	{                                                                                                    \
		cfprintf(stderr, ##__VA_ARGS__);                                                             \
		cfprintf(stderr, "{base}%s{clear}\n", "  .^.   .^.");                                        \
		cfprintf(stderr, "{base}%s{clear}\n", "  /⋀\\_ﾉ_/⋀\\");                                      \
		cfprintf(stderr, "{base}%s{clear}\n", " /ﾉｿﾉ\\ﾉｿ丶)|");                                      \
		cfprintf(stderr, "{base}%s{clear}\n", " ﾙﾘﾘ >  x )ﾘ");                                       \
		cfprintf(stderr, "{base}%s{clear}\n", "ﾉノ㇏  ^ ﾉ|ﾉ");                                       \
		cfprintf(stderr, "{base}%s{clear}\n", "      ⠁⠁");                                           \
		cfprintf(stderr, "{base}%s{clear}\n", "RURI ERROR MESSAGE");                                 \
		cfprintf(stderr, "{base}%s{clear}\n", "If you think something is wrong, please report at:"); \
		cfprintf(stderr, "\033[4m{base}%s{clear}\n", "https://github.com/Moe-hacker/ruri/issues");   \
		exit(114);                                                                                   \
	}
// Log system.
#if defined(RURI_DEBUG)
#define log(...)                                                                                                                      \
	{                                                                                                                             \
		struct timeval tv;                                                                                                    \
		gettimeofday(&tv, NULL);                                                                                              \
		cfprintf(stdout, "{green}[%ld.%06ld] in %s() in %s line %d:\n", tv.tv_sec, tv.tv_usec, __func__, __FILE__, __LINE__); \
		cfprintf(stdout, ##__VA_ARGS__)                                                                                       \
	}
#else
#define log(...) \
	{        \
	}
#endif
// Shared functions.
void register_signal(void);
void setup_seccomp(const struct CONTAINER *_Nonnull container);
void show_version_info(void);
void show_version_code(void);
void AwA(void);
void show_helps(void);
void show_examples(void);
void store_info(const struct CONTAINER *_Nonnull container);
struct CONTAINER *read_info(struct CONTAINER *_Nullable container, const char *_Nonnull container_dir);
void add_to_caplist(cap_value_t *_Nonnull list, cap_value_t cap);
bool is_in_caplist(const cap_value_t *_Nonnull list, cap_value_t cap);
void del_from_caplist(cap_value_t *_Nonnull list, cap_value_t cap);
void build_caplist(cap_value_t caplist[], bool privileged, cap_value_t drop_caplist_extra[], cap_value_t keep_caplist_extra[]);
struct MAGIC *get_magic(const char *_Nonnull cross_arch);
void run_unshare_container(struct CONTAINER *_Nonnull container);
char *container_info_to_k2v(const struct CONTAINER *_Nonnull container);
void run_chroot_container(struct CONTAINER *_Nonnull container);
void run_rootless_container(struct CONTAINER *_Nonnull container);
void run_rootless_chroot_container(struct CONTAINER *_Nonnull container);
int trymount(const char *_Nonnull source, const char *_Nonnull target, unsigned int mountflags);
void umount_container(const char *_Nonnull container_dir);
void read_config(struct CONTAINER *_Nonnull container, const char *_Nonnull path);
void set_limit(const struct CONTAINER *_Nonnull container);
struct ID_MAP get_idmap(uid_t uid, gid_t gid);
void container_ps(char *_Nonnull container_dir);
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
