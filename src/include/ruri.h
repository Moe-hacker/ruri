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
#include <linux/stat.h>
#include <linux/version.h>
#include <linux/loop.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This program need to be linked with `-lpthread` if the system uses glibc or musl.
#include <pthread.h>
// This program need to be linked with `-lseccomp`.
#include <seccomp.h>
// This program need to be linked with `-lcap`.
#include <sys/capability.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0)
#warning "This program has not been tested on Linux 3.x or earlier."
#endif
// Bool!!!
#if __STDC_VERSION__ < 202000L
#define bool _Bool
#define true ((_Bool) + 1u)
#define false ((_Bool) + 0u)
#endif
// For initializing some variables.
#define INIT_VALUE (-114)
// Limitations.
#define MAX_COMMANDS (1024)
#define MAX_ENVS (128 * 2)
#define MAX_MOUNTPOINTS (128 * 2)
// Include other headers.
#include "elf-magic.h"
#include "version.h"
// Info of a container to create.
struct __attribute__((aligned(128))) CONTAINER {
	// Container directory.
	char *container_dir;
	// Capabilities to drop.
	cap_value_t drop_caplist[CAP_LAST_CAP + 1];
	// Command for exec(2).
	char *command[MAX_COMMANDS];
	// Extra mountpoints.
	char *extra_mountpoint[MAX_MOUNTPOINTS];
	// Environment variables.
	char *env[MAX_ENVS];
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
	// Arch of cross-architecture container.
	char *cross_arch;
	// Path of QEMU binary.
	char *qemu_path;
};
// For get_magic().
#define magicof(x) (x##_magic)
#define maskof(x) (x##_mask)
struct __attribute__((aligned(16))) MAGIC {
	char *magic;
	char *mask;
};
// Warnings.
#define warning(...) fprintf(stderr, ##__VA_ARGS__)
// Show error msg and exit.
#define error(...)                                                                                                            \
	{                                                                                                                     \
		fprintf(stderr, ##__VA_ARGS__);                                                                               \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "  .^.   .^.");                                        \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "  /⋀\\_ﾉ_/⋀\\");                                      \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", " /ﾉｿﾉ\\ﾉｿ丶)|");                                      \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", " ﾙﾘﾘ >  x )ﾘ");                                       \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "ﾉノ㇏  ^ ﾉ|ﾉ");                                       \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "      ⠁⠁");                                           \
		fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "If you think something is wrong, please report at:"); \
		fprintf(stderr, "\033[4;1;38;2;254;228;208m%s\033[0m\n", "https://github.com/Moe-hacker/ruri/issues");        \
		exit(EXIT_FAILURE);                                                                                           \
	}
void register_signal(void);
void setup_seccomp(struct CONTAINER *container);
void show_version_info(void);
void show_version_code(void);
void AwA(void);
void show_helps(void);
void show_examples(void);
void add_to_caplist(cap_value_t *list, cap_value_t cap);
bool is_in_caplist(const cap_value_t *list, cap_value_t cap);
void del_from_caplist(cap_value_t *list, cap_value_t cap);
void build_caplist(cap_value_t caplist[], bool privileged, cap_value_t drop_caplist_extra[], cap_value_t keep_caplist_extra[]);
struct MAGIC *get_magic(const char *cross_arch);
void run_unshare_container(struct CONTAINER *container);
void run_chroot_container(struct CONTAINER *container);
void run_rootless_container(struct CONTAINER *container);
int trymount(const char *source, const char *target, unsigned int mountflags);
void umount_container(const char *container_dir);
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
