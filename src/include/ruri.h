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
// The macro __RURI_DEV__ will enable extra logs.
// Do not uncomment it, use `-D__RURI_DEV__` to compile instead.
// #define __RURI_DEV__
//
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
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0)
#warning "This program has not been tested on Linux 3.x or earlier."
#endif
// This program need to be linked with `-lpthread` if the system uses glibc or musl.
#include <pthread.h>
#include <sched.h>
// This program need to be linked with `-lseccomp`.
#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This program need to be linked with `-lcap`.
#include <sys/capability.h>
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
// For interprocess communication.
#define SOCKET_FILE "ruri.sock"
// Include other headers.
#include "elf-magic.h"
#include "msg.h"
#include "version.h"
// Info of containers.
struct __attribute__((aligned(128))) CONTAINERS {
	cap_value_t drop_caplist[CAP_LAST_CAP + 1];
	char *container_dir;
	// For send_msg_daemon(), we define it as char*.
	char *unshare_pid;
	char *env[MAX_ENVS];
	char *mountpoint[MAX_MOUNTPOINTS];
	bool no_new_privs;
	bool enable_seccomp;
	struct CONTAINERS *next;
};
// Info of a container to create.
struct __attribute__((aligned(128))) CONTAINER_INFO {
	char *container_dir;
	cap_value_t drop_caplist[CAP_LAST_CAP + 1];
	char *command[MAX_COMMANDS];
	// Mount before chroot(2).
	char *mountpoint[MAX_MOUNTPOINTS];
	char *env[MAX_ENVS];
	bool no_new_privs;
	bool enable_seccomp;
	bool no_warnings;
	bool use_unshare;
	bool rootless;
	// Mount
	bool host_runtime_dir;
	// Only be used in ruri_daemon().
	// For setns(2), we define it as char*.
	char *unshare_pid;
	// For cross-architecture containers.
	char *cross_arch;
	char *qemu_path;
};
// For get_magic().
#define magicof(x) (x##_magic)
#define maskof(x) (x##_mask)
struct MAGIC {
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
void setup_seccomp(struct CONTAINER_INFO *container_info);
void show_version_info(void);
void show_version_code(void);
void AwA(void);
void show_helps(void);
void show_examples(void);
void add_to_list(cap_value_t *list, cap_value_t cap);
bool is_in_list(const cap_value_t *list, cap_value_t cap);
void del_from_list(cap_value_t *list, cap_value_t cap);
ssize_t send_msg_daemon(const char *msg, struct sockaddr_un addr, int sockfd);
ssize_t send_msg_client(const char *msg, struct sockaddr_un addr);
ssize_t read_msg_daemon(char *buf, struct sockaddr_un addr, int sockfd);
ssize_t read_msg_client(char *buf, struct sockaddr_un addr);
void container_ps(void);
void kill_daemon(void);
int connect_to_daemon(struct sockaddr_un *addr);
void ruri_daemon(void);
struct MAGIC *get_magic(const char *cross_arch);
int run_unshare_container(struct CONTAINER_INFO *container_info);
void run_chroot_container(struct CONTAINER_INFO *container_info);
void umount_container(const char *container_dir);
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
