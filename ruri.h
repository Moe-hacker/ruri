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
#define __INIT_VALUE__ -114
// Version info.
#define __CONTAINER_VERSION__ "2.0-dev"
void show_n_spaces(int n);
void show_greetings(void);
void show_version_info(void);
void show_helps(bool greetings);
void add_to_list(cap_value_t *list, int length, cap_value_t cap);
void del_from_list(cap_value_t *list, int length, cap_value_t cap);
void *init_unshare_container(void *arg);
void run_unshare_container(char *container_dir, cap_value_t drop_caplist[], bool *no_warnings, char *init[]);
void run_chroot_container(char *container_dir, cap_value_t drop_caplist[], bool *no_warnings, char *init[]);
void umount_container(char *container_dir);
int send_msg_server(char *msg, struct sockaddr_un addr, int sockfd);
int send_msg_client(char *msg, struct sockaddr_un addr);
char *read_msg_server(struct sockaddr_un addr, int sockfd);
char *read_msg_client(struct sockaddr_un addr);
void container_daemon(void);
// Info of containers.
struct CONTAINERS
{
    // For container_daemon()
    char *container_dir;
    char *unshare_pid;
    cap_value_t drop_caplist[CAP_LAST_CAP + 1];
    struct CONTAINERS *container;
};
// Info of a container to create.
struct CONTAINER_INFO{
    // For init_unshare_container()
    char *container_dir;
    cap_value_t drop_caplist[CAP_LAST_CAP + 1];
    char *init_command[1024];
};
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
