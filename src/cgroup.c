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
static void mount_cgroup_v1(void)
{
	mkdir("/sys/fs/cgroup", S_IRUSR | S_IWUSR);
	// Maybe needless.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
	// Mount /sys/fs/cgroup as tmpfs.
	mount("tmpfs", "/sys/fs/cgroup", "tmpfs", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, NULL);
	// We only need cpuset and memory cgroup.
	mkdir("/sys/fs/cgroup/memory", S_IRUSR | S_IWUSR);
	mkdir("/sys/fs/cgroup/cpuset", S_IRUSR | S_IWUSR);
	mount("none", "/sys/fs/cgroup/memory", "cgroup", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, "memory");
	mount("none", "/sys/fs/cgroup/cpuset", "cgroup", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, "cpuset");
}
static bool is_cgroupv2_supported(void)
{
	bool found_cpuset = false;
	bool found_memory = false;
	int fd = open("/sys/fs/cgroup/cgroup.controllers", O_RDONLY | O_CLOEXEC);
	char buf[128] = { '\0' };
	ssize_t len = read(fd, buf, sizeof(buf));
	buf[len] = '\0';
	if (strstr(buf, "cpuset") != NULL) {
		found_cpuset = true;
	}
	if (strstr(buf, "memory") != NULL) {
		found_memory = true;
	}
	close(fd);
	if (found_cpuset && found_memory) {
		return true;
	}
	return false;
}
static int mount_cgroup_v2(void)
{
	/*
	 * We need cgroup2 cpuset and memory controller.
	 * If the device does not support, return -1.
	 */
	mkdir("/sys/fs/cgroup", S_IRUSR | S_IWUSR);
	// Maybe needless.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
	// I love cgroup2, because it's easy to mount.
	int ret = mount("none", "/sys/fs/cgroup", "cgroup2", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RELATIME, NULL);
	if (ret != 0) {
		return ret;
	}
	if (!is_cgroupv2_supported()) {
		umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
		return -1;
	}
	return 0;
}
static int mount_cgroup(void)
{
	/*
	 * Return the type of cgroup (1/2).
	 * Use cgroupv2 by default if supported.
	 */
	// It's better to use cgroupv2.
	if (mount_cgroup_v2() == 0) {
		return 2;
	}
	// But for old devices, we have to use v1.
	mount_cgroup_v1();
	return 1;
}
static void set_cgroup_v1(const struct CONTAINER *container)
{
	pid_t pid = getpid();
	char buf[128] = { '\0' };
	char cpuset_cgroup_path[PATH_MAX] = { '\0' };
	char memory_cgroup_path[PATH_MAX] = { '\0' };
	sprintf(cpuset_cgroup_path, "/sys/fs/cgroup/cpuset/%d", container->container_id);
	sprintf(memory_cgroup_path, "/sys/fs/cgroup/memory/%d", container->container_id);
	mkdir(cpuset_cgroup_path, S_IRUSR | S_IWUSR);
	mkdir(memory_cgroup_path, S_IRUSR | S_IWUSR);
	usleep(2000);
	int fd = -1;
	char memory_cgroup_procs_path[PATH_MAX] = { '\0' };
	sprintf(memory_cgroup_procs_path, "/sys/fs/cgroup/memory/%d/cgroup.procs", container->container_id);
	fd = open(memory_cgroup_procs_path, O_RDWR | O_CLOEXEC);
	sprintf(buf, "%d\n", pid);
	write(fd, buf, strlen(buf));
	close(fd);
	if (container->memory != NULL) {
		char memory_cgroup_limit_path[PATH_MAX] = { '\0' };
		sprintf(memory_cgroup_limit_path, "/sys/fs/cgroup/memory/%d/memory.limit_in_bytes", container->container_id);
		fd = open(memory_cgroup_limit_path, O_RDWR | O_CLOEXEC);
		sprintf(buf, "%s\n", container->memory);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("\033[33mSet memory limit failed\033[0m\n");
		}
		close(fd);
	}
	char cpuset_cgroup_procs_path[PATH_MAX] = { '\0' };
	sprintf(cpuset_cgroup_procs_path, "/sys/fs/cgroup/cpuset/%d/cgroup.procs", container->container_id);
	fd = open(cpuset_cgroup_procs_path, O_RDWR | O_CLOEXEC);
	sprintf(buf, "%d\n", pid);
	write(fd, buf, strlen(buf));
	close(fd);
	if (container->cpuset != NULL) {
		char cpuset_cgroup_cpus_path[PATH_MAX] = { '\0' };
		sprintf(cpuset_cgroup_cpus_path, "/sys/fs/cgroup/%d/cpus", container->container_id);
		fd = open(cpuset_cgroup_cpus_path, O_RDWR | O_CLOEXEC);
		sprintf(buf, "%s\n", container->cpuset);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("\033[33mSet cpu limit failed\033[0m\n");
		}
		close(fd);
	}
	// Do not keep the apifs mounted.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
}
static void set_cgroup_v2(const struct CONTAINER *container)
{
	if (container->memory == NULL && container->cpuset == NULL) {
		return;
	}
	pid_t pid = getpid();
	char buf[128] = { '\0' };
	char cgroup_path[PATH_MAX] = { '\0' };
	sprintf(cgroup_path, "/sys/fs/cgroup/%d", container->container_id);
	mkdir(cgroup_path, S_IRUSR | S_IWUSR);
	usleep(2000);
	char cgroup_procs_path[PATH_MAX] = { '\0' };
	sprintf(cgroup_procs_path, "/sys/fs/cgroup/%d/cgroup.procs", container->container_id);
	int fd = open(cgroup_procs_path, O_RDWR | O_CLOEXEC);
	sprintf(buf, "%d\n", pid);
	write(fd, buf, strlen(buf));
	close(fd);
	if (container->memory != NULL) {
		char cgroup_memlimit_path[PATH_MAX] = { '\0' };
		sprintf(cgroup_memlimit_path, "/sys/fs/cgroup/%d/memory.high", container->container_id);
		fd = open(cgroup_memlimit_path, O_RDWR | O_CLOEXEC);
		sprintf(buf, "%s\n", container->memory);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("\033[33mSet memory limit failed\033[0m\n");
		}
		close(fd);
	}
	if (container->cpuset != NULL) {
		char cgroup_cpuset_path[PATH_MAX] = { '\0' };
		sprintf(cgroup_cpuset_path, "/sys/fs/cgroup/%d/cpuset.cpus", container->container_id);
		fd = open(cgroup_cpuset_path, O_RDWR | O_CLOEXEC);
		sprintf(buf, "%s\n", container->cpuset);
		if (write(fd, buf, strlen(buf)) < 0 && !container->no_warnings) {
			warning("\033[33mSet cpu limit failed\033[0m\n");
		}
		close(fd);
	}
	// Do not keep the apifs mounted.
	umount2("/sys/fs/cgroup", MNT_DETACH | MNT_FORCE);
}
void set_limit(const struct CONTAINER *container)
{
	int cgtype = mount_cgroup();
	if (cgtype == 1) {
		set_cgroup_v1(container);
	} else {
		set_cgroup_v2(container);
	}
}
