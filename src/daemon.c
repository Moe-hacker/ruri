// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2024 Moe-hacker
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
#include "include/ruri.h"
// Add a node to CONTAINERS struct.
static struct CONTAINERS *register_container(struct CONTAINERS *container, struct CONTAINER_INFO *info)
{
	/*
	 * Use malloc(3) to request the memory of the node and then add container info to node.
	 * If current node is already used, try the next one.
	 * The last ->next node will always be NULL.
	 */
	struct CONTAINERS **node = &container;
	while (true) {
		// If current node is NULL, add container info here.
		if (*node == NULL) {
			// Request memory of container struct.
			*node = (struct CONTAINERS *)malloc(sizeof(struct CONTAINERS));
			// Add info of container.
			(*node)->container_dir = strdup(info->container_dir);
			(*node)->unshare_pid = strdup(info->unshare_pid);
			(*node)->no_new_privs = info->no_new_privs;
			(*node)->enable_seccomp = info->enable_seccomp;
			for (int i = 0; i < (CAP_LAST_CAP + 1); i++) {
				if (info->drop_caplist[i] == INIT_VALUE) {
					(*node)->drop_caplist[i] = INIT_VALUE;
					// for() loop ends here.
					break;
				}
				(*node)->drop_caplist[i] = info->drop_caplist[i];
			}
			for (int i = 0; i < MAX_ENVS; i++) {
				if (info->env[i] == NULL) {
					(*node)->env[i] = NULL;
					// for() loop ends here.
					break;
				}
				(*node)->env[i] = malloc(sizeof(char) * (strlen(info->env[i]) + 1));
				strcpy((*node)->env[i], info->env[i]);
			}
			for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
				if (info->mountpoint[i] == NULL) {
					(*node)->mountpoint[i] = NULL;
					// for() loop ends here.
					break;
				}
				(*node)->mountpoint[i] = malloc(sizeof(char) * (strlen(info->mountpoint[i]) + 1));
				strcpy((*node)->mountpoint[i], info->mountpoint[i]);
			}
			(*node)->next = NULL;
			// Function ends here.
			return container;
		}
		// Goto -> next node.
		node = &((*node)->next);
	}
}
// Return info of a container.
static struct CONTAINERS *get_container_info(char *container_dir, struct CONTAINERS *container)
{
	/*
	 * It will return the node that matches the container_dir.
	 * NULL pointer will be returned if reaching the end of all nodes.
	 * However, as container_active() will be run before it to check if container's running, NULL pointer will never be returned.
	 */
	struct CONTAINERS **node = &container;
	while (true) {
		if (*node != NULL) {
			// If container matches container_dir.
			if (strcmp((*node)->container_dir, container_dir) == 0) {
				// Function ends here.
				return *node;
			}
			// If not, try the next node.
			node = &((*node)->next);
		} else {
			// Will never be run.
			return NULL;
		}
	}
}
// Delete a container from CONTAINERS struct.
static struct CONTAINERS *deregister_container(char *container_dir, struct CONTAINERS *container)
{
	/*
	 * If container is a NULL pointer, just quit, but this will never happen.
	 * Or it will find the node that matching container_dir , free(3) its memory and use the next node to overwrite it.
	 * NULL pointer will be returned if reached the end of all nodes.
	 * However, as container_active() will be run before it to check if container's running, NULL pointer will never be returned.
	 */
	struct CONTAINERS **node = &container;
	while (true) {
		// It will never be true.
		if (*node == NULL) {
			return container;
		}
		// If container is the struct to delete.
		if (strcmp((*node)->container_dir, container_dir) == 0) {
			struct CONTAINERS *next_node = (*node)->next;
			free((*node));
			*node = next_node;
			// Function ends here.
			return container;
		}
		// Try the next struct.
		node = &((*node)->next);
	}
}
// Check if a container is running.
static bool container_active(char *container_dir, struct CONTAINERS *container)
{
	/*
	 * If there's a node that matches container_dir, it will return true.
	 * Or it will return false.
	 * It's used to determine whether a container is running.
	 */
	struct CONTAINERS **node = &container;
	while (true) {
		// Reached the end of container struct.
		if (*node == NULL) {
			return false;
		}
		// If container matches container_dir.
		if (strcmp((*node)->container_dir, container_dir) == 0) {
			return true;
		}
		// If not, try the next struct.
		node = &((*node)->next);
	}
}
// For container_ps().
static void read_all_nodes(struct CONTAINERS *container, struct sockaddr_un addr, int sockfd)
{
	/*
	 * It will read all nodes in container struct and send them to ruri.
	 * If it reaches the end of container struct, send `endps`.
	 */
	struct CONTAINERS **node = &container;
	while (true) {
		// Reached the end of container struct.
		if (*node == NULL) {
			send_msg_daemon(FROM_DAEMON__END_OF_PS_INFO, addr, sockfd);
			return;
		}
		// Send info to ruri.
		send_msg_daemon((*node)->container_dir, addr, sockfd);
		send_msg_daemon((*node)->unshare_pid, addr, sockfd);
		// Read the next node.
		node = &((*node)->next);
	}
}
// For ruri_daemon(), kill & umount all containers.
static void umount_all_containers(struct CONTAINERS *container)
{
	/*
	 * Kill and umount all containers.
	 * ruri_daemon() will exit after calling to this function, so free(3) is needless here.
	 */
	struct CONTAINERS **node = &container;
	while (true) {
		// Reached the end of container struct.
		if ((*node) == NULL) {
			return;
		}
		kill(atoi((*node)->unshare_pid), SIGKILL);
		// Umount other mountpoints.
		char buf[PATH_MAX];
		for (int i = 0; true; i += 2) {
			if ((*node)->mountpoint[i] != NULL) {
				strcpy(buf, (*node)->container_dir);
				strcat(buf, (*node)->mountpoint[i + 1]);
				for (int j = 0; j < 10; j++) {
					umount2(buf, MNT_DETACH | MNT_FORCE);
					umount(buf);
				}
			} else {
				break;
			}
		}
		// Get path to umount.
		char sys_dir[PATH_MAX];
		char proc_dir[PATH_MAX];
		char dev_dir[PATH_MAX];
		strcpy(sys_dir, (*node)->container_dir);
		strcpy(proc_dir, (*node)->container_dir);
		strcpy(dev_dir, (*node)->container_dir);
		strcat(sys_dir, "/sys");
		strcat(proc_dir, "/proc");
		strcat(dev_dir, "/dev");
		// Force umount all directories for 10 times.
		for (int i = 1; i < 10; i++) {
			umount2(sys_dir, MNT_DETACH | MNT_FORCE);
			umount2(dev_dir, MNT_DETACH | MNT_FORCE);
			umount2(proc_dir, MNT_DETACH | MNT_FORCE);
			umount2((*node)->container_dir, MNT_DETACH | MNT_FORCE);
		}
		node = &((*node)->next);
	}
}
// For daemon, init an unshare container in the background.
static void *daemon_init_unshare_container(void *arg)
{
	/*
	 * It is called as a child process of ruri_daemon().
	 * It will call to unshare() and send unshare_pid after fork(2) and other information to daemon.
	 * and call to run_chroot_container() to exec init command.
	 * Note that on devices that has pid ns enabled, if init process died, all processes in the container will be die.
	 */
	// pthread_create() only allows one argument.
	struct CONTAINER_INFO *container_info = (struct CONTAINER_INFO *)arg;
	// Try to create namespaces with unshare(2), no warnings to show because daemon will be run in the background.
	unshare(CLONE_NEWNS);
	unshare(CLONE_NEWUTS);
	unshare(CLONE_NEWIPC);
	unshare(CLONE_NEWPID);
	unshare(CLONE_NEWCGROUP);
	unshare(CLONE_NEWTIME);
	unshare(CLONE_SYSVSEM);
	unshare(CLONE_FILES);
	unshare(CLONE_FS);
	// Fork itself into namespace.
	// This can fix `can't fork: out of memory` issue.
	pid_t unshare_pid = fork();
	if (unshare_pid > 0) {
		char *container_dir = strdup(container_info->container_dir);
		// Set socket address.
		struct sockaddr_un addr;
		connect_to_daemon(&addr);
		char container_pid[1024];
		sprintf(container_pid, "%d", unshare_pid);
		// Send info of container back.
		send_msg_client(FROM_PTHREAD__REGISTER_CONTAINER, addr);
		// Pid of unshare container.
		// For setns(2).
		send_msg_client(FROM_PTHREAD__UNSHARE_CONTAINER_PID, addr);
		send_msg_client(container_pid, addr);
		// Container directory.
		send_msg_client(FROM_PTHREAD__CONTAINER_DIR, addr);
		send_msg_client(container_info->container_dir, addr);
		// Capabilities to drop.
		send_msg_client(FROM_PTHREAD__CAP_TO_DROP, addr);
		for (int i = 0; i < CAP_LAST_CAP; i++) {
			if (container_info->drop_caplist[i] == INIT_VALUE) {
				break;
			}
			send_msg_client(cap_to_name(container_info->drop_caplist[i]), addr);
		}
		send_msg_client(FROM_PTHREAD__END_OF_CAP_TO_DROP, addr);
		// Other mountpoints.
		send_msg_client(FROM_PTHREAD__MOUNTPOINT, addr);
		for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
			if (container_info->mountpoint[i] == NULL) {
				break;
			}
			send_msg_client(container_info->mountpoint[i], addr);
		}
		send_msg_client(FROM_PTHREAD__END_OF_MOUNTPOINT, addr);
		// Envs.
		send_msg_client(FROM_PTHREAD__ENV, addr);
		for (int i = 0; i < MAX_ENVS; i++) {
			if (container_info->env[i] == NULL) {
				break;
			}
			send_msg_client(container_info->env[i], addr);
		}
		send_msg_client(FROM_PTHREAD__END_OF_ENV, addr);
		// no_new_privs and seccomp stat.
		if (container_info->no_new_privs) {
			send_msg_client(FROM_PTHREAD__NO_NEW_PRIVS_TRUE, addr);
		} else {
			send_msg_client(FROM_PTHREAD__NO_NEW_PRIVS_FALSE, addr);
		}
		if (container_info->enable_seccomp) {
			send_msg_client(FROM_PTHREAD__ENABLE_SECCOMP_TRUE, addr);
		} else {
			send_msg_client(FROM_PTHREAD__ENABLE_SECCOMP_FALSE, addr);
		}
		// Fix the bug that the terminal was stuck.
		usleep(200000);
		// Fix `can't access tty` issue.
		waitpid(unshare_pid, NULL, 0);
		// If init process died.
		send_msg_client(FROM_PTHREAD__INIT_PROCESS_DIED, addr);
		send_msg_client(container_dir, addr);
		free(container_dir);
	} else if (unshare_pid == 0) {
		// Things to do next is same as a chroot container.
		container_info->no_warnings = true;
		run_chroot_container(container_info);
	}
	return 0;
}
// Get a new container_info struct.
static struct CONTAINER_INFO *new_container_info(void)
{
	struct CONTAINER_INFO *container_info = (struct CONTAINER_INFO *)malloc(sizeof(struct CONTAINER_INFO));
	container_info->command[0] = NULL;
	container_info->container_dir = NULL;
	container_info->unshare_pid = NULL;
	container_info->mountpoint[0] = NULL;
	container_info->env[0] = NULL;
	container_info->enable_seccomp = false;
	container_info->no_new_privs = false;
	container_info->drop_caplist[0] = INIT_VALUE;
	container_info->cross_arch = NULL;
	container_info->qemu_path = NULL;
	container_info->rootless = false;
	container_info->host_runtime_dir = false;
	container_info->unshare_pid = NULL;
	for (int i = 0; i < (CAP_LAST_CAP + 1); i++) {
		container_info->drop_caplist[i] = INIT_VALUE;
	}
	return container_info;
}
// Daemon process used to store unshare container information and init unshare container.
void ruri_daemon(void)
{
	/*
	 * 100% shit code at ruri_daemon.
	 * If the code is hard to write,
	 * it should be hard to read nya~
	 */
	/*
	 * How ruri creates a container:
	 * ruri checks if the daemon is running.
	 * ruri connects to the daemon and send the info of container to daemon.
	 * daemon gets info and create daemon_init_unshare() thread.
	 * daemon_init_unshare() sends the info back.
	 * daemon registers the container into CONTAINERS struct.
	 * It works, so do not change it.
	 */
	// Set process name.
	prctl(PR_SET_NAME, "rurid");
	// Ignore SIGTTIN, since daemon is running in the background, SIGTTIN may kill it.
	sigset_t sigs;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGTTIN);
	sigprocmask(SIG_BLOCK, &sigs, 0);
	// For pthread_create(3).
	pthread_t pthread_id = 0;
	// Check if we are running with root privileges.
	if (getuid() != 0) {
		error("\033[31mError: this program should be run with root privileges QwQ\n");
	}
	// Check if $LD_PRELOAD is unset.
	char *ld_preload = getenv("LD_PRELOAD");
	if ((ld_preload != NULL) && (strcmp(ld_preload, "") != 0)) {
		error("\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run QwQ\n");
	}
	// Create container struct.
	struct CONTAINERS *container = NULL;
	// Message to read.
	char msg[MSG_BUF_SIZE] = { '\0' };
	// Clear buf.
	memset(msg, '\0', MSG_BUF_SIZE * sizeof(char));
	// Container info.
	char *container_dir = NULL;
	// Info of a new container.
	struct CONTAINER_INFO *container_info = NULL;
	// Create socket.
	int sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
	if (sockfd < 0) {
		error("\033[31mError: cannot create socket QwQ\n");
	}
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	// In termux, $TMPDIR is not /tmp.
	char *tmpdir = getenv("TMPDIR");
	if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0)) {
		tmpdir = "/tmp";
	}
	// Set socket path.
	char socket_path[PATH_MAX] = { 0 };
	strcat(socket_path, tmpdir);
	strcat(socket_path, "/");
	strcat(socket_path, SOCKET_FILE);
	strcpy(addr.sun_path, socket_path);
	// Check if container daemon is already running.
	send_msg_client(FROM_CLIENT__TEST_MESSAGE, addr);
	read_msg_client(msg, addr);
	if (strcmp(FROM_DAEMON__TEST_MESSAGE, msg) == 0) {
		close(sockfd);
		error("\033[31mDaemon already running QwQ\n");
	}
	// fork(2) itself into the background.
	// It's really a daemon now, because its parent process will be init.
	pid_t pid = fork();
	if (pid > 0) {
		return;
	}
	if (pid < 0) {
		perror("fork");
		return;
	}
	// Create socket file.
	remove(socket_path);
	unlink(socket_path);
	if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0) {
		perror("bind");
		return;
	}
	listen(sockfd, 16);
	// Read message from ruri.
	while (true) {
		// Get message.
		read_msg_daemon(msg, addr, sockfd);
		// Test message, to check if daemon is active.
		if (strcmp(FROM_CLIENT__TEST_MESSAGE, msg) == 0) {
			send_msg_daemon(FROM_DAEMON__TEST_MESSAGE, addr, sockfd);
		}
		// Kill a container.
		else if (strcmp(FROM_CLIENT__KILL_A_CONTAINER, msg) == 0) {
			read_msg_daemon(msg, addr, sockfd);
			container_dir = strdup(msg);
			// Check if container is active.
			if (container_active(container_dir, container)) {
				// Kill container.
				// It will just kill init process, so on devices which has no pid ns enabled,
				// some process in container will still be alive.
				kill(atoi(get_container_info(container_dir, container)->unshare_pid), SIGKILL);
				send_msg_daemon(FROM_DAEMON__CONTAINER_KILLED, addr, sockfd);
				// Extra mountpoints will also be umounted in ruri client.
				send_msg_daemon(FROM_DAEMON__MOUNTPOINT, addr, sockfd);
				for (int i = 0; true; i += 2) {
					if (get_container_info(container_dir, container)->mountpoint[i] == NULL) {
						break;
					}
					send_msg_daemon(get_container_info(container_dir, container)->mountpoint[i + 1], addr, sockfd);
				}
				send_msg_daemon(FROM_DAEMON__END_OF_MOUNTPOINT, addr, sockfd);
				// Deregister the container.
				container = deregister_container(container_dir, container);
			} else {
				send_msg_daemon(FROM_DAEMON__CONTAINER_NOT_RUNNING, addr, sockfd);
			}
			free(container_dir);
			container_dir = NULL;
		}
		// Register a new container or send the info of an existing container to ruri.
		else if (strcmp(FROM_CLIENT__REGISTER_A_CONTAINER, msg) == 0) {
			// Ignore FROM_CLIENT__CONTAINER_DIR
			read_msg_daemon(msg, addr, sockfd);
			// Get container_dir.
			read_msg_daemon(msg, addr, sockfd);
			container_dir = strdup(msg);
			// If container is active, send unshare_pid and other info to client.
			if (container_active(container_dir, container)) {
				send_msg_daemon(FROM_DAEMON__ENV, addr, sockfd);
				for (int i = 0; i < MAX_ENVS; i++) {
					if (get_container_info(container_dir, container)->env[i] == NULL) {
						break;
					}
					send_msg_daemon(get_container_info(container_dir, container)->env[i], addr, sockfd);
				}
				send_msg_daemon(FROM_DAEMON__END_OF_ENV, addr, sockfd);
				send_msg_daemon(FROM_DAEMON__CAP_TO_DROP, addr, sockfd);
				for (int i = 0; true; i++) {
					if (get_container_info(container_dir, container)->drop_caplist[i] == INIT_VALUE) {
						break;
					}
					send_msg_daemon(cap_to_name(get_container_info(container_dir, container)->drop_caplist[i]), addr, sockfd);
				}
				send_msg_daemon(FROM_DAEMON__END_OF_CAP_TO_DROP, addr, sockfd);
				if (get_container_info(container_dir, container)->no_new_privs) {
					send_msg_daemon(FROM_DAEMON__NO_NEW_PRIVS_TRUE, addr, sockfd);
				} else {
					send_msg_daemon(FROM_DAEMON__NO_NEW_PRIVS_FALSE, addr, sockfd);
				}
				if (get_container_info(container_dir, container)->enable_seccomp) {
					send_msg_daemon(FROM_DAEMON__ENABLE_SECCOMP_TRUE, addr, sockfd);
				} else {
					send_msg_daemon(FROM_DAEMON__ENABLE_SECCOMP_FALSE, addr, sockfd);
				}
				send_msg_daemon(FROM_DAEMON__UNSHARE_CONTAINER_PID, addr, sockfd);
				send_msg_daemon(get_container_info(container_dir, container)->unshare_pid, addr, sockfd);
				free(container_dir);
				container_dir = NULL;
			}
			// If container is not active, init and register it.
			else {
				free(container_info);
				container_info = new_container_info();
				container_info->container_dir = strdup(container_dir);
				free(container_dir);
				send_msg_daemon(FROM_DAEMON__CONTAINER_NOT_RUNNING, addr, sockfd);
				// Read init command.
				read_msg_daemon(msg, addr, sockfd);
				// Get init command.
				for (int i = 0; true; i++) {
					read_msg_daemon(msg, addr, sockfd);
					if (strcmp(FROM_CLIENT__END_OF_INIT_COMMAND, msg) == 0) {
						break;
					}
					container_info->command[i] = strdup(msg);
					container_info->command[i + 1] = NULL;
				}
				if (container_info->command[0] == NULL) {
					container_info->command[0] = "/bin/sh";
					container_info->command[1] = "-c";
					container_info->command[2] = "while :;do /bin/sleep 100s;done";
					container_info->command[3] = NULL;
				}
				read_msg_daemon(msg, addr, sockfd);
				// Get caps to drop.
				for (int i = 0; true; i++) {
					read_msg_daemon(msg, addr, sockfd);
					if (strcmp(FROM_CLIENT__END_OF_CAP_TO_DROP, msg) == 0) {
						container_info->drop_caplist[i] = INIT_VALUE;
						break;
					}
					cap_from_name(msg, &container_info->drop_caplist[i]);
					container_info->drop_caplist[i + 1] = INIT_VALUE;
				}
				read_msg_daemon(msg, addr, sockfd);
				// Get mountpoints.
				for (int i = 0; true; i++) {
					read_msg_daemon(msg, addr, sockfd);
					if (strcmp(FROM_CLIENT__END_OF_MOUNTPOINT, msg) == 0) {
						break;
					}
					container_info->mountpoint[i] = strdup(msg);
					container_info->mountpoint[i + 1] = NULL;
				}
				read_msg_daemon(msg, addr, sockfd);
				// Get envs.
				for (int i = 0; true; i++) {
					read_msg_daemon(msg, addr, sockfd);
					if (strcmp(FROM_CLIENT__END_OF_ENV, msg) == 0) {
						break;
					}
					container_info->env[i] = strdup(msg);
					container_info->env[i + 1] = NULL;
				}
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_CLIENT__NO_NEW_PRIVS_TRUE, msg) == 0) {
					container_info->no_new_privs = true;
				}
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_CLIENT__ENABLE_SECCOMP_TRUE, msg) == 0) {
					container_info->enable_seccomp = true;
				}
				// Get cross-arch info.
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_CLIENT__CROSS_ARCH_TRUE, msg) == 0) {
					// Ignore FROM_CLIENT__CROSS_ARCH_INFO.
					read_msg_daemon(msg, addr, sockfd);
					// Get arch.
					read_msg_daemon(msg, addr, sockfd);
					container_info->cross_arch = strdup(msg);
					// Get qemu path.
					read_msg_daemon(msg, addr, sockfd);
					container_info->qemu_path = strdup(msg);
				} else {
					container_info->cross_arch = NULL;
					container_info->qemu_path = NULL;
				}
				// Get if we need to bind mount /dev/, /sys/ and /proc/ from host.
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_CLIENT__HOST_RUNTIME_TRUE, msg) == 0) {
					container_info->host_runtime_dir = true;
				}
				// Init container in new pthread.
				// It will send all the info of the container back to register it.
				pthread_create(&pthread_id, NULL, daemon_init_unshare_container, (void *)container_info);
			}
		}
		// Get container info from subprocess and add them to container struct.
		else if (strcmp(FROM_PTHREAD__REGISTER_CONTAINER, msg) == 0) {
			// Ignore FROM_PTHREAD__UNSHARE_CONTAINER_PID.
			read_msg_daemon(msg, addr, sockfd);
			read_msg_daemon(msg, addr, sockfd);
			free(container_info);
			container_info = new_container_info();
			container_info->unshare_pid = strdup(msg);
			// Ignore FROM_PTHREAD__CONTAINER_DIR
			read_msg_daemon(msg, addr, sockfd);
			read_msg_daemon(msg, addr, sockfd);
			container_info->container_dir = strdup(msg);
			// Ignore FROM_PTHREAD__CAP_TO_DROP
			read_msg_daemon(msg, addr, sockfd);
			// Get caps to drop.
			for (int i = 0; true; i++) {
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_PTHREAD__END_OF_CAP_TO_DROP, msg) == 0) {
					container_info->drop_caplist[i] = INIT_VALUE;
					break;
				}
				cap_from_name(msg, &container_info->drop_caplist[i]);
				container_info->drop_caplist[i + 1] = INIT_VALUE;
			}
			read_msg_daemon(msg, addr, sockfd);
			// Get mountpoints.
			for (int i = 0; true; i++) {
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_PTHREAD__END_OF_MOUNTPOINT, msg) == 0) {
					container_info->mountpoint[i] = NULL;
					break;
				}
				container_info->mountpoint[i] = strdup(msg);
			}
			read_msg_daemon(msg, addr, sockfd);
			// Get envs.
			for (int i = 0; true; i++) {
				read_msg_daemon(msg, addr, sockfd);
				if (strcmp(FROM_PTHREAD__END_OF_ENV, msg) == 0) {
					break;
				}
				container_info->env[i] = strdup(msg);
				container_info->env[i + 1] = NULL;
			}
			read_msg_daemon(msg, addr, sockfd);
			if (strcmp(FROM_PTHREAD__NO_NEW_PRIVS_TRUE, msg) == 0) {
				container_info->no_new_privs = true;
			}
			read_msg_daemon(msg, addr, sockfd);
			if (strcmp(FROM_PTHREAD__ENABLE_SECCOMP_TRUE, msg) == 0) {
				container_info->enable_seccomp = true;
			}
			// Register the container.
			container = register_container(container, container_info);
			// Send unshare_pid to ruri.
			usleep(200000);
			send_msg_daemon(FROM_DAEMON__UNSHARE_CONTAINER_PID, addr, sockfd);
			send_msg_daemon(container_info->unshare_pid, addr, sockfd);
		}
		// Kill daemon itself.
		else if (strcmp(FROM_CLIENT__KILL_DAEMON, msg) == 0) {
			umount_all_containers(container);
			// Exit daemon.
			remove(addr.sun_path);
			exit(EXIT_SUCCESS);
		}
		// Get ps info of all registered containers.
		else if (strcmp(FROM_CLIENT__GET_PS_INFO, msg) == 0) {
			read_all_nodes(container, addr, sockfd);
		}
		// If init process died, deregister the container.
		else if (strcmp(FROM_PTHREAD__INIT_PROCESS_DIED, msg) == 0) {
			read_msg_daemon(msg, addr, sockfd);
			container_dir = strdup(msg);
			if (container_active(container_dir, container)) {
				container = deregister_container(container_dir, container);
			}
		}
		// Check if init process is active.
		else if (strcmp(FROM_CLIENT__IS_INIT_ACTIVE, msg) == 0) {
			read_msg_daemon(msg, addr, sockfd);
			container_dir = strdup(msg);
			if (container_active(container_dir, container)) {
				send_msg_daemon(FROM_DAEMON__INIT_IS_ACTIVE, addr, sockfd);
			} else {
				send_msg_daemon(FROM_DAEMON__INIT_IS_NOT_ACTIVE, addr, sockfd);
			}
		}
	}
}