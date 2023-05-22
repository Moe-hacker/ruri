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
// Called by container_daemon(), init an unshare container in the background.
void *init_unshare_container(void *arg);
// Run after chroot(), called by run_chroot_container().
void init_container(void);
// Daemon process used to store unshare container information and init unshare container.
void container_daemon(void);
// Used for run_chroot_container, do some checks before chroot().
bool check_container(char *container_dir);
// Run unshare container, called by main().
void run_unshare_container(char *container_dir, cap_value_t drop_caplist[], bool *no_warnings, char *init[]);
// Run chroot container, called by main(), run_unshare_container() and init_unshare_container().
void run_chroot_container(char *container_dir, cap_value_t drop_caplist[], bool *no_warnings, char *init[]);
// Kill&umount container.
void umount_container(char *container_dir);
// Info of containers.
struct CONTAINERS
{
    // For container_daemon()
    char *container_dir;
    char *unshare_pid;
    char *drop_caplist[CAP_LAST_CAP + 1];
    struct CONTAINERS *container;
};
// Info of a container to create.
struct CONTAINER_INFO
{
    // For init_unshare_container() and container_daemon()
    char *container_dir;
    cap_value_t drop_caplist[CAP_LAST_CAP + 1];
    char *init_command[1024];
    // Will be ignored in init_unshare_container()
    char *unshare_pid;
};
//   ██╗ ██╗  ███████╗   ████╗   ███████╗
//  ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//  ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//  ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//  ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//   ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
