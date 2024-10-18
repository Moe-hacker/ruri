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
	 * It's called by main() to check if container config is correct.
	 * It will also check the running environment.
	 * Note that it can only do basic checks,
	 * and we can't know if the config can really run a container properly.
	 */
	// Check if container directory is given.
	if (container->container_dir == NULL) {
		error("{red}Error: container directory is not set or does not exist QwQ\n");
	}
	// Refuse to use `/` for container directory.
	if (strcmp(container->container_dir, "/") == 0) {
		error("{red}Error: `/` is not allowed to use as a container directory QwQ\n");
	}
	// Check if we are running with root privileges.
	if (getuid() != 0 && !(container->rootless)) {
		error("{red}Error: this program should be run with root privileges QwQ\n");
	}
	// --arch and --qemu-path should be set at the same time.
	if ((container->cross_arch == NULL) ^ (container->qemu_path == NULL)) {
		error("{red}Error: --arch and --qemu-path should be set at the same time QwQ\n");
	}
}
static void parse_cgroup_settings(const char *str, struct CONTAINER *container)
{
	/*
	 * Parse and set cgroup limit.
	 * The format should be like `cpuset=1` or `memory=1M`.
	 * We will not check if the config is vaild.
	 */
	char buf[16] = { '\0' };
	char *limit = NULL;
	// Get limit type.
	for (size_t i = 0; i < 16; i++) {
		// Avoid overflow.
		if (i >= strlen(str)) {
			break;
		}
		if (str[i] == '=') {
			limit = strdup(&(str[i + 1]));
			break;
		}
		buf[i] = str[i];
		buf[i + 1] = '\0';
	}
	if (strcmp("cpuset", buf) == 0) {
		container->cpuset = limit;
	} else if (strcmp("memory", buf) == 0) {
		container->memory = limit;
	} else {
		error("{red}Unknown cgroup option %s\n", str);
	}
}
static void parse_args(int argc, char **argv, struct CONTAINER *container)
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
		cfprintf(stderr, "{red}Error: too few arguments QwQ{clear}\n");
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
	// For using qemu binary outside the container.
	// This is the path of qemu binary in host,
	// and we will copy it into container as /qemu-ruri.
	// And after that, we will use /qemu-ruri as container->qemu_path.
	char *qemu_path = NULL;
	// Use the time now for container_id.
	time_t tm = time(NULL);
	// We need a int value for container_id, so use long%86400.
	// (86400 is the seconds of a day).
	container->container_id = (int)(tm % 86400);
	// A very large and shit-code for() loop.
	// At least it works fine...
	for (int index = 1; index < argc; index++) {
		/**** Deprecated options. ****/
		if (strcmp(argv[index], "-K") == 0) {
			cprintf("{yellow}%s option has been deprecated.{clear}\n", argv[index]);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-t") == 0) {
			cprintf("{yellow}%s option has been deprecated.{clear}\n", argv[index]);
			index++;
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[index], "-T") == 0) {
			cprintf("{yellow}%s option has been deprecated.{clear}\n", argv[index]);
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
			error("{red}Failed to parse arguments.\n");
		}
		// Use config file.
		if (strcmp(argv[index], "-c") == 0 || strcmp(argv[index], "--config") == 0) {
			if (index == argc - 1) {
				error("{red}Please specify a config file !\n{clear}");
			}
			index++;
			read_config(container, argv[index]);
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
				error("{red}Please specify the output file\n{clear}");
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
				error("{red}Please specify the arch\n{clear}");
			}
			index++;
			container->cross_arch = strdup(argv[index]);
		}
		// Path of QEMU.
		else if (strcmp(argv[index], "-q") == 0 || strcmp(argv[index], "--qemu-path") == 0) {
			index++;
			if (index == argc - 1) {
				error("{red}Please specify the path of qemu binary\n{clear}");
			}
			// Auto recognize if qemu_path is in host or in container.
			qemu_path = realpath(argv[index], NULL);
			if (qemu_path != NULL) {
				// If qemu_path is in host, we will copy it into container,
				// and use /qemu-ruri as container->qemu_path.
				container->qemu_path = "/qemu-ruri";
			} else {
				container->qemu_path = strdup(argv[index]);
			}
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
		// cgroup limit.
		else if (strcmp(argv[index], "-l") == 0 || strcmp(argv[index], "--limit") == 0) {
			index++;
			if ((argv[index] != NULL)) {
				parse_cgroup_settings(argv[index], container);
			} else {
				error("{red}Unknown cgroup option\n");
			}
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
						error("{red}Too many envs QwQ\n");
					}
				}
			} else {
				error("{red}Error: unknown env QwQ\n");
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
						error("{red}Too many mountpoints QwQ\n");
					}
				}
			} else {
				error("{red}Error: unknown mountpoint QwQ\n");
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
						error("{red}Too many mountpoints QwQ\n");
					}
				}
			} else {
				error("{red}Error: unknown mountpoint QwQ\n");
			}
		}
		// Extra capabilities to keep.
		else if (strcmp(argv[index], "-k") == 0 || strcmp(argv[index], "--keep") == 0) {
			index++;
			if (argv[index] != NULL) {
				// We both support capability name and number,
				// because in the fulture, there might be new capabilities that
				// we can not use the name to match it in current libcap.
				if (atoi(argv[index]) != 0) {
					add_to_caplist(keep_caplist_extra, atoi(argv[index]));
				} else if (cap_from_name(argv[index], &cap) == 0) {
					add_to_caplist(keep_caplist_extra, cap);
				} else {
					error("{red}or: unknown capability `%s`\nQwQ{clear}\n", argv[index]);
				}
			} else {
				error("{red}Missing argument\n");
			}
		}
		// Extra capabilities to drop.
		else if (strcmp(argv[index], "-d") == 0 || strcmp(argv[index], "--drop") == 0) {
			index++;
			if (argv[index] != NULL) {
				if (atoi(argv[index]) != 0) {
					add_to_caplist(drop_caplist_extra, atoi(argv[index]));
				} else if (cap_from_name(argv[index], &cap) == 0) {
					add_to_caplist(drop_caplist_extra, cap);
				} else {
					error("{red}Error: unknown capability `%s`\nQwQ{clear}\n", argv[index]);
				}
			} else {
				error("{red}Missing argument\n");
			}
		}
		// If this argument is CONTAINER_DIR.
		else if (({
				 // We use a GNU extension here.
				 container->container_dir = realpath(argv[index], NULL);
				 container->container_dir;
			 }) != NULL) {
			index++;
			// Arguments after container_dir will be read as command to exec in container.
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
			error("{red}Error: unknown option `%s`{clear}\n", argv[index]);
		}
	}
	// Copy qemu binary into container.
	if (qemu_path != NULL) {
		char target[PATH_MAX] = { '\0' };
		sprintf(target, "%s/qemu-ruri", container->container_dir);
		int sourcefd = open(qemu_path, O_RDONLY | O_CLOEXEC);
		int targetfd = open(target, O_WRONLY | O_CREAT | O_CLOEXEC, S_IRGRP | S_IXGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IXUSR | S_IWOTH | S_IXOTH | S_IROTH);
		struct stat stat_buf;
		fstat(sourcefd, &stat_buf);
		off_t offset = 0;
		// In linux, I think it's more safe to use sendfile(2) to copy files,
		// because it does not need a buffer.
		// !NOTE: Linux version under 2.6.33 does not support sendfile(2) for copying files.
		sendfile(targetfd, sourcefd, &offset, stat_buf.st_size);
		close(targetfd);
		close(sourcefd);
	}
	// Build the caplist to drop.
	build_caplist(container->drop_caplist, privileged, drop_caplist_extra, keep_caplist_extra);
	// Dump config.
	if (dump_config) {
		// Check if container directory is given.
		if (container->container_dir == NULL) {
			error("{red}Error: container directory is not set or does not exist QwQ\n");
		}
		// Refuse to use `/` for container directory.
		if (strcmp(container->container_dir, "/") == 0) {
			error("{red}Error: `/` is not allowed to use as a container directory QwQ\n");
		}
		char *config = container_info_to_k2v(container);
		if (output_path == NULL) {
			cprintf("%s", config);
			exit(EXIT_SUCCESS);
		}
		unlink(output_path);
		remove(output_path);
		int fd = open(output_path, O_CREAT | O_CLOEXEC | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR | S_IWOTH);
		write(fd, config, strlen(config));
		free(config);
		close(fd);
		exit(EXIT_SUCCESS);
	}
}
// It works on my machine!!!
int main(int argc, char **argv)
{
	/*
	 * Pogram starts here!
	 */
	// Exit when we get error reading configs.
	k2v_stop_at_warning = true;
	// Set process name.
	prctl(PR_SET_NAME, "ruri");
	// Catch coredump signal.
	register_signal();
	// Info of container to run.
	struct CONTAINER *container = (struct CONTAINER *)malloc(sizeof(struct CONTAINER));
	// Parse arguments.
	parse_args(argc, argv, container);
	// Check container and the running environment.
	check_container(container);
	// unset $LD_PRELOAD.
	unsetenv("LD_PRELOAD");
	// Run container.
	if ((container->enable_unshare) && !(container->rootless)) {
		// Unshare container.
		run_unshare_container(container);
	} else if ((container->rootless)) {
		// Rootless container.
		run_rootless_container(container);
	} else {
		// Common chroot container.
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
