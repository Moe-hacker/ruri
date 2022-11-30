//Enable unshare() feature.
//GNU YYDS!
#define _GNU_SOURCE
//Include headers used.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/limits.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//need to be linked with `-lcap`.
#include <sys/capability.h>
//Only for debugging,should be removed.
#define USE_UNSHARE 1
#define DROP_CAPS 1
//For debugging,set it to `./a.out`.
//I will find a better way to get root permissions or use shell to implement. 
#define BINARY_PATH "./a.out"