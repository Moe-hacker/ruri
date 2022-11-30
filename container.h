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
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
