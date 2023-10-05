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
// Do some checks before chroot(),called by main()
bool check_container(char *container_dir)
{
  /*
   * It's called to by main() to check if we can run a container in container_dir.
   * Note that it can only do basic checks. We can't know if container_dir is really right.
   */
  // Check if container directory is given.
  if (container_dir == NULL)
  {
    error("Error: container directory is not set QwQ");
  }
  // Refuse to use `/` for container directory.
  if (strcmp(container_dir, "/") == 0)
  {
    error("Error: `/` is not allowed to use as a container directory QwQ");
  }
  // Check if we are running with root privileges.
  if (getuid() != 0)
  {
    error("Error: this program should be run with root privileges QwQ");
  }
  // Check if $LD_PRELOAD is unset.
  // If LD_PRELOAD is set, container might will not run properly.
  char *ld_preload = getenv("LD_PRELOAD");
  if ((ld_preload != NULL) && (strcmp(ld_preload, "") != 0))
  {
    error("Error: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run QwQ");
  }
  // Check if container directory exists.
  DIR *direxist = NULL;
  if ((direxist = opendir(container_dir)) == NULL)
  {
    error("Error: container directory does not exist QwQ");
  }
  closedir(direxist);
  return true;
}
// It works on my machine!!!
int main(int argc, char **argv)
{
/*
 * 100% shit-code in main().
 * At least it works...
 * If the code is hard to write,
 * it should be hard to read nya~
 */
// Dev version warning.
#ifdef __RURI_DEV__
  printf("\033[31mWarning: you are using dev build.\033[0m\n");
  printf("\n");
#endif
  // Set process name.
  prctl(PR_SET_NAME, "ruri");
  // Check if arguments are given.
  if (argc <= 1)
  {
    fprintf(stderr, "\033[31mError: too few arguments QwQ\033[0m\n");
    show_helps(0);
    return 1;
  }
  bool use_unshare = false;
  bool no_warnings = false;
  char container_dir[PATH_MAX] = {'\0'};
  bool privileged = false;
  char *init[MAX_INIT_COMMANDS] = {NULL};
  char *env[MAX_ENVS] = {NULL};
  char *mountpoint[MAX_MOUNTPOINTS] = {NULL};
  struct CONTAINER_INFO *container_info = NULL;
  bool no_new_privs = false;
  bool enable_seccomp = false;
  cap_value_t drop_caplist[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    drop_caplist[i] = INIT_VALUE;
  }
  // Based on docker's default capability set.
  cap_value_t drop_caplist_common[] = {CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND, CAP_SYS_TIME, CAP_MKNOD, CAP_SYS_CHROOT};
  cap_value_t drop_caplist_unprivileged[] = {CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND, CAP_SYS_CHROOT, CAP_SETPCAP, CAP_MKNOD, CAP_AUDIT_WRITE, CAP_SETFCAP, CAP_KILL, CAP_NET_BIND_SERVICE, CAP_SYS_TIME, CAP_AUDIT_READ, CAP_PERFMON, CAP_BPF, CAP_CHECKPOINT_RESTORE};
  cap_value_t keep_caplist_extra[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    keep_caplist_extra[i] = INIT_VALUE;
  }
  cap_value_t drop_caplist_extra[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    drop_caplist_extra[i] = INIT_VALUE;
  }
  cap_value_t cap = INIT_VALUE;
  // Parse command-line arguments.
  for (int index = 1; index < argc; index++)
  {
    //==============For OPTIONS==============
    if (strcmp(argv[index], "-v") == 0)
    {
      show_version_info();
      return 0;
    }
    if (strcmp(argv[index], "-V") == 0)
    {
      show_version_code();
      return 0;
    }
    if (strcmp(argv[index], "-D") == 0)
    {
      container_daemon();
      return 0;
    }
    if (strcmp(argv[index], "-K") == 0)
    {
      kill_daemon();
      return 0;
    }
    if (strcmp(argv[index], "-h") == 0)
    {
      show_helps(true);
      return 0;
    }
    if (strcmp(argv[index], "-hh") == 0)
    {
      show_helps(true);
      show_examples();
      return 0;
    }
    if (strcmp(argv[index], "-l") == 0)
    {
      container_ps();
      return 0;
    }
    if (strcmp(argv[index], "-t") == 0)
    {
      if (geteuid() != 0)
      {
        fprintf(stderr, "\033[31mError: this program should be run with root.\033[0m\n");
        return 1;
      }
      struct sockaddr_un addr;
      if (!connect_to_daemon(&addr))
      {
        if (!no_warnings)
        {
          printf("\033[31mrurid is not running.\033[0m\n");
        }
        return 1;
      }
      if (!no_warnings)
      {
        printf("\033[1;38;2;254;228;208mrurid is running.\033[0m\n");
      }
      return 0;
    }
    if (strcmp(argv[index], "-U") == 0)
    {
      index += 1;
      if (argv[index] != NULL)
      {
        if (check_container(argv[index]))
        {
          realpath(argv[index], container_dir);
          umount_container(container_dir);
          return 0;
        }
      }
      else
      {
        error("Error: container directory is not set QwQ");
      }
    }
    //=========For [ARGS] CONTAINER_DIRECTORY [INIT_COMMAND]===========
    if (strcmp(argv[index], "-n") == 0)
    {
      no_new_privs = true;
    }
    else if (strcmp(argv[index], "-s") == 0)
    {
      enable_seccomp = true;
    }
    else if (strcmp(argv[index], "-u") == 0)
    {
      use_unshare = true;
    }
    else if (strcmp(argv[index], "-d") == 0)
    {
      for (unsigned long i = 0; i < (sizeof(drop_caplist_unprivileged) / sizeof(drop_caplist_unprivileged[0])); i++)
      {
        drop_caplist[i] = drop_caplist_unprivileged[i];
      }
    }
    else if (strcmp(argv[index], "-p") == 0)
    {
      privileged = true;
    }
    else if (strcmp(argv[index], "-w") == 0)
    {
      no_warnings = true;
    }
    else if (strcmp(argv[index], "-e") == 0)
    {
      index++;
      if ((argv[index] != NULL) && (argv[index + 1] != NULL))
      {
        for (int i = 0; i < MAX_ENVS; i++)
        {
          if (env[i] == NULL)
          {
            env[i] = strdup(argv[index]);
            index++;
            env[i + 1] = strdup(argv[index]);
            env[i + 2] = NULL;
            break;
          }
          // Max 128 envs.
          if (i == (MAX_ENVS - 1))
          {
            error("Too many envs QwQ");
          }
        }
      }
      else
      {
        error("Error: unknow env QwQ");
      }
    }
    else if (strcmp(argv[index], "-m") == 0)
    {
      index++;
      if ((argv[index] != NULL) && (argv[index + 1] != NULL))
      {
        for (int i = 0; i < MAX_MOUNTPOINTS; i++)
        {
          if (mountpoint[i] == NULL)
          {
            mountpoint[i] = strdup(argv[index]);
            index++;
            mountpoint[i + 1] = strdup(argv[index]);
            mountpoint[i + 2] = NULL;
            break;
          }
          // Max 128 mountpoints.
          if (i == (MAX_MOUNTPOINTS - 1))
          {
            error("Too many mountpoints QwQ");
          }
        }
      }
      else
      {
        error("Error: unknow mountpoint QwQ");
      }
    }
    else if (strcmp(argv[index], "--keep") == 0)
    {
      index++;
      if (argv[index] != NULL)
      {
        if (cap_from_name(argv[index], &cap) == 0)
        {
          add_to_list(keep_caplist_extra, CAP_LAST_CAP + 1, cap);
        }
        else
        {
          fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", argv[index], "`");
          error("QwQ");
        }
      }
      else
      {
        fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", "(null)", "`");
        error("QwQ");
      }
    }
    else if (strcmp(argv[index], "--drop") == 0)
    {
      index++;
      if (argv[index] != NULL)
      {
        if (cap_from_name(argv[index], &cap) == 0)
        {
          add_to_list(drop_caplist_extra, CAP_LAST_CAP + 1, cap);
        }
        else
        {
          fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", argv[index], "`");
          error("QwQ");
        }
      }
      else
      {
        fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", "(null)", "`");
        error("QwQ");
      }
    }
    else if ((strchr(argv[index], '/') && strcmp(strchr(argv[index], '/'), argv[index]) == 0) || (strchr(argv[index], '.') && strcmp(strchr(argv[index], '.'), argv[index]) == 0))
    {
      // Get the absolute path of container.
      if (check_container(argv[index]))
      {
        realpath(argv[index], container_dir);
      }
      else
      {
        exit(1);
      }
      index++;
      // Arguments after container_dir will be read as init command.
      if (argv[index])
      {
        for (int i = 0; i < argc; i++)
        {
          if (argv[index])
          {
            init[i] = argv[index];
            init[i + 1] = NULL;
            index++;
          }
          else
          {
            break;
          }
        }
      }
      else
      {
        init[0] = NULL;
      }
    }
    else
    {
      fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow option `", argv[index], "`");
      show_helps(false);
      return 1;
    }
  }
  // Check if container_dir is given.
  if (container_dir[0] == '\0')
  {
    error("Error: container directory is not set QwQ");
  }
  // Check Linux version.
  if (!no_warnings)
  {
    struct utsname uts;
    uname(&uts);
    if (atoi(&uts.release[0]) < 4)
    {
      fprintf(stderr, "\033[33mWarning: This program has not been tested on Linux 3.x or earlier.\n");
    }
  }
  // Check if init binary exists and is not a directory.
  char init_binary[PATH_MAX];
  strcpy(init_binary, container_dir);
  if (init[0] != NULL)
  {
    strcat(init_binary, init[0]);
  }
  else
  {
    strcat(init_binary, "/bin/su");
  }
  struct stat init_binary_stat;
  // lstat() will return -1 while the init_binary does not exist.
  if (lstat(init_binary, &init_binary_stat) != 0)
  {
    error("Init binary does not exist, please check if container_dir and init command are correct QwQ");
  }
  if (S_ISDIR(init_binary_stat.st_mode))
  {
    error("Init binary is a directory, RUOK? Die job death car?");
  }
  // Set default caplist to drop.
  if (!privileged && drop_caplist[0] == INIT_VALUE)
  {
    for (unsigned long i = 0; i < (sizeof(drop_caplist_common) / sizeof(drop_caplist_common[0])); i++)
    {
      drop_caplist[i] = drop_caplist_common[i];
    }
  }
  // Comply with capability-set policy specified.
  if (drop_caplist_extra[0] != INIT_VALUE)
  {
    for (unsigned long i = 0; i < (sizeof(drop_caplist_extra) / sizeof(drop_caplist_extra[0])); i++)
    {
      if (drop_caplist_extra[i] != INIT_VALUE)
      {
        add_to_list(drop_caplist, CAP_LAST_CAP + 1, drop_caplist_extra[i]);
      }
    }
  }
  if (keep_caplist_extra[0] != INIT_VALUE)
  {
    for (unsigned long i = 0; i < (sizeof(keep_caplist_extra) / sizeof(keep_caplist_extra[0])); i++)
    {
      if (keep_caplist_extra[i] != INIT_VALUE)
      {
        del_from_list(drop_caplist, CAP_LAST_CAP + 1, keep_caplist_extra[i]);
      }
    }
  }
  // Build container_info struct.
  container_info = (struct CONTAINER_INFO *)malloc(sizeof(struct CONTAINER_INFO));
  container_info->container_dir = container_dir;
  container_info->no_new_privs = no_new_privs;
  container_info->enable_seccomp = enable_seccomp;
  for (int i = 0; i <= CAP_LAST_CAP; i++)
  {
    container_info->drop_caplist[i] = drop_caplist[i];
  }
  for (int i = 0;;)
  {
    if (init[i] != NULL)
    {
      container_info->init_command[i] = strdup(init[i]);
      container_info->init_command[i + 1] = NULL;
      i++;
    }
    else
    {
      container_info->init_command[i] = NULL;
      break;
    }
  }
  for (int i = 0; i < MAX_ENVS; i++)
  {
    if (env[i] != NULL)
    {
      container_info->env[i] = strdup(env[i]);
      container_info->env[i + 1] = NULL;
    }
    else
    {
      container_info->env[i] = NULL;
      break;
    }
  }
  for (int i = 0; i < MAX_MOUNTPOINTS; i++)
  {
    if (mountpoint[i] != NULL)
    {
      container_info->mountpoint[i] = strdup(mountpoint[i]);
      container_info->mountpoint[i + 1] = NULL;
    }
    else
    {
      container_info->mountpoint[i] = NULL;
      break;
    }
  }
  // Set $PATH to the common value in GNU/Linux, because $PATH in termux will not work in GNU/Linux containers.
  setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
  // Pure-chroot and unshare container are two functions.
  if (use_unshare)
  {
    run_unshare_container(container_info, no_warnings);
  }
  else
  {
    run_chroot_container(container_info, no_warnings);
  }
  return 0;
}
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
