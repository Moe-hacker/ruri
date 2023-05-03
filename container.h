// Enable unshare() feature.
// GNU YYDS!
#define _GNU_SOURCE
// Include header files used.
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <dirent.h>
#include <errno.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/limits.h>
#include <sys/prctl.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/un.h>
// This program need to be linked with `-lcap`.
#include <sys/capability.h>
#define INIT_VALUE -114
#ifndef __CONTAINER_DEV__
#define _CONTAINER_VERSION "1.2"
#else
#define _CONTAINER_VERSION "1.3-dev"
#endif
// Define functions.
void show_n_char(int num);
void show_greetings(void);
void show_version_info(void);
void show_helps(bool greetings);
void add_to_list(cap_value_t *list, int length, cap_value_t cap);
void del_from_list(cap_value_t *list, int length, cap_value_t cap);
void chroot_container(char *container_dir, cap_value_t drop_caplist[], bool *use_unshare, bool *no_warnings, char *init[]);
void umount_container(char *container_dir);
#ifdef __CONTAINER_DEV__
#warning "Dev version is only for the developer."
int send_msg_server(char *msg, struct sockaddr_un addr, int sockfd);
int send_msg_client(char *msg, struct sockaddr_un addr);
char *read_msg_server(struct sockaddr_un addr, int sockfd);
char *read_msg_client(struct sockaddr_un addr);
void container_daemon(void);
// Define container struct for container_daemon.
struct CONTAINER
{
    // Container info.
    char *container_dir;
    char *unshare_pid;
    // Used to determine whether the container needs to be deleted.
    unsigned int active_containers;
    struct CONTAINER *container;
};
#endif
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
