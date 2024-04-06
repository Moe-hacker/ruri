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
static void check_container(const struct CONTAINER *container)
{
	/*
	 * It's called by main() to check if container is correct.
	 * It will also check the running environment.
	 * Note that it can only do basic checks,
	 * and we can't know if the config can really run a container properly.
	 */
	// Check if container directory is given.
	if (container->container_dir == NULL) {
		error("\033[31mError: container directory is not set QwQ\n");
	}
	// Refuse to use `/` for container directory.
	if (strcmp(container->container_dir, "/") == 0) {
		error("\033[31mError: `/` is not allowed to use as a container directory QwQ\n");
	}
	// Check if we are running with root privileges.
	if (getuid() != 0 && !(container->rootless)) {
		error("\033[31mError: this program should be run with root privileges QwQ\n");
	}
	// Check if container directory exists.
	DIR *direxist = opendir(container->container_dir);
	if (direxist == NULL) {
		error("\033[31mError: container directory does not exist QwQ\n");
	}
	closedir(direxist);
}
static struct CONTAINER *parse_args(int argc, char **argv, struct CONTAINER *container)
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
	// Init configs.
	bool dump_config = false;
	char *output_path = NULL;
	cap_value_t keep_caplist_extra[CAP_LAST_CAP + 1] = { INIT_VALUE };
	cap_value_t drop_caplist_extra[CAP_LAST_CAP + 1] = { INIT_VALUE };
	cap_value_t cap = INIT_VALUE;
	bool privileged = false;
	container = (struct CONTAINER *)malloc(sizeof(struct CONTAINER));
	container->enable_seccomp = false;
	container->no_new_privs = false;
	container->no_warnings = false;
	container->enable_unshare = false;
	container->rootless = false;
	container->mount_host_runtime = false;
	container->command[0] = NULL;
	container->env[0] = NULL;
	container->extra_mountpoint[0] = NULL;
	container->extra_ro_mountpoint[0] = NULL;
	container->cross_arch = NULL;
	container->qemu_path = NULL;
	container->ns_pid = INIT_VALUE;
	container->use_rurienv = true;
	container->ro_root = false;
	container->cpuset = NULL;
	container->memory = NULL;
	// Use the time for container_id.
	time_t tm = time(NULL);
	container->container_id = (int)(tm % 86400);
	// A very large and shit-code for() loop.
	// At least it works fine...
	for (int index = 1; index < argc; index++) {
		/**** Deprecated options. ****/
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
		if (strcmp(argv[index], "-v") == 0 || strcmp(argv[index], "--version") == 0) {
			show_version_info();
			exit(EXIT_SUCCESS);
		}
		// Show version code, very useless right now.
		if (strcmp(argv[index], "-V") == 0 || strcmp(argv[index], "--version-code") == 0) {
			show_version_code();
			exit(EXIT_SUCCESS);
		}
		// Show help page.
		if (strcmp(argv[index], "-h") == 0 || strcmp(argv[index], "--help") == 0) {
			show_helps();
			exit(EXIT_SUCCESS);
		}
		// Show help page and example usage.
		if (strcmp(argv[index], "-H") == 0 || strcmp(argv[index], "--show-examples") == 0) {
			show_helps();
			show_examples();
			exit(EXIT_SUCCESS);
		}
		// Umount a container.
		if (strcmp(argv[index], "-U") == 0 || strcmp(argv[index], "--umount") == 0) {
			index += 1;
			if (argv[index] != NULL) {
				char *container_dir = realpath(argv[index], NULL);
				umount_container(container_dir);
				exit(EXIT_SUCCESS);
			}
			exit(EXIT_FAILURE);
		}
		/**** For running a container ****/
		// Just make clang-tidy happy.
		if (argv[index] == NULL) {
			error("\033[31mFailed to parse arguments.\n");
		}
		// Use config file.
		if (strcmp(argv[index], "-c") == 0 || strcmp(argv[index], "--config") == 0) {
			if (index == argc - 1) {
				error("\033[31mPlease specify a config file !\n\033[0m");
			}
			index++;
			container = read_config(container, argv[index]);
			break;
		}
		// Dump config.
		if (strcmp(argv[index], "-D") == 0 || strcmp(argv[index], "--dump-config") == 0) {
			dump_config = true;
		}
		// Output file.
		else if (strcmp(argv[index], "-o") == 0 || strcmp(argv[index], "--output") == 0) {
			index++;
			if (index == argc - 1) {
				error("\033[31mPlease specify the output file\n\033[0m");
			}
			output_path = argv[index];
		}
		// Set no_new_privs bit.
		else if (strcmp(argv[index], "-n") == 0 || strcmp(argv[index], "--no-new-privs") == 0) {
			container->no_new_privs = true;
		}
		// Do not store .rurienv file.
		else if (strcmp(argv[index], "-N") == 0 || strcmp(argv[index], "--no-rurienv") == 0) {
			container->use_rurienv = false;
		}
		// Simulate architecture.
		else if (strcmp(argv[index], "-a") == 0 || strcmp(argv[index], "--arch") == 0) {
			if (index == argc - 1) {
				error("\033[31mPlease specify the arch\n\033[0m");
			}
			index++;
			container->cross_arch = strdup(argv[index]);
		}
		// Path of QEMU.
		else if (strcmp(argv[index], "-q") == 0 || strcmp(argv[index], "--qemu-path") == 0) {
			index++;
			if (index == argc - 1) {
				error("\033[31mPlease specify the path of qemu binary\n\033[0m");
			}
			container->qemu_path = strdup(argv[index]);
		}
		// Enable built-in seccomp profile.
		else if (strcmp(argv[index], "-s") == 0 || strcmp(argv[index], "--enable-seccomp") == 0) {
			container->enable_seccomp = true;
		}
		// Run unshare container.
		else if (strcmp(argv[index], "-u") == 0 || strcmp(argv[index], "--unshare") == 0) {
			container->enable_unshare = true;
		}
		// Run privileged container.
		else if (strcmp(argv[index], "-p") == 0 || strcmp(argv[index], "--privileged") == 0) {
			privileged = true;
		}
		// Run rootless container.
		else if (strcmp(argv[index], "-r") == 0 || strcmp(argv[index], "--rootless") == 0) {
			container->rootless = true;
		}
		// Do not show warnings.
		else if (strcmp(argv[index], "-w") == 0 || strcmp(argv[index], "--no-warnings") == 0) {
			container->no_warnings = true;
		}
		// Force bind-mount host /dev/, /sys/ and /proc/.
		else if (strcmp(argv[index], "-S") == 0 || strcmp(argv[index], "--host-runtime") == 0) {
			container->mount_host_runtime = true;
		}
		// Mount / as read-only.
		else if (strcmp(argv[index], "-R") == 0 || strcmp(argv[index], "--read-only") == 0) {
			container->ro_root = true;
		}
		// Set extra env.
		else if (strcmp(argv[index], "-e") == 0 || strcmp(argv[index], "--env") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_ENVS; i++) {
					if (container->env[i] == NULL) {
						container->env[i] = strdup(argv[index]);
						index++;
						container->env[i + 1] = strdup(argv[index]);
						container->env[i + 2] = NULL;
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
		else if (strcmp(argv[index], "-m") == 0 || strcmp(argv[index], "--mount") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
					if (container->extra_mountpoint[i] == NULL) {
						container->extra_mountpoint[i] = realpath(argv[index], NULL);
						index++;
						container->extra_mountpoint[i + 1] = strdup(argv[index]);
						container->extra_mountpoint[i + 2] = NULL;
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
		// Set extra read-only mountpoints.
		else if (strcmp(argv[index], "-M") == 0 || strcmp(argv[index], "--ro-mount") == 0) {
			index++;
			if ((argv[index] != NULL) && (argv[index + 1] != NULL)) {
				for (int i = 0; i < MAX_MOUNTPOINTS; i++) {
					if (container->extra_ro_mountpoint[i] == NULL) {
						container->extra_ro_mountpoint[i] = realpath(argv[index], NULL);
						index++;
						container->extra_ro_mountpoint[i + 1] = strdup(argv[index]);
						container->extra_ro_mountpoint[i + 2] = NULL;
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
		else if (strcmp(argv[index], "-k") == 0 || strcmp(argv[index], "--keep") == 0) {
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
		else if (strcmp(argv[index], "-d") == 0 || strcmp(argv[index], "--drop") == 0) {
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
			container->container_dir = realpath(argv[index], NULL);
			if (container->container_dir == NULL) {
				error("\033[31mCONTAINER_DIR %s does not exist\033[0m\n", argv[index]);
			}
			index++;
			// Arguments after container_dir will be read as init command.
			if (argv[index]) {
				for (int i = 0; i < argc; i++) {
					if (argv[index]) {
						container->command[i] = strdup(argv[index]);
						container->command[i + 1] = NULL;
						index++;
					} else {
						break;
					}
				}
			} else {
				container->command[0] = NULL;
			}
		}
		// For unknown arguments, yeah I didn't forgot it...
		else {
			show_helps();
			error("\033[31mError: unknow option `%s`\033[0m\n", argv[index]);
		}
	}
	// Set default init command to run.
	if (container->command[0] == NULL) {
		// Rootless container can not run program like /bin/su.
		if (!(container->rootless)) {
			container->command[0] = "/bin/su";
			container->command[1] = "-";
			container->command[2] = NULL;
		} else {
			container->command[0] = "/bin/sh";
			container->command[1] = NULL;
		}
	}
	// Get the capabilities to drop.
	build_caplist(container->drop_caplist, privileged, drop_caplist_extra, keep_caplist_extra);
	// Dump config.
	if (dump_config) {
		// Check if container directory is given.
		if (container->container_dir == NULL) {
			error("\033[31mError: container directory is not set QwQ\n");
		}
		// Refuse to use `/` for container directory.
		if (strcmp(container->container_dir, "/") == 0) {
			error("\033[31mError: `/` is not allowed to use as a container directory QwQ\n");
		}
		// Check if container directory exists.
		DIR *direxist = opendir(container->container_dir);
		if (direxist == NULL) {
			error("\033[31mError: container directory does not exist QwQ\n");
		}
		closedir(direxist);
		char *config = container_info_to_k2v(container);
		if (output_path == NULL) {
			printf("%s", config);
			exit(EXIT_SUCCESS);
		}
		unlink(output_path);
		remove(output_path);
		int fd = open(output_path, O_CREAT | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR | S_IWOTH);
		write(fd, config, strlen(config));
		exit(EXIT_SUCCESS);
	}
	return container;
}
// It works on my machine!!!
int main(int argc, char **argv)
{
	/*
	 * Pogram starts here.
	 */
	// Exit when we get error reading configs.
	k2v_stop_at_warning = true;
	// Set process name.
	prctl(PR_SET_NAME, "ruri");
	// Catch coredump signal.
	register_signal();
	// Info of container to run.
	struct CONTAINER *container = NULL;
	// Parse arguments.
	container = parse_args(argc, argv, container);
	// Check container and the running environment.
	check_container(container);
	// Run container.
	// unset $LD_PRELOAD.
	if (getenv("LD_PRELOAD") != NULL) {
		unsetenv("LD_PRELOAD");
		pid_t pid = fork();
		if (pid > 0) {
			waitpid(pid, NULL, 0);
			exit(EXIT_SUCCESS);
		}
	}
	if ((container->enable_unshare) && !(container->rootless)) {
		run_unshare_container(container);
	} else if ((container->rootless)) {
		run_rootless_container(container);
	} else {
		run_chroot_container(container);
	}
	return 0;
}
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
