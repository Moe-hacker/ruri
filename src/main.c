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
#include "include/ruri.h"
// Do some checks before chroot(2),called by main().
static void check_container(const struct CONTAINER_INFO *container_info)
{
	/*
	 * It's called by main() to check if container_info is correct.
	 * It will also check the running environment.
	 * Note that it can only do basic checks,
	 * and we can't know if container_info can really run a container properly.
	 */
	// Check if container directory is given.
	if (container_info->container_dir == NULL) {
		error("\033[31mError: container directory is not set QwQ\n");
	}
	// Refuse to use `/` for container directory.
	if (strcmp(container_info->container_dir, "/") == 0) {
		error("\033[31mError: `/` is not allowed to use as a container directory QwQ\n");
	}
	// Check if we are running with root privileges.
	if (getuid() != 0 && !(container_info->rootless)) {
		error("\033[31mError: this program should be run with root privileges QwQ\n");
	}
	// Check if $LD_PRELOAD is unset.
	// If LD_PRELOAD is set, container might will not run properly.
	char *ld_preload = getenv("LD_PRELOAD");
	if ((ld_preload != NULL) && (strcmp(ld_preload, "") != 0)) {
		error("\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run QwQ\n");
	}
	// Check if container directory exists.
	DIR *direxist = opendir(container_info->container_dir);
	if (direxist == NULL) {
		error("\033[31mError: container directory does not exist QwQ\n");
	}
	closedir(direxist);
	// Check if command binary exists and is not a directory.
	char init_binary[PATH_MAX];
	strcpy(init_binary, container_info->container_dir);
	strcat(init_binary, container_info->command[0]);
	struct stat init_binary_stat;
	// lstat(3) will return -1 while the init_binary does not exist.
	if (lstat(init_binary, &init_binary_stat) != 0) {
		error("\033[31mPlease check if CONTAINER_DIRECTORY and [COMMAND [ARG]...] are correct QwQ\n");
	}
	if (S_ISDIR(init_binary_stat.st_mode)) {
		error("\033[31mCOMMAND can not be a directory QwQ\n");
	}
}
static void build_caplist(cap_value_t caplist[], int priv_level, cap_value_t drop_caplist_extra[], cap_value_t keep_caplist_extra[])
{
	/*
	 * priv_level:
	 * 0 for unprivileged, 1 for common, 2 for privileged.
	 * And the capabilities to drop is also affected by drop/keep_caplist_extra[].
	 */
	// Based on docker's default capability set.
	cap_value_t drop_caplist_common[] = { CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND, CAP_SYS_TIME, CAP_MKNOD, CAP_SYS_CHROOT };
	// I hope it will not cause bugs.
	cap_value_t drop_caplist_unprivileged[] = { CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND, CAP_SYS_CHROOT, CAP_SETPCAP, CAP_MKNOD, CAP_AUDIT_WRITE, CAP_SETFCAP, CAP_KILL, CAP_NET_BIND_SERVICE, CAP_SYS_TIME, CAP_AUDIT_READ, CAP_PERFMON, CAP_BPF, CAP_CHECKPOINT_RESTORE };
	// Set default caplist to drop.
	if (priv_level == 0) {
		for (size_t i = 0; i < (sizeof(drop_caplist_unprivileged) / sizeof(drop_caplist_unprivileged[0])); i++) {
			caplist[i] = drop_caplist_unprivileged[i];
			caplist[i + 1] = INIT_VALUE;
		}
	} else if (priv_level == 1) {
		for (size_t i = 0; i < (sizeof(drop_caplist_common) / sizeof(drop_caplist_common[0])); i++) {
			caplist[i] = drop_caplist_common[i];
			caplist[i + 1] = INIT_VALUE;
		}
	} else {
		caplist[0] = INIT_VALUE;
	}
	// Comply with drop/keep_caplist_extra[] specified.
	if (drop_caplist_extra[0] != INIT_VALUE) {
		for (int i = 0; true; i++) {
			if (drop_caplist_extra[i] == INIT_VALUE) {
				break;
			}
			add_to_list(caplist, drop_caplist_extra[i]);
		}
	}
	if (keep_caplist_extra[0] != INIT_VALUE) {
		for (int i = 0; true; i++) {
			if (keep_caplist_extra[i] != INIT_VALUE) {
				break;
			}
			del_from_list(caplist, keep_caplist_extra[i]);
		}
	}
}
static struct CONTAINER_INFO *parse_args(int argc, char **argv, struct CONTAINER_INFO *info)
{
	/*
	 * 100% shit-code here.
	 * At least it works...
	 * It has cognitive complexity of 120+, be happy reading~
	 * If the code is hard to write,
	 * it should be hard to read nya~
	 */
	// Check if arguments are given.
	if (argc <= 1) {
		fprintf(stderr, "\033[31mError: too few arguments QwQ\033[0m\n");
		show_helps();
		exit(EXIT_FAILURE);
	}
	cap_value_t keep_caplist_extra[CAP_LAST_CAP + 1] = { INIT_VALUE };
	cap_value_t drop_caplist_extra[CAP_LAST_CAP + 1] = { INIT_VALUE };
	cap_value_t cap = INIT_VALUE;
	int priv_level = 1;
	info = (struct CONTAINER_INFO *)malloc(sizeof(struct CONTAINER_INFO));
	info->enable_seccomp = false;
	info->no_new_privs = false;
	info->no_warnings = false;
	info->use_unshare = false;
	info->rootless = false;
	info->command[0] = NULL;
	info->env[0] = NULL;
	info->mountpoint[0] = NULL;
	// A very large and shit-code for() loop.
	// At least it works fine...
	for (int index = 1; index < argc; index++) {
		/**** For other options ****/
		// As an easter egg.
		if (strcmp(argv[index], "AwA") == 0) {
			AwA();
			exit(EXIT_SUCCESS);
		}
		// Show version info.
		if (strcmp(argv[index], "-v") == 0) {
			show_version_info();
			exit(EXIT_SUCCESS);
		}
		// Show version code, very useless right now.
		if (strcmp(argv[index], "-V") == 0) {
			show_version_code();
			exit(EXIT_SUCCESS);
		}
		// Start rurid.
		if (strcmp(argv[index], "-D") == 0) {
			ruri_daemon();
			exit(EXIT_SUCCESS);
		}
		// Kill rurid.
		if (strcmp(argv[index], "-K") == 0) {
			kill_daemon();
			exit(EXIT_SUCCESS);
		}
		// Show help page.
		if (strcmp(argv[index], "-h") == 0) {
			show_helps();
			exit(EXIT_SUCCESS);
		}
		// Show help page and example usage.
		if (strcmp(argv[index], "-H") == 0) {
			show_helps();
			show_examples();
			exit(EXIT_SUCCESS);
		}
		// List running unshare containers.
		if (strcmp(argv[index], "-l") == 0) {
			container_ps();
			exit(EXIT_SUCCESS);
		}
		// Check if rurid is running.
		if (strcmp(argv[index], "-t") == 0) {
			if (geteuid() != 0) {
				error("\033[31mError: this program should be run with root.\033[0m\n");
				exit(EXIT_FAILURE);
			}
			struct sockaddr_un addr;
			if (connect_to_daemon(&addr) != 0) {
				printf("\033[31mrurid is not running.\033[0m\n");
				exit(EXIT_FAILURE);
			}
			printf("\033[1;38;2;254;228;208mrurid is running.\033[0m\n");
			exit(EXIT_SUCCESS);
		}
		// Check if rurid is running, without output.
		if (strcmp(argv[index], "-T") == 0) {
			if (geteuid() != 0) {
				error("\033[31mError: this program should be run with root.\033[0m\n");
				exit(EXIT_FAILURE);
			}
			struct sockaddr_un addr;
			if (connect_to_daemon(&addr) != 0) {
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		// Umount a container.
		if (strcmp(argv[index], "-U") == 0) {
			char container_dir[PATH_MAX];
			index += 1;
			if (argv[index] != NULL) {
				realpath(argv[index], container_dir);
				umount_container(container_dir);
				exit(EXIT_SUCCESS);
			}
		}
		/**** For running a container ****/
		// Just make clang-tidy happy.
		if (argv[index] == NULL) {
			error("\033[31mFailed to parse arguments.\n");
		}
		// Set no_new_privs bit.
		if (strcmp(argv[index], "-n") == 0) {
			info->no_new_privs = true;
		}
		// Enable built-in seccomp profile.
		else if (strcmp(argv[index], "-s") == 0) {
			info->enable_seccomp = true;
		}
		// Run unshare container.
		else if (strcmp(argv[index], "-u") == 0) {
			info->use_unshare = true;
		}
		// Run unprivileged container.
		else if (strcmp(argv[index], "-d") == 0) {
			priv_level = 0;
		}
		// Run privileged container.
		else if (strcmp(argv[index], "-p") == 0) {
			priv_level = 2;
		}
		// Run rootless container.
		else if (strcmp(argv[index], "-r") == 0) {
			info->rootless = true;
		}
		// Do not show warnings.
		else if (strcmp(argv[index], "-w") == 0) {
			info->no_warnings = true;
		}
		// Set extra env.
		else if (strcmp(argv[index], "-e") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_ENVS; i++) {
					if (info->env[i] == NULL) {
						info->env[i] = strdup(argv[index]);
						index++;
						info->env[i + 1] = strdup(argv[index]);
						info->env[i + 2] = NULL;
						break;
					}
					// Max 128 envs.
					if (i == (MAX_ENVS - 1)) {
						error("\033[31mToo many envs QwQ\n");
					}
				}
			} else {
				error("\033[31mError: unknow env QwQ\n");
			}
		}
		// Set extra mountpoints.
		else if (strcmp(argv[index], "-m") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
					if (info->mountpoint[i] == NULL) {
						info->mountpoint[i] = strdup(argv[index]);
						index++;
						info->mountpoint[i + 1] = strdup(argv[index]);
						info->mountpoint[i + 2] = NULL;
						break;
					}
					// Max 128 mountpoints.
					if (i == (MAX_MOUNTPOINTS - 1)) {
						error("\033[31mToo many mountpoints QwQ\n");
					}
				}
			} else {
				error("\033[31mError: unknow mountpoint QwQ\n");
			}
		}
		// Extra capabilities to keep.
		else if (strcmp(argv[index], "--keep") == 0) {
			index++;
			if (argv[index] != NULL) {
				if (cap_from_name(argv[index], &cap) == 0) {
					add_to_list(keep_caplist_extra, cap);
				} else {
					error("\033[31mError: unknow capability `%s`\nQwQ\033[0m\n", argv[index]);
				}
			} else {
				error("\033[31mMissing argument\n");
			}
		}
		// Extra capabilities to drop.
		else if (strcmp(argv[index], "--drop") == 0) {
			index++;
			if (argv[index] != NULL) {
				if (cap_from_name(argv[index], &cap) == 0) {
					add_to_list(drop_caplist_extra, cap);
				} else {
					error("\033[31mError: unknow capability `%s`\nQwQ\033[0m\n", argv[index]);
				}
			} else {
				error("\033[31mMissing argument\n");
			}
		}
		// A very shit way to judge that this is a dir...
		else if ((strchr(argv[index], '/') && strcmp(strchr(argv[index], '/'), argv[index]) == 0) || (strchr(argv[index], '.') && strcmp(strchr(argv[index], '.'), argv[index]) == 0)) {
			// Get the absolute path of container.
			info->container_dir = realpath(argv[index], NULL);
			index++;
			// Arguments after container_dir will be read as init command.
			if (argv[index]) {
				for (int i = 0; i < argc; i++) {
					if (argv[index]) {
						info->command[i] = strdup(argv[index]);
						info->command[i + 1] = NULL;
						index++;
					} else {
						break;
					}
				}
			} else {
				info->command[0] = NULL;
			}
		}
		// For unknown arguments, yeah I didn't forgot it...
		else {
			show_helps();
			error("\033[31mError: unknow option `%s`\033[0m\n", argv[index]);
		}
	}
	// Set default init command to run.
	if (info->command[0] == NULL) {
		// Rootless container can not run program like /bin/su.
		if (!(info->rootless)) {
			info->command[0] = "/bin/su";
			info->command[1] = "-";
			info->command[2] = NULL;
		} else {
			info->command[0] = "/bin/sh";
			info->command[1] = NULL;
		}
	}
	// Get the capabilities to drop.
	build_caplist(info->drop_caplist, priv_level, drop_caplist_extra, keep_caplist_extra);
	return info;
}
// It works on my machine!!!
int main(int argc, char **argv)
{
	/*
	 * Pogram starts here.
	 */
// Dev version warning.
#ifdef __RURI_DEV__
	warning("\033[31mWarning: you are using dev build.\033[0m\n\n");
#endif
	// Set process name.
	prctl(PR_SET_NAME, "ruri");
	// Info of container to run.
	struct CONTAINER_INFO *container_info = NULL;
	// Parse arguments.
	container_info = parse_args(argc, argv, container_info);
	// Check container_info and the running environment.
	check_container(container_info);
	// Run container.
	if ((container_info->use_unshare) && !(container_info->rootless)) {
		run_unshare_container(container_info);
	} else if ((container_info->rootless)) {
		// Create a new user namespace.
		unshare(CLONE_NEWUSER);
		pid_t pid = fork();
		if (pid > 0) {
			waitpid(pid, NULL, 0);
		} else if (pid < 0) {
			error("\033[31mFork error");
		} else {
			// Set uid map.
			char uid_map[32] = { "\0" };
			sprintf(uid_map, "0 %d 1", getuid());
			int uidmap_fd = open("/proc/self/uid_map", O_RDWR | O_CLOEXEC);
			write(uidmap_fd, uid_map, sizeof(uid_map));
			// Run chroot container.
			// mount(2) will fail without CAP_SYS_ADMIN.
			run_chroot_container(container_info);
		}
	} else {
		run_chroot_container(container_info);
	}
	return 0;
}
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
