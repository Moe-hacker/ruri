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
// Add a node to CONTAINERS struct.
struct CONTAINERS *register_container(char *container_dir, char *unshare_pid, char drop_caplist[CAP_LAST_CAP + 1][128], char *env[MAX_ENVS], char mountpoint[MAX_MOUNTPOINTS][PATH_MAX], bool no_new_privs, bool enable_seccomp, struct CONTAINERS *container)
{
  /*
   * Use malloc() to request the memory of the node and then add container info to node.
   * If current node is already used, try the next one.
   * The next node of the node added will be NULL.
   */
  // If current node is NULL, add container info here.
  if (container == NULL)
  {
    // Request memory of container struct.
    container = (struct CONTAINERS *)malloc(sizeof(struct CONTAINERS));
    // Add info of container.
    container->container_dir = strdup(container_dir);
    container->unshare_pid = strdup(unshare_pid);
    container->no_new_privs = no_new_privs;
    container->enable_seccomp = enable_seccomp;
    for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
    {
      if (drop_caplist[i][0] != '\0')
      {
        container->drop_caplist[i] = malloc(sizeof(char) * (strlen(drop_caplist[i]) + 1));
        strcpy(container->drop_caplist[i], drop_caplist[i]);
      }
      else
      {
        container->drop_caplist[i] = NULL;
        break;
      }
    }
    for (int i = 0; i < MAX_ENVS; i++)
    {
      if (env[i] != NULL)
      {
        container->env[i] = malloc(sizeof(char) * (strlen(env[i]) + 1));
        strcpy(container->env[i], env[i]);
      }
      else
      {
        container->env[i] = NULL;
        break;
      }
    }
    for (int i = 0; i < MAX_MOUNTPOINTS; i++)
    {
      if (mountpoint[i][0] != '\0')
      {
        container->mountpoint[i] = malloc(sizeof(char) * (strlen(mountpoint[i]) + 1));
        strcpy(container->mountpoint[i], mountpoint[i]);
      }
      else
      {
        container->mountpoint[i] = NULL;
        break;
      }
    }
    container->container = NULL;
    // Return node added.
    return container;
  }
  // If current node is not NULL, try the next.
  container->container = register_container(container_dir, unshare_pid, drop_caplist, env, mountpoint, no_new_privs, enable_seccomp, container->container);
  return container;
}
// Return info of a container.
struct CONTAINERS *get_container_info(char *container_dir, struct CONTAINERS *container)
{
  /*
   * It will return the node that matches the container_dir.
   * NULL pointer will be returned if reaching the end of all nodes.
   * However, as container_active() will be run before it to check if container's running, NULL pointer will never be returned.
   */
  if (container != NULL)
  {
    // If container matches container_dir.
    if (strcmp(container->container_dir, container_dir) == 0)
    {
      return container;
    }
    // If not, try the next node.
    return get_container_info(container_dir, container->container);
  }
  // Will never be run.
  return NULL;
}
// Delete a container from CONTAINERS struct.
struct CONTAINERS *deregister_container(char *container_dir, struct CONTAINERS *container)
{
  /*
   * If container is a NULL pointer, just quit, but this will never happen.
   * Or it will find the node that matching container_dir , free() its memory and use the next node to overwrite it.
   * NULL pointer will be returned if reached the end of all nodes.
   * However, as container_active() will be run before it to check if container's running, NULL pointer will never be returned.
   */
  // It will never be true.
  if (container == NULL)
  {
    return container;
  }
  // If container is the struct to delete.
  if (strcmp(container->container_dir, container_dir) == 0)
  {
    struct CONTAINERS *next_node = container->container;
    free(container);
    container = next_node;
  }
  // If not, try the next struct.
  else
  {
    container->container = deregister_container(container_dir, container->container);
  }
  return container;
}
// Check if a container is running.
bool container_active(char *container_dir, struct CONTAINERS *container)
{
  /*
   * If there's a node that matches container_dir, it will return true.
   * Or it will return false.
   * It's used to determine whether a container is running.
   */
  // Reached the end of container struct.
  if (container == NULL)
  {
    return false;
  }
  // If container matches container_dir.
  if (strcmp(container->container_dir, container_dir) == 0)
  {
    return true;
  }
  // If not, try the next struct.
  return container_active(container_dir, container->container);
}
// For container_ps().
void read_all_nodes(struct CONTAINERS *container, struct sockaddr_un addr, int sockfd)
{
  /*
   * It will read all nodes in container struct and send them to ruri.
   * If it reaches the end of container struct, send `endps`.
   */
  // Reached the end of container struct.
  if (container == NULL)
  {
    send_msg_daemon(FROM_DAEMON__END_OF_PS_INFO, addr, sockfd);
    return;
  }
  // Send info to ruri.
  send_msg_daemon(container->container_dir, addr, sockfd);
  send_msg_daemon(container->unshare_pid, addr, sockfd);
  // Read the next node.
  read_all_nodes(container->container, addr, sockfd);
}
// For container_daemon(), kill & umount all containers.
void umount_all_containers(struct CONTAINERS *container)
{
  /*
   * Kill and umount all containers.
   * container_daemon() will exit after calling to this function, so free() is needless here.
   */
  if (container == NULL)
  {
    return;
  }
  kill(atoi(container->unshare_pid), SIGKILL);
  // Umount other mountpoints.
  char buf[PATH_MAX];
  for (int i = 0;;)
  {
    if (container->mountpoint[i] != NULL)
    {
      strcpy(buf, container->container_dir);
      strcat(buf, container->mountpoint[i + 1]);
      i += 2;
      for (int j = 0; j < 10; j++)
      {
        umount2(buf, MNT_DETACH | MNT_FORCE);
        umount(buf);
      }
    }
    else
    {
      break;
    }
  }
  // Get path to umount.
  char sys_dir[PATH_MAX];
  char proc_dir[PATH_MAX];
  char dev_dir[PATH_MAX];
  strcpy(sys_dir, container->container_dir);
  strcpy(proc_dir, container->container_dir);
  strcpy(dev_dir, container->container_dir);
  strcat(sys_dir, "/sys");
  strcat(proc_dir, "/proc");
  strcat(dev_dir, "/dev");
  // Force umount all directories for 10 times.
  for (int i = 1; i < 10; i++)
  {
    umount2(sys_dir, MNT_DETACH | MNT_FORCE);
    umount2(dev_dir, MNT_DETACH | MNT_FORCE);
    umount2(proc_dir, MNT_DETACH | MNT_FORCE);
    umount2(container->container_dir, MNT_DETACH | MNT_FORCE);
  }
  umount_all_containers(container->container);
}
// For daemon, init an unshare container in the background.
void *daemon_init_unshare_container(void *arg)
{
  /*
   * It is called as a child process of container_daemon().
   * It will call to unshare() and send unshare_pid after fork() and other information to daemon.
   * and call to run_chroot_container() to exec init command.
   * Note that on the devices that has pid ns enabled, if init process died, all processes in the container will be die.
   */
  // pthread_create() only allows one argument.
  struct CONTAINER_INFO *container_info = (struct CONTAINER_INFO *)arg;
  // Try to create namespaces with unshare(), no warnings to show because daemon will be run in the background.
  if (unshare(CLONE_NEWNS) == -1)
  {
    error("mount ns does not supported on this device!");
  }
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
  if (unshare_pid > 0)
  {
    char *container_dir = strdup(container_info->container_dir);
    // Set socket address.
    struct sockaddr_un addr;
    connect_to_daemon(&addr);
    char container_pid[1024];
    sprintf(container_pid, "%d", unshare_pid);
    // Register the container into daemon's CONTAINERS struct.
    send_msg_client(FROM_PTHREAD__REGISTER_CONTAINER, addr);
    send_msg_client(FROM_PTHREAD__UNSHARE_CONTAINER_PID, addr);
    send_msg_client(container_pid, addr);
    send_msg_client(container_info->container_dir, addr);
    send_msg_client(FROM_PTHREAD__CAP_TO_DROP, addr);
    if (container_info->drop_caplist[0] != INIT_VALUE)
    {
      for (int i = 0; i < CAP_LAST_CAP; i++)
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
    send_msg_client(FROM_PTHREAD__END_OF_CAP_TO_DROP, addr);
    send_msg_client(FROM_PTHREAD__MOUNTPOINT, addr);
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
    send_msg_client(FROM_PTHREAD__END_OF_MOUNTPOINT, addr);
    send_msg_client(FROM_PTHREAD__ENV, addr);
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
    send_msg_client(FROM_PTHREAD__END_OF_ENV, addr);
    if (container_info->no_new_privs != false)
    {
      send_msg_client(FROM_PTHREAD__NO_NEW_PRIVS_TRUE, addr);
    }
    else
    {
      send_msg_client(FROM_PTHREAD__NO_NEW_PRIVS_FALSE, addr);
    }
    if (container_info->enable_seccomp != false)
    {
      send_msg_client(FROM_PTHREAD__ENABLE_SECCOMP_TRUE, addr);
    }
    else
    {
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
  }
  else if (unshare_pid == 0)
  {
    // The things to do next is same as a chroot container.
    run_chroot_container(container_info, true);
  }
  return 0;
}
// Daemon process used to store unshare container information and init unshare container.
void container_daemon()
{
  /*
   * 100% shit code at container_daemon.
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
  // For pthread_create().
  pthread_t pthread_id = 0;
  // Check if we are running with root privileges.
  if (getuid() != 0)
  {
    error("Error: this program should be run with root privileges QwQ");
  }
  // Check if $LD_PRELOAD is unset.
  char *ld_preload = getenv("LD_PRELOAD");
  if ((ld_preload != NULL) && (strcmp(ld_preload, "") != 0))
  {
    error("Error: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run QwQ");
  }
  // Create container struct.
  struct CONTAINERS *container = NULL;
  // Message to read.
  char *msg = NULL;
  // Container info.
  char *container_dir = NULL;
  // Info of a new container.
  struct CONTAINER_INFO container_info;
  container_info.container_dir = NULL;
  container_info.init_command[0] = NULL;
  container_info.unshare_pid = NULL;
  container_info.mountpoint[0] = NULL;
  container_info.env[0] = NULL;
  for (int i = 0; i < (CAP_LAST_CAP); i++)
  {
    container_info.drop_caplist[i] = INIT_VALUE;
  }
  pid_t unshare_pid = 0;
  char drop_caplist[CAP_LAST_CAP + 1][128];
  drop_caplist[0][0] = '\0';
  char *env[MAX_ENVS] = {NULL};
  char mountpoint[MAX_MOUNTPOINTS][PATH_MAX];
  mountpoint[0][0] = '\0';
  bool no_new_privs = false;
  bool enable_seccomp = false;
  // Create socket.
  int sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
  if (sockfd < 0)
  {
    error("Error: cannot create socket QwQ");
  }
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp.
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  // Set socket path.
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/");
  strcat(socket_path, SOCKET_FILE);
  strcpy(addr.sun_path, socket_path);
  // Check if container daemon is already running.
  send_msg_client(FROM_CLIENT__TEST_MESSAGE, addr);
  msg = read_msg_client(addr);
  if ((msg != NULL) && (strcmp(FROM_DAEMON__TEST_MESSAGE, msg) == 0))
  {
    close(sockfd);
    error("Daemon already running QwQ");
  }
  free(msg);
  msg = NULL;
  // Fork() itself into the background.
  // It's really a daemon now, because its parent process will be init.
  pid_t pid = fork();
  if (pid > 0)
  {
    return;
  }
  if (pid < 0)
  {
    perror("fork");
    return;
  }
  // Create socket file.
  remove(socket_path);
  unlink(socket_path);
  if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0)
  {
    perror("bind");
    return;
  }
  listen(sockfd, 16);
  // Read message from ruri.
  while (true)
  {
    // Get message.
    msg = NULL;
    msg = read_msg_daemon(addr, sockfd);
    // Avoid crashes by null pointer.
    if (msg == NULL)
    {
      goto _continue;
    }
    // Test message, to check if daemon is active.
    else if (strcmp(FROM_CLIENT__TEST_MESSAGE, msg) == 0)
    {
      free(msg);
      msg = NULL;
      send_msg_daemon(FROM_DAEMON__TEST_MESSAGE, addr, sockfd);
      goto _continue;
    }
    // Kill a container.
    else if (strcmp(FROM_CLIENT__KILL_A_CONTAINER, msg) == 0)
    {
      free(msg);
      msg = NULL;
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_dir = strdup(msg);
      free(msg);
      msg = NULL;
      // Check if container is active.
      if (container_active(container_dir, container))
      {
        // Kill container.
        // It will just kill init process, so on devices which has no pid ns enabled, some process in container will still be alive.
        unshare_pid = atoi(get_container_info(container_dir, container)->unshare_pid);
        kill(unshare_pid, SIGKILL);
        send_msg_daemon(FROM_DAEMON__CONTAINER_KILLED, addr, sockfd);
        // Extra mountpoints will also be umounted in ruri client.
        send_msg_daemon(FROM_DAEMON__MOUNTPOINT, addr, sockfd);
        for (int i = 0;;)
        {
          if (get_container_info(container_dir, container)->mountpoint[i] != NULL)
          {
            send_msg_daemon(get_container_info(container_dir, container)->mountpoint[i + 1], addr, sockfd);
            i += 2;
          }
          else
          {
            break;
          }
        }
        send_msg_daemon(FROM_DAEMON__END_OF_MOUNTPOINT, addr, sockfd);
        // Deregister the container.
        container = deregister_container(container_dir, container);
      }
      else
      {
        send_msg_daemon(FROM_DAEMON__CONTAINER_NOT_RUNNING, addr, sockfd);
      }
      free(container_dir);
      container_dir = NULL;
      goto _continue;
    }
    // Register a new container or send the info of an existing container to ruri.
    else if (strcmp(FROM_CLIENT__REGISTER_A_CONTAINER, msg) == 0)
    {
      free(msg);
      msg = NULL;
      // Get container_dir.
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_dir = strdup(msg);
      free(msg);
      msg = NULL;
      // If container is active, send unshare_pid and other info to client.
      if (container_active(container_dir, container))
      {
        send_msg_daemon(FROM_DAEMON__ENV, addr, sockfd);
        for (int i = 0; i < MAX_ENVS; i++)
        {
          if (get_container_info(container_dir, container)->env[i] != NULL)
          {
            send_msg_daemon(get_container_info(container_dir, container)->env[i], addr, sockfd);
          }
          else
          {
            break;
          }
        }
        send_msg_daemon(FROM_DAEMON__END_OF_ENV, addr, sockfd);
        send_msg_daemon(FROM_DAEMON__CAP_TO_DROP, addr, sockfd);
        for (int i = 0;;)
        {
          if (get_container_info(container_dir, container)->drop_caplist[i] != NULL)
          {
            send_msg_daemon(get_container_info(container_dir, container)->drop_caplist[i], addr, sockfd);
            i++;
          }
          else
          {
            break;
          }
        }
        send_msg_daemon(FROM_DAEMON__END_OF_CAP_TO_DROP, addr, sockfd);
        if (get_container_info(container_dir, container)->no_new_privs != false)
        {
          send_msg_daemon(FROM_DAEMON__NO_NEW_PRIVS_TRUE, addr, sockfd);
        }
        else
        {
          send_msg_daemon(FROM_DAEMON__NO_NEW_PRIVS_FALSE, addr, sockfd);
        }
        if (get_container_info(container_dir, container)->enable_seccomp != false)
        {
          send_msg_daemon(FROM_DAEMON__ENABLE_SECCOMP_TRUE, addr, sockfd);
        }
        else
        {
          send_msg_daemon(FROM_DAEMON__ENABLE_SECCOMP_FALSE, addr, sockfd);
        }
        send_msg_daemon(FROM_DAEMON__UNSHARE_CONTAINER_PID, addr, sockfd);
        send_msg_daemon(get_container_info(container_dir, container)->unshare_pid, addr, sockfd);
        free(container_dir);
        container_dir = NULL;
        goto _continue;
      }
      // If container is not active, init and register it.
      else
      {
        container_info.container_dir = strdup(container_dir);
        free(container_dir);
        send_msg_daemon(FROM_DAEMON__CONTAINER_NOT_RUNNING, addr, sockfd);
        container_info.init_command[0] = NULL;
        container_info.unshare_pid = NULL;
        for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
        {
          container_info.drop_caplist[i] = INIT_VALUE;
        }
        // Read init command.
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        free(msg);
        // Get init command.
        for (int i = 0;;)
        {
          msg = read_msg_daemon(addr, sockfd);
          if (msg == NULL)
          {
            goto _continue;
          }
          if (strcmp(FROM_CLIENT__END_OF_INIT_COMMAND, msg) == 0)
          {
            free(msg);
            msg = NULL;
            break;
          }
          container_info.init_command[i] = strdup(msg);
          container_info.init_command[i + 1] = NULL;
          free(msg);
          msg = NULL;
          i++;
        }
        if (container_info.init_command[0] == NULL)
        {
          container_info.init_command[0] = "/bin/sh";
          container_info.init_command[1] = "-c";
          container_info.init_command[2] = "while :;do sleep 100s;done";
          container_info.init_command[3] = NULL;
        }
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        free(msg);
        // Get caps to drop.
        for (int i = 0;;)
        {
          msg = read_msg_daemon(addr, sockfd);
          if (msg == NULL)
          {
            goto _continue;
          }
          if (strcmp(FROM_CLIENT__END_OF_CAP_TO_DROP, msg) == 0)
          {
            container_info.drop_caplist[i] = INIT_VALUE;
            free(msg);
            msg = NULL;
            break;
          }
          cap_from_name(msg, &container_info.drop_caplist[i]);
          container_info.drop_caplist[i + 1] = INIT_VALUE;
          free(msg);
          msg = NULL;
          i++;
        }
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        free(msg);
        // Get mountpoints.
        for (int i = 0;;)
        {
          msg = read_msg_daemon(addr, sockfd);
          if (msg == NULL)
          {
            goto _continue;
          }
          if (strcmp(FROM_CLIENT__END_OF_MOUNTPOINT, msg) == 0)
          {
            free(msg);
            msg = NULL;
            break;
          }
          container_info.mountpoint[i] = strdup(msg);
          container_info.mountpoint[i + 1] = NULL;
          free(msg);
          msg = NULL;
          i++;
        }
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        free(msg);
        // Get envs.
        for (int i = 0;;)
        {
          msg = read_msg_daemon(addr, sockfd);
          if (msg == NULL)
          {
            goto _continue;
          }
          if (strcmp(FROM_CLIENT__END_OF_ENV, msg) == 0)
          {
            free(msg);
            msg = NULL;
            break;
          }
          container_info.env[i] = strdup(msg);
          container_info.env[i + 1] = NULL;
          free(msg);
          msg = NULL;
          i++;
        }
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        if (strcmp(FROM_CLIENT__NO_NEW_PRIVS_TRUE, msg) == 0)
        {
          container_info.no_new_privs = true;
        }
        else
        {
          container_info.no_new_privs = false;
        }
        free(msg);
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        if (strcmp(FROM_CLIENT__ENABLE_SECCOMP_TRUE, msg) == 0)
        {
          container_info.enable_seccomp = true;
        }
        else
        {
          container_info.enable_seccomp = false;
        }
        free(msg);
        msg = NULL;
        // Init container in new pthread.
        // It will send all the info of the container back to register it.
        pthread_create(&pthread_id, NULL, daemon_init_unshare_container, (void *)&container_info);
        goto _continue;
      }
      goto _continue;
    }
    // Get container info from subprocess and add them to container struct.
    else if (strcmp(FROM_PTHREAD__REGISTER_CONTAINER, msg) == 0)
    {
      free(msg);
      // Ignore FROM_PTHREAD__UNSHARE_CONTAINER_PID.
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      free(msg);
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_info.unshare_pid = strdup(msg);
      free(msg);
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_info.container_dir = strdup(msg);
      free(msg);
      // Ignore FROM_PTHREAD__CAP_TO_DROP
      msg = read_msg_daemon(addr, sockfd);
      free(msg);
      if (msg == NULL)
      {
        goto _continue;
      }
      // Get caps to drop.
      for (int i = 0;;)
      {
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        if (strcmp(FROM_PTHREAD__END_OF_CAP_TO_DROP, msg) == 0)
        {
          drop_caplist[i][0] = '\0';
          free(msg);
          msg = NULL;
          break;
        }
        strcpy(drop_caplist[i], msg);
        drop_caplist[i + 1][0] = '\0';
        free(msg);
        msg = NULL;
        i++;
      }
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      free(msg);
      msg = NULL;
      // Get mountpoints.
      for (int i = 0;;)
      {
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        if (strcmp(FROM_PTHREAD__END_OF_MOUNTPOINT, msg) == 0)
        {
          mountpoint[i][0] = '\0';
          free(msg);
          msg = NULL;
          break;
        }
        strcpy(mountpoint[i], msg);
        free(msg);
        msg = NULL;
        i++;
      }
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      free(msg);
      // Get envs.
      for (int i = 0;;)
      {
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        if (strcmp(FROM_PTHREAD__END_OF_ENV, msg) == 0)
        {
          free(msg);
          msg = NULL;
          break;
        }
        env[i] = strdup(msg);
        env[i + 1] = NULL;
        free(msg);
        msg = NULL;
        i++;
      }
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      if (strcmp(FROM_PTHREAD__NO_NEW_PRIVS_TRUE, msg) == 0)
      {
        no_new_privs = true;
      }
      else
      {
        no_new_privs = false;
      }
      free(msg);
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      if (strcmp(FROM_PTHREAD__ENABLE_SECCOMP_TRUE, msg) == 0)
      {
        enable_seccomp = true;
      }
      else
      {
        enable_seccomp = false;
      }
      free(msg);
      msg = NULL;
      // Register the container.
      container = register_container(container_info.container_dir, container_info.unshare_pid, drop_caplist, env, mountpoint, no_new_privs, enable_seccomp, container);
      // Send unshare_pid to ruri.
      usleep(200000);
      send_msg_daemon(FROM_DAEMON__UNSHARE_CONTAINER_PID, addr, sockfd);
      send_msg_daemon(container_info.unshare_pid, addr, sockfd);
      container_info.container_dir = NULL;
      container_info.init_command[0] = NULL;
      container_info.unshare_pid = NULL;
      for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
      {
        container_info.drop_caplist[i] = INIT_VALUE;
      }
      for (int i = 0; i < MAX_MOUNTPOINTS; i++)
      {
        mountpoint[i][0] = '\0';
      }
      goto _continue;
    }
    // Kill daemon itself.
    else if (strcmp(FROM_CLIENT__KILL_DAEMON, msg) == 0)
    {
      free(msg);
      msg = NULL;
      umount_all_containers(container);
      // Exit daemon.
      remove(addr.sun_path);
      exit(EXIT_SUCCESS);
    }
    // Get ps info of all registered containers.
    else if (strcmp(FROM_CLIENT__GET_PS_INFO, msg) == 0)
    {
      free(msg);
      msg = NULL;
      read_all_nodes(container, addr, sockfd);
      goto _continue;
    }
    // If init process died, deregister the container.
    else if (strcmp(FROM_PTHREAD__INIT_PROCESS_DIED, msg) == 0)
    {
      free(msg);
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_dir = strdup(msg);
      free(msg);
      msg = NULL;
      container = deregister_container(container_dir, container);
      goto _continue;
    }
    // Check if init process is active.
    else if (strcmp(FROM_CLIENT__IS_INIT_ACTIVE, msg) == 0)
    {
      free(msg);
      msg = NULL;
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_dir = strdup(msg);
      free(msg);
      msg = NULL;
      if (container_active(container_dir, container))
      {
        send_msg_daemon(FROM_DAEMON__INIT_IS_ACTIVE, addr, sockfd);
      }
      else
      {
        send_msg_daemon(FROM_DAEMON__INIT_IS_NOT_ACTIVE, addr, sockfd);
      }
      goto _continue;
    }
    // Continue the loop.
  _continue:
    free(msg);
    msg = NULL;
  }
}