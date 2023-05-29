// SPDX-License-Identifier: MIT
/*
 * This file is part of ruri.
 *  MIT License
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
 */
// Enable Linux features.
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sched.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
// This program need to be linked with `-lpthread` on some devices.
#include <pthread.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/limits.h>
#include <sys/prctl.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
// This program need to be linked with `-lcap`.
#include <sys/capability.h>
// For initializing some variables.
#define INIT_VALUE -114
// Version info.
#define CONTAINER_VERSION "2.0-dev"
// Info of containers.
struct CONTAINERS
{
    // For container_daemon()
    char *container_dir;
    // For setns(), we define it as char*.
    char *unshare_pid;
    char *drop_caplist[CAP_LAST_CAP + 1];
    // TODO
    // MAX:128 envs
    char *env[256];
    struct CONTAINERS *container;
};
// Info of a container to create.
struct CONTAINER_INFO
{
    // For init_unshare_container() and container_daemon()
    char *container_dir;
    cap_value_t drop_caplist[CAP_LAST_CAP + 1];
    char *init_command[1024];
    // For init_container
    char *mountpoint[256];
    // TODO
    // MAX:128 envs
    char *env[256];
    // Only be used in container_daemon()
    // For setns(), we define it as char*.
    char *unshare_pid;
};
// Function list.
// For centering output.
void show_n_spaces(int n);
// As an easter agg.
void show_greetings(void);
// For `ruri -v`.
void show_version_info(void);
// For `ruri -h`.
void show_helps(bool greetings);
// Add a cap to caplist.
void add_to_list(cap_value_t *list, int length, cap_value_t cap);
// Del a cap from caplist.
void del_from_list(cap_value_t *list, int length, cap_value_t cap);
// Add a node to CONTAINERS struct.
struct CONTAINERS *add_node(char *container_dir, char *unshare_pid, char *drop_caplist[CAP_LAST_CAP + 1], struct CONTAINERS *container);
// Return info of a container.
struct CONTAINERS *read_node(char *container_dir, struct CONTAINERS *container);
// Delete a node from CONTAINERS struct.
struct CONTAINERS *del_node(struct CONTAINERS *container);
// Delete a container from CONTAINERS struct. It will call to del_node().
struct CONTAINERS *del_container(char *container_dir, struct CONTAINERS *container);
// Check if a container is running.
bool container_active(char *container_dir, struct CONTAINERS *container);
// For daemon, send msg to socket.
int send_msg_server(char *msg, struct sockaddr_un addr, int sockfd);
// For client, send msg to socket.
int send_msg_client(char *msg, struct sockaddr_un addr);
// For daemon, return the messages have been read.
char *read_msg_server(struct sockaddr_un addr, int sockfd);
// For client, return the messages have been read.
char *read_msg_client(struct sockaddr_un addr);
// TODO
//  For container_ps().
void read_all_nodes(struct CONTAINERS *container);
// TODO
// List all running unshare containers.
void container_ps(void);
// TODO
// Send kill message to daemon.
void kill_daemon(void);
// TODO
// For container_daemon(), kill and umount all containers.
void umount_all_containers(struct CONTAINERS *container);
// Called by container_daemon(), init an unshare container in the background.
void *init_unshare_container(void *arg);
// Run after chroot(), called by run_chroot_container().
void init_container(void);
// Daemon process used to store unshare container information and init unshare container.
void container_daemon(void);
// TODO :IT should be run in main()
// Used for run_chroot_container, do some checks before chroot().
bool check_container(char *container_dir);
// Run unshare container, called by main().
void run_unshare_container(struct CONTAINER_INFO *container_info, bool *no_warnings);
// Run chroot container, called by main(), run_unshare_container() and init_unshare_container().
void run_chroot_container(struct CONTAINER_INFO *container_info, bool *no_warnings);
// Kill&umount container.
void umount_container(char *container_dir);
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
