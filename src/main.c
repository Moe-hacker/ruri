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
		error("\033[31mError: please unset $LD_PRELOAD before running this program QwQ\n");
	}
	// Check if container directory exists.
	DIR *direxist = opendir(container_info->container_dir);
	if (direxist == NULL) {
		error("\033[31mError: container directory does not exist QwQ\n");
	}
	closedir(direxist);
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
	bool privileged = false;
	info = (struct CONTAINER_INFO *)malloc(sizeof(struct CONTAINER_INFO));
	info->enable_seccomp = false;
	info->no_new_privs = false;
	info->no_warnings = false;
	info->enable_unshare = false;
	info->rootless = false;
	info->mount_host_runtime = false;
	info->command[0] = NULL;
	info->env[0] = NULL;
	info->extra_mountpoint[0] = NULL;
	info->cross_arch = NULL;
	info->qemu_path = NULL;
	info->ns_pid = INIT_VALUE;
	// A very large and shit-code for() loop.
	// At least it works fine...
	for (int index = 1; index < argc; index++) {
		/**** Deprecated options. ****/
		if (strcmp(argv[index], "-D") == 0) {
			printf("\033[33m%s option has been deprecated.\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-K") == 0) {
			printf("\033[33m%s option has been deprecated.\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-t") == 0) {
			printf("\033[33m%s option has been deprecated.\n", argv[index]);
			index++;
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-T") == 0) {
			printf("\033[33m%s option has been deprecated.\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-l") == 0) {
			printf("\033[33m%s option has been deprecated.\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
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
		// Umount a container.
		if (strcmp(argv[index], "-U") == 0) {
			index += 1;
			if (argv[index] != NULL) {
				char *container_dir = realpath(argv[index], NULL);
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
		// Simulate architecture.
		else if (strcmp(argv[index], "-a") == 0) {
			index++;
			info->cross_arch = strdup(argv[index]);
		}
		// Path of QEMU.
		else if (strcmp(argv[index], "-q") == 0) {
			index++;
			info->qemu_path = strdup(argv[index]);
		}
		// Join existing ns.
		else if (strcmp(argv[index], "-j") == 0) {
			index++;
			info->enable_unshare = true;
			info->ns_pid = (pid_t)atol(argv[index]);
		}
		// Enable built-in seccomp profile.
		else if (strcmp(argv[index], "-s") == 0) {
			info->enable_seccomp = true;
		}
		// Run unshare container.
		else if (strcmp(argv[index], "-u") == 0) {
			info->enable_unshare = true;
		}
		// Run privileged container.
		else if (strcmp(argv[index], "-p") == 0) {
			privileged = true;
		}
		// Run rootless container.
		else if (strcmp(argv[index], "-r") == 0) {
			info->rootless = true;
		}
		// Do not show warnings.
		else if (strcmp(argv[index], "-w") == 0) {
			info->no_warnings = true;
		}
		// Force bind-mount host /dev/, /sys/ and /proc/.
		else if (strcmp(argv[index], "-S") == 0) {
			info->mount_host_runtime = true;
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
				error("\033[31mError: unknown env QwQ\n");
			}
		}
		// Set extra mountpoints.
		else if (strcmp(argv[index], "-m") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
					if (info->extra_mountpoint[i] == NULL) {
						info->extra_mountpoint[i] = realpath(argv[index], NULL);
						index++;
						info->extra_mountpoint[i + 1] = strdup(argv[index]);
						info->extra_mountpoint[i + 2] = NULL;
						break;
					}
					// Max 128 mountpoints.
					if (i == (MAX_MOUNTPOINTS - 1)) {
						error("\033[31mToo many mountpoints QwQ\n");
					}
				}
			} else {
				error("\033[31mError: unknown mountpoint QwQ\n");
			}
		}
		// Extra capabilities to keep.
		else if (strcmp(argv[index], "-k") == 0) {
			index++;
			if (argv[index] != NULL) {
				if (cap_from_name(argv[index], &cap) == 0) {
					add_to_caplist(keep_caplist_extra, cap);
				} else {
					error("\033[31mError: unknown capability `%s`\nQwQ\033[0m\n", argv[index]);
				}
			} else {
				error("\033[31mMissing argument\n");
			}
		}
		// Extra capabilities to drop.
		else if (strcmp(argv[index], "-d") == 0) {
			index++;
			if (argv[index] != NULL) {
				if (cap_from_name(argv[index], &cap) == 0) {
					add_to_caplist(drop_caplist_extra, cap);
				} else {
					error("\033[31mError: unknown capability `%s`\nQwQ\033[0m\n", argv[index]);
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
	build_caplist(info->drop_caplist, privileged, drop_caplist_extra, keep_caplist_extra);
	return info;
}
// It works on my machine!!!
int main(int argc, char **argv)
{
	/*
	 * Pogram starts here.
	 */
	// Set process name.
	prctl(PR_SET_NAME, "ruri");
	// Catch coredump signal.
	register_signal();
	// Info of container to run.
	struct CONTAINER_INFO *container_info = NULL;
	// Parse arguments.
	container_info = parse_args(argc, argv, container_info);
	// Check container_info and the running environment.
	check_container(container_info);
	// Run container.
	if ((container_info->enable_unshare) && !(container_info->rootless)) {
		run_unshare_container(container_info);
	} else if ((container_info->rootless)) {
		run_rootless_container(container_info);
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
