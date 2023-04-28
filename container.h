//  ██╗ ██╗  ██╗ ██╗  ██╗
// ████████╗ ██║ ██║  ██║
// ╚██╔═██╔╝ ██║ ███████║
// ████████╗ ╚═╝ ██╔══██║
// ╚██╔═██╔╝ ██╗ ██║  ██║
//  ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝
// ╔═╝  ║ ║╔═╝╔═║╔═ ╔═╝╔═║  ╔═╝╝║  ╔═╝
// ║    ╔═║╔═╝╔═║║ ║╔═╝╔╔╝  ╔═╝║║  ╔═╝
// ══╝  ╝ ╝══╝╝ ╝══ ══╝╝ ╝  ╝  ╝══╝══╝
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
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/socket.h>
// This program need to be linked with `-lcap`.
#include <sys/capability.h>
#define INIT_VALUE -114
#define _CONTAINER_VERSION "1.2"
// Define functions.
void show_n_char(int num);
void show_greetings(void);
void show_version_info(void);
void show_helps(bool greetings);
void add_to_list(cap_value_t *list, int length, cap_value_t cap);
void del_from_list(cap_value_t *list, int length, cap_value_t cap);
void chroot_container(char *container_dir, cap_value_t drop_caplist[], bool *use_unshare, bool *no_warnings, char *init[]);
void umount_container(char *container_dir);
void container_daemon(void);
// Define container struct for container_daemon.
struct CONTAINER
{
    char *container_dir;
    char *is_unshare;
    char *unshare_pid;
    unsigned int active_containers;
    struct CONTAINER *container;
};
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
