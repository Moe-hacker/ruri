// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2023 Moe-hacker
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
#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <linux/sched.h>
#include <linux/stat.h>
// This program need to be linked with `-lpthread` on some devices.
#include <pthread.h>
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This program need to be linked with `-lcap`
#include <sys/capability.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>
// For initializing some variables.
#define INIT_VALUE (-114)
// Version info.
#define RURI_VERSION "2.0-dev"
// Limitations
#define MAX_INIT_COMMANDS 1024
#define MAX_ENVS (128 * 2)
#define MAX_MOUNTPOINTS (128 * 2)
// Used for interprocess communication.
#define SOCKET_FILE "ruri.sock"
// Do not format this.
// clang-format off
// The real value of them is not important here.
// From client.
#define FROM_CLIENT__TEST_MESSAGE            "Nya?"
#define FROM_CLIENT__KILL_A_CONTAINER        "0x01"
#define FROM_CLIENT__REGISTER_A_CONTAINER    "0x02"
#define FROM_CLIENT__KILL_DAEMON             "0x03"
#define FROM_CLIENT__GET_PS_INFO             "0x04"
#define FROM_CLIENT__IS_INIT_ACTIVE          "0x05"
#define FROM_CLIENT__INIT_COMMAND            "0x06"
#define FROM_CLIENT__END_OF_INIT_COMMAND     "0x07"
#define FROM_CLIENT__CAP_TO_DROP             "0x08"
#define FROM_CLIENT__END_OF_CAP_TO_DROP      "0x09"
// From subprocess of rurid.
#define FROM_PTHREAD__INIT_PROCESS_DIED      "0x0a"
#define FROM_PTHREAD__UNSHARE_CONTAINER_PID  "0x0b"
#define FROM_PTHREAD__CAP_TO_DROP            "0x0c"
#define FROM_PTHREAD__END_OF_CAP_TO_DROP     "0x0d"
// From rurid.
#define FROM_DAEMON__TEST_MESSAGE            "Nya!"
#define FROM_DAEMON__UNSHARE_CONTAINER_PID   "0x0e"
#define FROM_DAEMON__CONTAINER_KILLED        "0x0f"
#define FROM_DAEMON__CONTAINER_NOT_RUNNING   "0x10"
#define FROM_DAEMON__CONTAINER_IS_ACTIVE     "0x11"
#define FROM_DAEMON__CONTAINER_IS_NOT_ACTIVE "0x12"
#define FROM_DAEMON__INIT_IS_ACTIVE          "0x13"
#define FROM_DAEMON__INIT_IS_NOT_ACTIVE      "0x14"
#define FROM_DAEMON__END_OF_PS_INFO          "0x15"
// clang-format on
// Info of containers.
struct CONTAINERS
{
  // For container_daemon()
  char *container_dir;
  // For write(), we define it as char*.
  char *unshare_pid;
  char *drop_caplist[CAP_LAST_CAP + 1];
  // TODO(Moe-hacker)
  char *env[MAX_ENVS];
  // TODO(Moe-hacker)
  char *mountpoint[MAX_MOUNTPOINTS];
  struct CONTAINERS *container;
};
// Info of a container to create.
struct CONTAINER_INFO
{
  // For daemon_init_unshare_container() and container_daemon()
  char *container_dir;
  cap_value_t drop_caplist[CAP_LAST_CAP + 1];
  char *init_command[MAX_INIT_COMMANDS];
  // Mount before chroot()
  // TODO(Moe-hacker)
  char *mountpoint[MAX_MOUNTPOINTS];
  char *env[MAX_ENVS];
  // Only be used in container_daemon()
  // For setns(), we define it as char*.
  char *unshare_pid;
};
// Function list.
void error(char *msg);
void show_greetings(void);
void show_version_info(void);
void show_helps(bool greetings);
void add_to_list(cap_value_t *list, int length, cap_value_t cap);
void del_from_list(cap_value_t *list, int length, cap_value_t cap);
struct CONTAINERS *add_node(char *container_dir, char *unshare_pid, char *drop_caplist[CAP_LAST_CAP + 1], char *env[MAX_ENVS], char *mountpoint[MAX_MOUNTPOINTS], struct CONTAINERS *container);
struct CONTAINERS *read_node(char *container_dir, struct CONTAINERS *container);
struct CONTAINERS *del_container(char *container_dir, struct CONTAINERS *container);
bool container_active(char *container_dir, struct CONTAINERS *container);
ssize_t send_msg_server(char *msg, struct sockaddr_un addr, int sockfd);
ssize_t send_msg_client(char *msg, struct sockaddr_un addr);
char *read_msg_server(struct sockaddr_un addr, int sockfd);
char *read_msg_client(struct sockaddr_un addr);
void read_all_nodes(struct CONTAINERS *container, struct sockaddr_un addr, int sockfd);
int container_ps(void);
int kill_daemon(void);
int test_daemon(void);
void umount_all_containers(struct CONTAINERS *container);
void *daemon_init_unshare_container(void *arg);
void init_container(void);
int container_daemon(void);
bool check_container(char *container_dir);
pid_t init_unshare_container(bool no_warnings);
pid_t join_ns_from_daemon(struct CONTAINER_INFO *container_info, struct sockaddr_un addr, bool no_warnings);
int run_unshare_container(struct CONTAINER_INFO *container_info, bool no_warnings);
void run_chroot_container(struct CONTAINER_INFO *container_info, bool no_warnings);
void umount_container(char *container_dir);
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
