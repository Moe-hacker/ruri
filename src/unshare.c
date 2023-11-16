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
// For run_unshare_container().
static pid_t init_unshare_container(bool no_warnings)
{
  /*
   * Use unshare() to create new namespaces and fork() to join them.
   * Return pid of forked process.
   * unshare_pid in forked process is 0.
   */
  pid_t unshare_pid = INIT_VALUE;
  // Create namespaces.
  if (unshare(CLONE_NEWNS) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that mount namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_NEWUTS) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that uts namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_NEWIPC) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that ipc namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_NEWPID) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that pid namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_NEWCGROUP) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that cgroup namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_NEWTIME) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that time namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_SYSVSEM) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that semaphore namespace is not supported on this device QwQ\033[0m\n");
  }
  if (unshare(CLONE_FILES) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that we could not unshare file descriptors with child process QwQ\033[0m\n");
  }
  if (unshare(CLONE_FS) == -1 && !no_warnings)
  {
    printf("\033[33mWarning: seems that we could not unshare filesystem information with child process QwQ\033[0m\n");
  }
  // Fork itself into namespace.
  // This can fix `can't fork: out of memory` issue.
  unshare_pid = fork();
  // Fix `can't access tty` issue.
  if (unshare_pid > 0)
  {
    usleep(200000);
    waitpid(unshare_pid, NULL, 0);
  }
  else if (unshare_pid < 0)
  {
    error("Fork error QwQ?");
  }
  return unshare_pid;
}
// For run_unshare_container().
static pid_t join_ns_from_daemon(struct CONTAINER_INFO *container_info, struct sockaddr_un addr, bool no_warnings)
{
  /*
   * Request container_pid and other info of container from daemon, use setns() to join namespaces and then fork() itself into them.
   * If container is not running, it will send the info to daemon, and daemon will register it and send its container_pid back.
   */
  pid_t unshare_pid = INIT_VALUE;
  char msg[MSG_BUF_SIZE] = {'\000'};
  // Clear buf.
  memset(msg, '\000', MSG_BUF_SIZE);
  char *container_pid = NULL;
  send_msg_client(FROM_CLIENT__REGISTER_A_CONTAINER, addr);
  send_msg_client(container_info->container_dir, addr);
  read_msg_client(msg, addr);
  if (strcmp(msg, FROM_DAEMON__CONTAINER_NOT_RUNNING) == 0)
  {
    // Send init command to daemon.
    send_msg_client(FROM_CLIENT__INIT_COMMAND, addr);
    if (strcmp(container_info->command[0], "/bin/su") != 0)
    {
      for (int i = 0; i < 1023; i++)
      {
        if (container_info->command[i] != NULL)
        {
          send_msg_client(container_info->command[i], addr);
          free(container_info->command[i]);
          container_info->command[i] = NULL;
        }
        else
        {
          break;
        }
      }
      container_info->command[0] = strdup("/bin/su");
      container_info->command[1] = NULL;
    }
    send_msg_client(FROM_CLIENT__END_OF_INIT_COMMAND, addr);
    // Send the cap to drop to daemon.
    send_msg_client(FROM_CLIENT__CAP_TO_DROP, addr);
    if (container_info->drop_caplist[0] != INIT_VALUE)
    {
      for (int i = 0; i < CAP_LAST_CAP + 1; i++)
      {
        // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN.
        if (!container_info->drop_caplist[i])
        {
          send_msg_client(cap_to_name(0), addr);
        }
        else if (container_info->drop_caplist[i] != INIT_VALUE)
        {
          send_msg_client(cap_to_name(container_info->drop_caplist[i]), addr);
        }
        else
        {
          break;
        }
      }
    }
    send_msg_client(FROM_CLIENT__END_OF_CAP_TO_DROP, addr);
    // Send mountpoint to daemon.
    send_msg_client(FROM_CLIENT__MOUNTPOINT, addr);
    for (int i = 0; i < MAX_MOUNTPOINTS; i++)
    {
      if (container_info->mountpoint[i] != NULL)
      {
        send_msg_client(container_info->mountpoint[i], addr);
      }
      else
      {
        break;
      }
    }
    send_msg_client(FROM_CLIENT__END_OF_MOUNTPOINT, addr);
    // Send envs to daemon.
    send_msg_client(FROM_CLIENT__ENV, addr);
    for (int i = 0; i < MAX_ENVS; i++)
    {
      if (container_info->env[i] != NULL)
      {
        send_msg_client(container_info->env[i], addr);
      }
      else
      {
        break;
      }
    }
    send_msg_client(FROM_CLIENT__END_OF_ENV, addr);
    if (container_info->no_new_privs)
    {
      send_msg_client(FROM_CLIENT__NO_NEW_PRIVS_TRUE, addr);
    }
    else
    {
      send_msg_client(FROM_CLIENT__NO_NEW_PRIVS_FALSE, addr);
    }
    if (container_info->enable_seccomp)
    {
      send_msg_client(FROM_CLIENT__ENABLE_SECCOMP_TRUE, addr);
    }
    else
    {
      send_msg_client(FROM_CLIENT__ENABLE_SECCOMP_FALSE, addr);
    }
  }
  else
  {
    for (int i = 0; i < MAX_ENVS; i++)
    {
      read_msg_client(msg, addr);
      if (strcmp(msg, FROM_DAEMON__END_OF_ENV) == 0)
      {
        break;
      }
      container_info->env[i] = strdup(msg);
      container_info->env[i + 1] = NULL;
    }
    read_msg_client(msg, addr);
    for (int i = 0;;)
    {
      read_msg_client(msg, addr);
      if (strcmp(msg, FROM_DAEMON__END_OF_CAP_TO_DROP) == 0)
      {
        break;
      }
      cap_from_name(msg, &container_info->drop_caplist[i]);
      container_info->drop_caplist[i + 1] = INIT_VALUE;
      i++;
    }
    read_msg_client(msg, addr);
    if (strcmp(msg, FROM_DAEMON__NO_NEW_PRIVS_TRUE) != 0)
    {
      container_info->no_new_privs = false;
    }
    read_msg_client(msg, addr);
    if (strcmp(msg, FROM_DAEMON__ENABLE_SECCOMP_TRUE) != 0)
    {
      container_info->enable_seccomp = false;
    }
  }
  // Fix a bug that read_msg_client() returns NULL because container has not been registered properly.
  usleep(400000);
  // Ignore FROM_DAEMON__UNSHARE_CONTAINER_PID.
  read_msg_client(msg, addr);
  // Pid for setns().
  read_msg_client(msg, addr);
  container_pid = strdup(msg);
#ifdef __RURI_DEV__
  printf("%s%s\033[0m\n", "\033[1;38;2;254;228;208mContainer pid from daemon:\033[1;38;2;152;245;225m", container_pid);
#endif
  // Use setns() to enter namespaces created by daemon.
  char cgroup_ns_file[PATH_MAX] = {'\000'};
  char ipc_ns_file[PATH_MAX] = {'\000'};
  char mount_ns_file[PATH_MAX] = {'\000'};
  char pid_ns_file[PATH_MAX] = {'\000'};
  char time_ns_file[PATH_MAX] = {'\000'};
  char uts_ns_file[PATH_MAX] = {'\000'};
  sprintf(cgroup_ns_file, "%s%s%s", "/proc/", container_pid, "/ns/cgroup");
  sprintf(ipc_ns_file, "%s%s%s", "/proc/", container_pid, "/ns/ipc");
  sprintf(mount_ns_file, "%s%s%s", "/proc/", container_pid, "/ns/mnt");
  sprintf(pid_ns_file, "%s%s%s", "/proc/", container_pid, "/ns/pid");
  sprintf(time_ns_file, "%s%s%s", "/proc/", container_pid, "/ns/time");
  sprintf(uts_ns_file, "%s%s%s", "/proc/", container_pid, "/ns/uts");
  free(container_pid);
  container_pid = NULL;
  int fd = INIT_VALUE;
  fd = open(mount_ns_file, O_RDONLY | O_CLOEXEC);
  if (fd < 0 && !no_warnings)
  {
    printf("\033[33mWarning: seems that mount namespace is not supported on this device QwQ\033[0m\n");
  }
  else
  {
    setns(fd, 0);
  }
  fd = open(pid_ns_file, O_RDONLY | O_CLOEXEC);
  if (fd < 0 && !no_warnings)
  {
    printf("\033[33mWarning: seems that pid namespace is not supported on this device QwQ\033[0m\n");
  }
  else
  {
    setns(fd, 0);
  }
  fd = open(time_ns_file, O_RDONLY | O_CLOEXEC);
  if (fd < 0 && !no_warnings)
  {
    printf("\033[33mWarning: seems that time namespace is not supported on this device QwQ\033[0m\n");
  }
  else
  {
    setns(fd, 0);
  }
  fd = open(uts_ns_file, O_RDONLY | O_CLOEXEC);
  if (fd < 0 && !no_warnings)
  {
    printf("\033[33mWarning: seems that uts namespace is not supported on this device QwQ\033[0m\n");
  }
  else
  {
    setns(fd, 0);
  }
  fd = open(cgroup_ns_file, O_RDONLY | O_CLOEXEC);
  if (fd < 0 && !no_warnings)
  {
    printf("\033[33mWarning: seems that cgroup namespace is not supported on this device QwQ\033[0m\n");
  }
  else
  {
    setns(fd, 0);
  }
  fd = open(ipc_ns_file, O_RDONLY | O_CLOEXEC);
  if (fd < 0 && !no_warnings)
  {
    printf("\033[33mWarning: seems that ipc namespace is not supported on this device QwQ\033[0m\n");
  }
  else
  {
    setns(fd, 0);
  }
  // Close fds after fork().
  unshare(CLONE_FILES);
  // Fork itself into namespace.
  // This can fix `can't fork: out of memory` issue.
  unshare_pid = fork();
  // Fix `can't access tty` issue.
  if (unshare_pid > 0)
  {
    usleep(200000);
    waitpid(unshare_pid, NULL, 0);
    usleep(200000);
    send_msg_client(FROM_CLIENT__IS_INIT_ACTIVE, addr);
    send_msg_client(container_info->container_dir, addr);
    read_msg_client(msg, addr);
    if (strcmp(msg, FROM_DAEMON__INIT_IS_ACTIVE) != 0)
    {
      error("Error: Init process died QwQ");
    }
  }
  else if (unshare_pid < 0)
  {
    error("Fork error QwQ?");
    return 1;
  }
  return unshare_pid;
}
// Run unshare container.
int run_unshare_container(struct CONTAINER_INFO *container_info, const bool no_warnings)
{
  /*
   * If daemon is not running, it will create namespaces itself.
   * Or it will connect to daemon and use setns() to join namespaces created by daemon.
   * After fork() to send itself to new namespaces, it will call to run_chroot_container().
   */
  // Set default init.
  if (container_info->command[0] == NULL)
  {
    container_info->command[0] = strdup("/bin/su");
    container_info->command[1] = NULL;
  }
#ifdef __RURI_DEV__
  printf("\033[1;38;2;254;228;208mRun unshare container:\n");
  printf("%s%s\n", "\033[1;38;2;254;228;208mcontainer_dir: \033[1;38;2;152;245;225m", container_info->container_dir);
  printf("\033[1;38;2;254;228;208minit command : \033[1;38;2;152;245;225m");
  for (int i = 0;;)
  {
    if (container_info->command[i] != NULL)
    {
      printf("%s%s", container_info->command[i], " ");
      i++;
    }
    else
    {
      printf("\n");
      break;
    }
  }
  printf("\033[1;38;2;254;228;208mdrop caplist: \033[1;38;2;152;245;225m");
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
#endif
  pid_t unshare_pid = INIT_VALUE;
  // Set socket address.
  struct sockaddr_un addr;
  bool daemon_running = false;
  if (connect_to_daemon(&addr) == 0)
  {
    daemon_running = true;
  }
  else
  {
    if (!no_warnings)
    {
      printf("\033[33mWarning: seems that container daemon is not running QwQ\033[0m\n");
    }
  }
  // Unshare() itself into new namespaces.
  if (!daemon_running)
  {
    unshare_pid = init_unshare_container(no_warnings);
  }
  else
  {
    unshare_pid = join_ns_from_daemon(container_info, addr, no_warnings);
  }
  // Check if unshare is enabled.
  if (unshare_pid == 0)
  {
    usleep(200000);
    run_chroot_container(container_info, no_warnings);
  }
  return 0;
}