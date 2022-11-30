// ██╗ ██╗  ██╗ ██╗  ██╗
//████████╗ ██║ ██║  ██║
//╚██╔═██╔╝ ██║ ███████║
//████████╗ ╚═╝ ██╔══██║
//╚██╔═██╔╝ ██╗ ██║  ██║
// ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝
//╔═╝  ║ ║╔═╝╔═║╔═ ╔═╝╔═║  ╔═╝╝║  ╔═╝
//║    ╔═║╔═╝╔═║║ ║╔═╝╔╔╝  ╔═╝║║  ╔═╝
//══╝  ╝ ╝══╝╝ ╝══ ══╝╝ ╝  ╝  ╝══╝══╝
//Enable unshare() feature.
//GNU YYDS!
#define _GNU_SOURCE
//Include header files used.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <dirent.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/limits.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//This program need to be linked with `-lcap`.
#include <sys/capability.h>

/////////////////////////////////
//Only for debugging,this should be removed.
#define USE_UNSHARE 1
#define DROP_CAPS 1
#define DROP_MORE_CAPS 0
///////////////////////////////

//Some definitions of flags,set 0 to disable and 1 to enable.
//But do not remove definitions without editing container.c.
//Caps to drop from docker default containers.
//If you don't know the meaning of these caps,just set their value to 1.
#define DROP_CAP_SYS_ADMIN 1
#define DROP_CAP_SYS_MODULE 1
#define DROP_CAP_SYS_RAWIO 1
#define DROP_CAP_SYS_PACCT 1
#define DROP_CAP_SYS_NICE 1
#define DROP_CAP_SYS_RESOURCE 1
#define DROP_CAP_SYS_TTY_CONFIG 1
#define DROP_CAP_AUDIT_CONTROL 1
#define DROP_CAP_MAC_OVERRIDE 1
#define DROP_CAP_MAC_ADMIN 1
#define DROP_CAP_NET_ADMIN 1
#define DROP_CAP_SYSLOG 1
#define DROP_CAP_DAC_READ_SEARCH 1
#define DROP_CAP_LINUX_IMMUTABLE 1
#define DROP_CAP_NET_BROADCAST 1
#define DROP_CAP_IPC_LOCK 1
#define DROP_CAP_IPC_OWNER 1
#define DROP_CAP_SYS_PTRACE 1
#define DROP_CAP_SYS_BOOT 1
#define DROP_CAP_LEASE 1
#define DROP_CAP_WAKE_ALARM 1
#define DROP_CAP_BLOCK_SUSPEND 1
//This is usually not necessary.
//Do not change these values or you might run into problems.
#define DROP_CAP_SYS_CHROOT 1
#define DROP_CAP_SETPCAP 1
#define DROP_CAP_MKNOD 1
#define DROP_CAP_AUDIT_WRITE 1
#define DROP_CAP_CHOWN 0
#define DROP_CAP_NET_RAW 0
#define DROP_CAP_DAC_OVERRIDE 0
#define DROP_CAP_FOWNER 0
#define DROP_CAP_FSETID 0
#define DROP_CAP_KILL 0
#define DROP_CAP_SETGID 0
#define DROP_CAP_NET_BIND_SERVICE 0
#define DROP_CAP_SETFCAP 0
// ██╗ ██╗  ███████╗   ████╗   ███████╗
//████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
// ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝