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
// Run after chroot(), called by run_chroot_container().
void init_container()
{
  /*
   * It'll be run after chroot(), so `/` is the root dir of container now.
   * The device list and permissions are based on common docker container.
   */
  // umount /proc before we mount it.
  umount2("/proc", MNT_DETACH | MNT_FORCE);
  // Fix issues in archlinux containers.
  mount("/", "/", NULL, MS_BIND, NULL);
  // Mount proc,sys and dev.
  mkdir("/sys", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  mkdir("/proc", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  mkdir("/dev", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  mount("proc", "/proc", "proc", MS_NOSUID | MS_NOEXEC | MS_NODEV, NULL);
  // For /sys,we make it read-only.
  mount("sysfs", "/sys", "sysfs", MS_NOSUID | MS_NOEXEC | MS_NODEV | MS_RDONLY, NULL);
  mount("tmpfs", "/dev", "tmpfs", MS_NOSUID, "size=65536k,mode=755");
  // Continue mounting some other directories in /dev.
  mkdir("/dev/pts", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  mount("devpts", "/dev/pts", "devpts", 0, "gid=4,mode=620");
  mkdir("/dev/shm", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  mount("tmpfs", "/dev/shm", "tmpfs", MS_NOSUID | MS_NOEXEC | MS_NODEV, "mode=1777");
  mkdir("/dev/mqune", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  mount("mqune", "/dev/mqune", "mqune", 0, NULL);
  // Protect some system runtime directories as read-only.
  mount("/proc/bus", "/proc/bus", "proc", MS_BIND | MS_RDONLY, NULL);
  mount("/proc/fs", "/proc/fs", "proc", MS_BIND | MS_RDONLY, NULL);
  mount("/proc/irq", "/proc/irq", "proc", MS_BIND | MS_RDONLY, NULL);
  mount("/proc/sys", "/proc/sys", "proc", MS_BIND | MS_RDONLY, NULL);
  mount("/proc/asound", "/proc/asound", "proc", MS_BIND | MS_RDONLY, NULL);
  mount("/proc/scsi", "/proc/scsi", "proc", MS_BIND | MS_RDONLY, NULL);
  mount("/sys/firmware", "/sys/firmware", "sysfs", MS_BIND | MS_RDONLY, NULL);
  // For getting dev nodes.
  dev_t dev = 0;
  // Create system runtime files in /dev and then fix permissions.
  dev = makedev(1, 3);
  mknod("/dev/null", S_IFCHR, dev);
  chmod("/dev/null", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  dev = makedev(5, 1);
  mknod("/dev/console", S_IFCHR, dev);
  chown("/dev/console", 0, 5);
  chmod("/dev/console", S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH);
  dev = makedev(1, 5);
  mknod("/dev/zero", S_IFCHR, dev);
  chmod("/dev/zero", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  dev = makedev(5, 2);
  mknod("/dev/ptmx", S_IFCHR, dev);
  chown("/dev/ptmx", 0, 5);
  chmod("/dev/ptmx", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  dev = makedev(5, 0);
  mknod("/dev/tty", S_IFCHR, dev);
  chown("/dev/tty", 0, 5);
  chmod("/dev/tty", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  dev = makedev(1, 8);
  mknod("/dev/random", S_IFCHR, dev);
  chmod("/dev/random", S_IRUSR | S_IRGRP | S_IROTH);
  dev = makedev(1, 9);
  mknod("/dev/urandom", S_IFCHR, dev);
  chmod("/dev/urandom", S_IRUSR | S_IRGRP | S_IROTH);
  mkdir("/dev/net", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
  dev = makedev(10, 200);
  mknod("/dev/net/tun", S_IFCHR, dev);
  // Create some system runtime link files in /dev.
  symlink("/proc/self/fd", "/dev/fd");
  symlink("/proc/self/fd/0", "/dev/stdin");
  symlink("/proc/self/fd/1", "/dev/stdout");
  symlink("/proc/self/fd/2", "/dev/stderr");
  symlink("/dev/null", "/dev/tty0");
  // Fix issues in archlinux containers.
  remove("/etc/mtab");
  unlink("/etc/mtab");
  symlink("/proc/mounts", "/etc/mtab");
}
// Run chroot container.
void run_chroot_container(struct CONTAINER_INFO *container_info, const bool no_warnings)
{
  /*
   * It's called to by main(), run_unshare_container() and daemon_init_unshare_container()(container_daemon()).
   * It will chroot() to container_dir, call to init_container(), drop capabilities and exec() init command in container.
   */
  // Ignore SIGTTIN, if running in the background, SIGTTIN may kill it.
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTTIN);
  sigprocmask(SIG_BLOCK, &sigs, 0);
#ifdef __RURI_DEV__
  printf("Run chroot container:\n");
  printf("%s%s\n", "container_dir: ", container_info->container_dir);
  if (container_info->no_new_privs != false)
  {
    printf("%s\n", "no_new_privs: true");
  }
  else
  {
    printf("%s\n", "no_new_privs: false");
  }
  if (container_info->enable_seccomp != false)
  {
    printf("%s\n", "enable_seccomp: true");
  }
  else
  {
    printf("%s\n", "enable_seccomp: false");
  }
  printf("init command : ");
  for (int i = 0;;)
  {
    if (container_info->init_command[i] != NULL)
    {
      printf("%s%s", container_info->init_command[i], " ");
      i++;
    }
    else
    {
      printf("\n");
      break;
    }
  }
  printf("drop caplist: ");
  for (int i = 0;;)
  {
    if (!container_info->drop_caplist[i])
    {
      printf("%s%s", cap_to_name(0), " ");
      i++;
    }
    else if (container_info->drop_caplist[i] != INIT_VALUE)
    {
      printf("%s%s", cap_to_name(container_info->drop_caplist[i]), " ");
      i++;
    }
    else
    {
      printf("\n");
      break;
    }
  }
  printf("Mountpoints: \n");
  for (int i = 0;;)
  {
    if (container_info->mountpoint[i] != NULL)
    {
      printf("%s%s", container_info->mountpoint[i], " to ");
      printf("%s%s", container_info->mountpoint[i + 1], "\n");
      i += 2;
    }
    else
    {
      printf("\n");
      break;
    }
  }
  printf("Envs: \n");
  for (int i = 0;;)
  {
    if (container_info->env[i] != NULL)
    {
      printf("%s%s", container_info->env[i], " = ");
      printf("%s%s", container_info->env[i + 1], "\n");
      i += 2;
    }
    else
    {
      printf("\n");
      break;
    }
  }
#endif
  // Mount mountpoints.
  for (int i = 0;;)
  {
    if (container_info->mountpoint[i] != NULL)
    {
      // Set mountpoint.
      char *mountpoint_dir = (char *)malloc(strlen(container_info->mountpoint[i + 1]) + strlen(container_info->container_dir) + 2);
      strcpy(mountpoint_dir, container_info->container_dir);
      strcat(mountpoint_dir, container_info->mountpoint[i + 1]);
      // Check if mountpoint exists.
      DIR *test = NULL;
      if ((test = opendir(mountpoint_dir)) == NULL)
      {
        if (mkdirs(mountpoint_dir, 0755) != 0)
        {
          error("Could not create mountpoint directory");
        }
      }
      else
      {
        closedir(test);
      }
      // Mount mountpoints.
      mount(container_info->mountpoint[i], mountpoint_dir, NULL, MS_BIND, NULL);
      i += 2;
      free(mountpoint_dir);
    }
    else
    {
      break;
    }
  }
  // Set default init.
  if (container_info->init_command[0] == NULL)
  {
    container_info->init_command[0] = "/bin/su";
    container_info->init_command[1] = NULL;
  }
  // chroot into container.
  chroot(container_info->container_dir);
  chdir("/");
  // Check if system runtime files are already created.
  DIR *direxist = NULL;
  if ((direxist = opendir("/sys/kernel")) == NULL)
  {
    // Create system runtime files.
    init_container();
  }
  else
  {
    closedir(direxist);
  }
  // Set up Seccomp BPF.
  if (container_info->enable_seccomp != false)
  {
    setup_seccomp(container_info);
  }
  // Drop caps.
  if ((container_info->drop_caplist[0] != INIT_VALUE) || !container_info->drop_caplist[0])
  {
    for (int i = 0; i < CAP_LAST_CAP + 1; i++)
    {
      // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN.
      if (!container_info->drop_caplist[i])
      {
        if (cap_drop_bound(0) != 0 && !no_warnings)
        {
          fprintf(stderr, "\033[33mWarning: Failed to drop cap `%s`\n", cap_to_name(0));
          fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
        }
      }
      else if (container_info->drop_caplist[i] != INIT_VALUE)
      {
        if (cap_drop_bound(container_info->drop_caplist[i]) != 0 && !no_warnings)
        {
          fprintf(stderr, "\033[33mWarning: Failed to drop cap `%s`\n", cap_to_name(container_info->drop_caplist[i]));
          fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
        }
      }
      else
      {
        break;
      }
    }
  }
  // Set envs.
  for (int i = 0;;)
  {
    if (container_info->env[i] != NULL)
    {
      setenv(container_info->env[i], container_info->env[i + 1], 1);
      i = i + 2;
    }
    else
    {
      break;
    }
  }
  // Login to container.
  // Use execv() function because system() may be unavailable now.
  usleep(200000);
  // Set NO_NEW_PRIVS Flag.
  // It requires Linux3.5 or later.
  // It will make sudo unavailable in container.
  if (container_info->no_new_privs != false)
  {
    prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
  }
  if (execv(container_info->init_command[0], container_info->init_command) == -1)
  {
    // Catch exceptions.
    fprintf(stderr, "\033[31mFailed to execute `%s`\n", container_info->init_command[0]);
    fprintf(stderr, "execv() returned: %d\n", errno);
    fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
    error("QwQ");
  }
}
