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
 */
#include "ruri.h"
// For `ruri -l`
void container_ps()
{
	/*
	 * It will connect to daemon and list running containers.
	 * If daemon is not running, just show error and exit.
	 */
	// Set socket address.
	struct sockaddr_un addr;
	if (connect_to_daemon(&addr) != 0) {
		error("Daemon not running.");
	}
	// Message to read.
	char msg[MSG_BUF_SIZE] = { '\000' };
	// Clear buf.
	memset(msg, '\000', MSG_BUF_SIZE);
	// Daemon will return the info of running containers.
	send_msg_client(FROM_CLIENT__GET_PS_INFO, addr);
	printf("\033[1;38;2;254;228;208mCONTAINER_DIR\033[1;38;2;152;245;225m:\033[1;38;2;123;104;238mUNSHARE_PID\n");
	printf("\033[1;38;2;152;245;225m=========================\n");
	while (true) {
		read_msg_client(msg, addr);
		// End of container info.
		if (strcmp(msg, FROM_DAEMON__END_OF_PS_INFO) == 0) {
			break;
		}
		// Print the received container info.
		printf("\033[1;38;2;254;228;208m%s", msg);
		read_msg_client(msg, addr);
		printf("\033[1;38;2;152;245;225m:\033[1;38;2;123;104;238m%s\n", msg);
	}
}
// For `ruri -K`
void kill_daemon()
{
	/*
	 * It will just send `kill` to daemon.
	 * If daemon is not running, show error and exit.
	 */
	// Set socket address.
	struct sockaddr_un addr;
	if (connect_to_daemon(&addr) != 0) {
		error("Daemon not running");
	}
	// daemon will kill itself after received this message.
	send_msg_client(FROM_CLIENT__KILL_DAEMON, addr);
}
// Kill&umount container.
void umount_container(char *container_dir)
{
	/*
	 * It will try to connect to daemon, and daemon will kill daemon_init_unshare_container() process of container if the container is running.
	 * Then it will umount(2) container_dir and other directories in it.
	 */
	// Set socket address.
	struct sockaddr_un addr;
	char msg[MSG_BUF_SIZE] = { '\000' };
	// Clear buf.
	memset(msg, '\000', MSG_BUF_SIZE);
	char mountpoint[MAX_MOUNTPOINTS / 2][PATH_MAX];
	mountpoint[0][0] = '\0';
	if (connect_to_daemon(&addr) != 0) {
		printf("\033[33mWarning: seems that container daemon is not running nya~\033[0m\n");
	} else {
		// Kill the container from daemon.
		send_msg_client(FROM_CLIENT__KILL_A_CONTAINER, addr);
		send_msg_client(container_dir, addr);
		read_msg_client(msg, addr);
		if (strcmp(msg, FROM_DAEMON__CONTAINER_NOT_RUNNING) == 0) {
			fprintf(stderr, "\033[33mWarning: seems that container is not running nya~\033[0m\n");
		} else {
			read_msg_client(msg, addr);
			// Get other mountpoints.
			for (int i = 0; true; i++) {
				read_msg_client(msg, addr);
				if (strcmp(msg, FROM_DAEMON__END_OF_MOUNTPOINT) == 0) {
					break;
				}
				strcpy(mountpoint[i], msg);
				mountpoint[i + 1][0] = '\0';
			}
		}
	}
	// Get path to umount.
	char sys_dir[PATH_MAX];
	char proc_dir[PATH_MAX];
	char dev_dir[PATH_MAX];
	char to_umountpoint[PATH_MAX];
	strcpy(sys_dir, container_dir);
	strcpy(proc_dir, container_dir);
	strcpy(dev_dir, container_dir);
	strcat(sys_dir, "/sys");
	strcat(proc_dir, "/proc");
	strcat(dev_dir, "/dev");
	printf("\033[1;38;2;254;228;208mUmount container.\n");
	// Umount other mountpoints.
	for (int i = 0; true; i++) {
		if (mountpoint[i][0] != 0) {
			strcpy(to_umountpoint, container_dir);
			strcat(to_umountpoint, mountpoint[i]);
			for (int j = 0; j < 10; j++) {
				umount2(to_umountpoint, MNT_DETACH | MNT_FORCE);
				umount(to_umountpoint);
				usleep(20000);
			}
		} else {
			break;
		}
	}
	// Force umount system runtime directories for 10 times.
	for (int i = 1; i < 10; i++) {
		umount2(sys_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(dev_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(proc_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(container_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
	}
}