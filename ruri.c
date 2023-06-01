// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri.
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
 */
#include "ruri.h"
/*
 * The macro __CONTAINER_DEV__ will enable extra logs if it's enabled.
 */
// For centering output.
void show_n_spaces(int n)
{
  /*
   * In fact it's needless.
   * But when I wrote it, I didn't know what's strcat. So it has been kept.
   */
  int count;
  for (count = 1; count <= n; count++)
  {
    printf(" ");
  }
  return;
}
// Greeting information.
// As an easter agg.
void show_greetings(void)
{
  /*
   * Nothing's useful at this function, just for fun.
   */
  // Get the size of terminal.
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  short row = size.ws_col;
  // For centering output.
  row -= 44;
  row /= 2;
  show_n_spaces(row);
  printf("%s\n", "\033[1;38;2;66;66;66m               ▅▅▀▀▀▀▀▀▀▀▀▀▀▀▅");
  show_n_spaces(row);
  printf("%s\n", "          ▅▅▀▀▀               ▀▀▅▅");
  show_n_spaces(row);
  printf("%s\n", "     ▅▅▅▀▀            ▅           ▀▅");
  show_n_spaces(row);
  printf("%s\n", "      ▅▀      ▅▀█▅▅▀▀▅▀▅        ▅▅  ▀▅");
  show_n_spaces(row);
  printf("%s\n", "     ▅▀   █▅▀▀  ▀     ▀ ▀▀▅▅    █ ▀▀▅ █");
  show_n_spaces(row);
  printf("%s\n", "    ▅▀   ▅▀  ▅▀      ▀▅    ▀▅   █▅███▀█");
  show_n_spaces(row);
  printf("%s\n", "  ▅▅█▀▅ █ ▅▅▀          ▀▀   █   ████   █");
  show_n_spaces(row);
  printf("%s\n", "      █ █ ▅▅▅▅▅        ▅▅▅▅▅ █  ▀█▀    █");
  show_n_spaces(row);
  printf("%s\n", "      █ █▀ ▅▅▅ ▀      ▀ ▅▅▅ ▀█   █     █");
  show_n_spaces(row);
  printf("%s\n", "      █ █ █\033[40;31m█▀█\033[0m\033[1;38;2;66;66;66m█        █\033[40;31m█▀█\033[0m\033[1;38;2;66;66;66m█ █   █     █");
  show_n_spaces(row);
  printf("%s\n", "     █  █ █\033[31m███\033[1;38;2;66;66;66m█        █\033[31m███\033[1;38;2;66;66;66m█ █   █     ▀▅");
  show_n_spaces(row);
  printf("%s\n", "    ▅▀  █  ▀▀▀          ▀▀▀  █   █      █");
  show_n_spaces(row);
  printf("%s\n", "  ▅▀▅▀ █                     █   █      █");
  show_n_spaces(row);
  printf("%s\n", " █   █ ▀▅ ▅▀▅   ▅▀▅   ▅▅     █   █      ▀▅");
  show_n_spaces(row);
  printf("%s\n", "▅█▅▅██▅ ▅██  ▀███ ▅████ ▀▅█▀▅▀   █       ▀▅");
  show_n_spaces(row);
  printf("%s\n", "███████ ▀██████████████████▀▀             █");
  show_n_spaces(row);
  printf("%s\n", " █    ▀▅  ██▀ ▀██▀▀██▀▀██▀█     █▀         █");
  show_n_spaces(row);
  printf("%s\n", " ▀▅     ▀▀█              ▅▀     █          █");
  show_n_spaces(row);
  printf("%s\n", "   ▀▅    █               █     ██        ▅▀");
  show_n_spaces(row);
  printf("%s\n", "     ▀▅▅▅▀                ▀▀▀▀▀ █        █");
  show_n_spaces(row);
  printf("%s\n", "        ▀                       ▀        ▀");
  show_n_spaces(row);
  printf("%s\n", "");
  return;
}
// For `ruri -v`.
void show_version_info(void)
{
  /*
   * Just show version info and license.
   * Version info is defined in macro CONTAINER_VERSION.
   */
  printf("\033[1;38;2;254;228;208m%s%s%s", "ruri ", CONTAINER_VERSION, "\n");
  printf("Copyright (C) 2022-2023 Moe-hacker\n");
  printf("\n");
  printf("Permission is hereby granted, free of charge, to any person obtaining a copy\n");
  printf("of this software and associated documentation files (the \"Software\"), to deal\n");
  printf("in the Software without restriction, including without limitation the rights\n");
  printf("to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n");
  printf("copies of the Software, and to permit persons to whom the Software is\n");
  printf("furnished to do so, subject to the following conditions:\n");
  printf("\n");
  printf("The above copyright notice and this permission notice shall be included in all\n");
  printf("copies or substantial portions of the Software.\n");
  printf("\n");
  printf("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n");
  printf("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n");
  printf("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n");
  printf("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n");
  printf("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n");
  printf("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n");
  printf("SOFTWARE.\033[0m\n");
  return;
}
// For `ruri -h`.
void show_helps(bool greetings)
{
  /*
   * Help page of ruri.
   * It needs to be perfected.
   */
  // Do not show greeting if command-line args are wrong.
  if (greetings)
  {
    show_greetings();
  }
  printf("\033[1;38;2;254;228;208mUsage:\n");
  printf("  ruri [Other options] [<Args> <container directory> <init command>]\n");
  printf("Other options:\n");
  printf("  -v                    :Show version info\n");
  printf("  -h                    :Show helps\n");
  printf("  -D                    :Run rurid\n");
  printf("  -K                    :Kill rurid\n");
  printf("  -l                    :List all running unshare containers\n");
  printf("  -U [container_dir]    :Umount&kill a container\n");
  printf("Args for running a container:\n");
  printf("  -u                    :Enable unshare feature\n");
  printf("  -d                    :Drop more capabilities for better security\n");
  printf("  -p                    :Run privileged container\n");
  printf(" --keep [cap]           :Keep the specified cap\n");
  printf(" --drop [cap]           :Drop the specified cap\n");
  printf("  -e [env] [value]      :Set env to its value\n");
  printf("  -m [dir] [mountpoint] :Mount dir to mountpoint\n");
  printf("  -w                    :Disable warnings\n");
  printf("This program should be run with root privileges\n");
  printf("Please unset $LD_PRELOAD before running this program\033[0m\n");
  return;
}
// Add a cap to caplist.
void add_to_list(cap_value_t *list, int length, cap_value_t cap)
{
  /*
   * If the cap is already in list, just do nothing and quit.
   * Caps are initialized by INIT_VALUE, the INIT_VALUE will be ignored when dropping caps.
   */
#ifdef __CONTAINER_DEV__
  printf("Add %s to drop_caplist.\n", cap_to_name(cap));
#endif
  bool in = false;
  // Check if the cap to add is already in caplist.
  for (int i = 0; i < length; i++)
  {
    if (list[i] == cap)
    {
      in = true;
      break;
    }
  }
  // Add cap to caplist.
  if (!in)
  {
    for (int k = 0; k < length; k++)
    {
      if (list[k] == INIT_VALUE)
      {
        list[k] = cap;
        break;
      }
    }
  }
  return;
}
// Del a cap from caplist.
void del_from_list(cap_value_t *list, int length, cap_value_t cap)
{
  /*
   * If the cap is not in list, just do nothing and quit.
   * Or we will overwrite it with the next cap to keep the list continuous.
   */
#ifdef __CONTAINER_DEV__
  printf("Del %s from drop_caplist.\n", cap_to_name(cap));
#endif
  for (int i = 0; i < length; i++)
  {
    if (list[i] == cap)
    {
      while (i < length - 1)
      {
        list[i] = list[i + 1];
        i++;
      }
      list[i] = INIT_VALUE;
      break;
    }
  }
  return;
}
// Add a node to CONTAINERS struct.
struct CONTAINERS *add_node(char *container_dir, char *unshare_pid, char *drop_caplist[CAP_LAST_CAP + 1], char *env[MAX_ENVS], char *mountpoint[MAX_MOUNTPOINTS], struct CONTAINERS *container)
{
  /*
   * Use malloc() to request the memory of the node and add container info to node.
   * If current node is already used, try the next one.
   * The next node of the node added will be NULL.
   */
  if (container == NULL)
  {
    // Request memory of container struct.
    container = (struct CONTAINERS *)malloc(sizeof(struct CONTAINERS));
    container->container_dir = strdup(container_dir);
    container->unshare_pid = strdup(unshare_pid);
    for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
    {
      if (drop_caplist[i] != NULL)
      {
        container->drop_caplist[i] = strdup(drop_caplist[i]);
      }
      else
      {
        break;
      }
    }
    for (int i = 0; i < MAX_ENVS; i++)
    {
      if (env[i] != NULL)
      {
        container->env[i] = strdup(env[i]);
      }
      else
      {
        break;
      }
    }
    for (int i = 0; i < MAX_MOUNTPOINTS; i++)
    {
      if (mountpoint[i] != NULL)
      {
        container->mountpoint[i] = strdup(mountpoint[i]);
      }
      else
      {
        break;
      }
    }
    container->container = NULL;
    return container;
  }
  else
  {
    container->container = add_node(container_dir, unshare_pid, drop_caplist, env, mountpoint, container->container);
    return container;
  }
}
// Return info of a container.
struct CONTAINERS *read_node(char *container_dir, struct CONTAINERS *container)
{
  /*
   * It will return the node that matches the container_dir.
   * NULL pointer will be returned if reaching the end of all nodes.
   * However, as container_active() will be run before it to check if container's running, NULL pointer will never be returned.
   */
  if (container != NULL)
  {
    if (strcmp(container->container_dir, container_dir) == 0)
    {
      return container;
    }
    else
    {
      return read_node(container_dir, container->container);
    }
  }
  // Will never been run.
  else
  {
    return NULL;
  }
}
// Delete a node from CONTAINERS struct.
struct CONTAINERS *del_node(struct CONTAINERS *container)
{
  /*
   * It will use the next node to overwrite current node.
   * When the next node is NULL, it will stop.
   * Not using free() here, needn't because the struct is too small.
   */
  if (container == NULL)
  {
    return NULL;
  }
  else
  {
    if (container->container != NULL)
    {
      container = container->container;
      container->container = del_node(container);
    }
    else
    {
      container = NULL;
    }
  }
  return container;
}
// Delete a container from CONTAINERS struct.
struct CONTAINERS *del_container(char *container_dir, struct CONTAINERS *container)
{
  /*
   * Call to del_node() to delete the node that matches container_dir.
   * If container is a NULL pointer, just quit, but this will never happen.
   */
  // It will never be true.
  if (container == NULL)
  {
    return container;
  }
  // If container is the struct to delete.
  else if (strcmp(container->container_dir, container_dir) == 0)
  {
    container = del_node(container);
  }
  // If not, try the next struct.
  else
  {
    container->container = del_container(container_dir, container->container);
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
  // Found container matching container_dir.
  else if (strcmp(container->container_dir, container_dir) == 0)
  {
    return true;
  }
  // Try the next struct.
  else
  {
    return container_active(container_dir, container->container);
  }
}
// For daemon.
int send_msg_server(char *msg, struct sockaddr_un addr, int sockfd)
{
  /*
   * It will accept a new connection and write msg to socket.
   * Although the returned value has never been used, it will return the number written.
   */
#ifdef __CONTAINER_DEV__
  printf("%s%s\n", "Daemon send msg: ", msg);
#endif
  unsigned int size = sizeof(addr);
  // Accept a connection.
  int sock_new = accept(sockfd, (struct sockaddr *)&addr, &size);
  // Set timeout duration.
  struct timeval timeout = {3, 0};
  setsockopt(sock_new, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sock_new, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Send messages.
  return write(sock_new, msg, strlen(msg));
}
// For client.
int send_msg_client(char *msg, struct sockaddr_un addr)
{
  /*
   * It will send msg to socket and quit.
   * Although the returned value has never been used, it will return the number written.
   */
#ifdef __CONTAINER_DEV__
  printf("%s%s\n", "Client send msg: ", msg);
#endif
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("socket");
    return -1;
  }
  // Set timeout duration.
  struct timeval timeout = {0, 100};
  setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Connect to daemon.
  connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
  // Send messages.
  return send(sockfd, msg, strlen(msg), 0);
}
// For daemon, return the messages have been read.
char *read_msg_server(struct sockaddr_un addr, int sockfd)
{
  /*
   * It will return the messages have been read.
   */
  char *ret = (char *)malloc(PATH_MAX);
  unsigned int size = sizeof(addr);
  // Accept a connection.
  int sock_new = accept(sockfd, (struct sockaddr *)&addr, &size);
  // Set timeout duration.
  struct timeval timeout = {3, 0};
  setsockopt(sock_new, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sock_new, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Read messages.
  if (read(sock_new, ret, PATH_MAX) == -1)
  {
    free(ret);
    ret = NULL;
  }
  close(sock_new);
#ifdef __CONTAINER_DEV__
  if (ret != NULL)
  {
    printf("%s%s\n", "Daemon read msg: ", ret);
  }
  else
  {
    printf("%s\n", "Daemon read msg: NULL");
  }
#endif
  return ret;
}
// For client, return the messages have been read.
char *read_msg_client(struct sockaddr_un addr)
{
  /*
   * It will return the messages have been read.
   */
  char *ret = (char *)malloc(PATH_MAX);
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("socket");
  }
  // Set timeout duration.
  struct timeval timeout = {0, 100};
  setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Connect to daemon.
  connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
  // Read messages.
  if (read(sockfd, ret, PATH_MAX) == -1)
  {
    free(ret);
    ret = NULL;
  }
  close(sockfd);
#ifdef __CONTAINER_DEV__
  if (ret != NULL)
  {
    printf("%s%s\n", "Client read msg: ", ret);
  }
  else
  {
    printf("%s\n", "Client read msg: NULL");
  }
#endif
  return ret;
}
// For container_ps().
void read_all_nodes(struct CONTAINERS *container, struct sockaddr_un addr, int sockfd)
{
  /*
   * It will read all nodes in container struct and send them to ruri.
   * If it reaches the end of container struct, send `endps`.
   */
  if (container == NULL)
  {
    send_msg_server("endps", addr, sockfd);
    return;
  }
  else
  {
    send_msg_server(container->container_dir, addr, sockfd);
    send_msg_server(container->unshare_pid, addr, sockfd);
    read_all_nodes(container->container, addr, sockfd);
    return;
  }
}
// For `ruri -l`
void container_ps(void)
{
  /*
   * It will connect to rurid and list running containers.
   * If rurid is not running, just show error and exit.
   */
  // Set socket address.
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/container.sock");
  strcpy(addr.sun_path, socket_path);
  // Try to connect to container.sock and check if it's created by ruri daemon.
  // Container daemon will return `Nya!`.
  send_msg_client("Nya?", addr);
  char *msg = NULL;
  msg = read_msg_client(addr);
  if ((msg == NULL) || (strcmp("Nya!", msg) != 0))
  {
    fprintf(stderr, "\033[31mError: seems that container daemon is not running\033[0m\n");
    exit(1);
  }
  send_msg_client("ps", addr);
  printf("\033[1;38;2;254;228;208mCONTAINER_DIR\033[1;38;2;152;245;225m:\033[1;38;2;123;104;238mUNSHARE_PID\n");
  printf("\033[1;38;2;152;245;225m=========================\n");
  while (true)
  {
    msg = read_msg_client(addr);
    if (strcmp(msg, "endps") == 0)
    {
      break;
    }
    else
    {
      printf("\033[1;38;2;254;228;208m%s", msg);
      msg = read_msg_client(addr);
      printf("\033[1;38;2;152;245;225m:\033[1;38;2;123;104;238m%s\n", msg);
    }
  }
}
// For `container -K`
void kill_daemon(void)
{
  /*
   * It will just send `kill` to rurid.
   * If rurid is not running, show error and exit.
   */
  // Set socket address.
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/container.sock");
  strcpy(addr.sun_path, socket_path);
  // Try to connect to container.sock and check if it's created by ruri daemon.
  // Container daemon will return `Nya!`.
  send_msg_client("Nya?", addr);
  char *msg = NULL;
  msg = read_msg_client(addr);
  if ((msg == NULL) || (strcmp("Nya!", msg) != 0))
  {
    fprintf(stderr, "\033[31mError: seems that container daemon is not running\033[0m\n");
    exit(1);
  }
  send_msg_client("kill", addr);
  return;
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
  else
  {
    kill(atoi(container->unshare_pid), SIGKILL);
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
}
// For daemon, init an unshare container in the background.
void *init_unshare_container(void *arg)
{
  /*
   * It is called as a child process of container_daemon()
   * It will call to unshare(), send unshare_pid after fork() and other information to container_daemon()
   * and call to run_chroot_container() to exec init command.
   * Note that on the devices that has pid ns enabled, if init process died, all processes in the container will be die.
   */
  // pthread_create() only allows one argument.
  struct CONTAINER_INFO *container_info = (struct CONTAINER_INFO *)arg;
#ifdef __CONTAINER_DEV__
  printf("Daemon init container:\n");
  printf("%s%s\n", "container_dir: ", container_info->container_dir);
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
#endif
  // Try to create namespaces with unshare(), no warnings to show because daemon shuld be silent.
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
  // Fix `can't access tty` issue.
  if (unshare_pid > 0)
  {
    // Set socket address.
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
    char *tmpdir = getenv("TMPDIR");
    if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
    {
      tmpdir = "/tmp";
    }
    char socket_path[PATH_MAX] = {0};
    strcat(socket_path, tmpdir);
    strcat(socket_path, "/container.sock");
    strcpy(addr.sun_path, socket_path);
    char container_pid[1024];
    sprintf(container_pid, "%d", unshare_pid);
    send_msg_client("pid", addr);
    send_msg_client(container_pid, addr);
    send_msg_client(container_info->container_dir, addr);
    // XXX
    send_msg_client("caplist", addr);
    if (container_info->drop_caplist[0] != INIT_VALUE)
    {
      for (int i = 0; i < CAP_LAST_CAP + 1; i++)
      {
        if (container_info->drop_caplist[i] != INIT_VALUE)
        {
          send_msg_client(cap_to_name(container_info->drop_caplist[i]), addr);
          // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN
          if (!container_info->drop_caplist[i])
          {
            send_msg_client(cap_to_name(0), addr);
          }
        }
      }
    }
    send_msg_client("endcaplist", addr);
    usleep(200000);
    waitpid(unshare_pid, NULL, 0);
  }
  else if (unshare_pid == 0)
  {
    run_chroot_container(container_info, true);
  }
  return 0;
}
// Run after chroot(), called by run_chroot_container()
void init_container(void)
{
  /*
   * It'll be run after chroot(), so `/` is the root dir of container now.
   * The device list and permissions are the same as common docker container.
   */
  // umount /proc.
  umount2("/proc", MNT_DETACH | MNT_FORCE);
  // Fix issues in archlinux containers.
  mount("/", "/", NULL, MS_BIND, NULL);
  // mount proc,sys and dev.
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
  // For making dev nodes.
  // XXX
  int dev;
  // Create system runtime nodes in /dev and then fix permissions.
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
// Daemon process used to store unshare container information and init unshare container.
void container_daemon(void)
{
  // TODO(Moe-hacker): 检查msg是否为NULL
  // TODO(Moe-hacker): strdup()后free()
  // TODO(Moe-hacker): check if init binary exists.
  /*
   *
   * TODO(Moe-hacker):
   * 遵守caplist
   * XXX
   * TODO(Moe-hacker)
   * Received messages and reply contents:
   * --------------------------------------------------------------------------------------------------------------------------
   * |                                 read                               |            send             |      comment
   * --------------------------------------------------------------------------------------------------------------------------
   * |                                 Nya?                               |            Nya!             | Test messasge
   * |                          del+${container_dir}                      |            OK/Fail          | Kill a container
   * |                                 info                               |                             | wait for ${container_dir}
   * |                          ${container_dir}                          |   Pid+$container_pid//NaN   | Read container_dir, check if container is already running and send container_pid to ruri
   * |     init+${init_command}+endinit+caplist+${caplist}+endcaplist     |                             | Read information of container and init container
   * |pid+${container_pid}+${contaiiner_dir}+caplist+${caplist}+endcaplist|                             | Read container info from child process
   *
   *
   */
  // Set process name.
  prctl(PR_SET_NAME, "rurid", NULL, NULL, NULL);
  // Ignore SIGTTIN, if running in the background, SIGTTIN may kill it.
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTTIN);
  sigprocmask(SIG_BLOCK, &sigs, 0);
  // For pthread_create()
  pthread_t pthread_id;
  // Check if we are running with root privileges.
  if (getuid() != 0)
  {
    fprintf(stderr, "\033[31mError: this program should be run with root privileges !\033[0m\n");
    exit(1);
  }
  // Check if $LD_PRELOAD is unset.
  char *ld_preload = getenv("LD_PRELOAD");
  if ((ld_preload != NULL) && (strcmp(ld_preload, "") != 0))
  {
    fprintf(stderr, "\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run.\033[0m\n");
    exit(1);
  }
  // Create container struct.
  struct CONTAINERS *container = NULL;
  // Set default value.
  // Message to read.
  char *msg = NULL;
  // Container info.
  char *container_dir = NULL;
  // TODO(Moe-hacker): container_info设置为指针，回收container_info内存并重新创建
  struct CONTAINER_INFO container_info;
  container_info.container_dir = NULL;
  container_info.init_command[0] = NULL;
  container_info.unshare_pid = NULL;
  // TODO(Moe-hacker)
  container_info.mountpoint[0] = NULL;
  container_info.env[0] = NULL;
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    container_info.drop_caplist[i] = INIT_VALUE;
  }
  pid_t unshare_pid;
  char *drop_caplist[CAP_LAST_CAP + 1] = {NULL};
  char *env[MAX_ENVS] = {NULL};
  char *mountpoint[MAX_MOUNTPOINTS] = {NULL};
  // Create socket
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    fprintf(stderr, "\033[31mError: cannot create socket.\n");
    return;
  }
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/container.sock");
  strcpy(addr.sun_path, socket_path);
  // Check if container daemon is already running.
  // Container daemon will return `Nya!`.
  send_msg_client("Nya?", addr);
  msg = read_msg_client(addr);
  if ((msg != NULL) && (strcmp("Nya!", msg) == 0))
  {
    close(sockfd);
    printf("\033[31mDaemon already running.\n");
    exit(1);
  }
  else
  {
    // Fork itself into the background.
    pid_t pid = fork();
    if (pid > 0)
    {
      exit(0);
    }
    else if (pid < 0)
    {
      perror("fork");
      exit(1);
    }
    // Create container.sock
    remove(socket_path);
    unlink(socket_path);
    if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
      perror("bind");
      exit(1);
    }
  }
  listen(sockfd, 16);
  // Read message from ruri.
  while (true)
  {
    // Get message.
    msg = NULL;
    msg = read_msg_server(addr, sockfd);
    if (msg == NULL)
    {
      continue;
    }
    // Test message.
    if (strcmp("Nya?", msg) == 0)
    {
      send_msg_server("Nya!", addr, sockfd);
    }
    // Kill a container.
    else if (strcmp("del", msg) == 0)
    {
      container_dir = read_msg_server(addr, sockfd);
      if (container_active(container_dir, container))
      {
        unshare_pid = atoi(read_node(container_dir, container)->unshare_pid);
        kill(unshare_pid, SIGKILL);
        container = del_container(container_dir, container);
        send_msg_server("OK", addr, sockfd);
      }
      else
      {
        send_msg_server("Fail", addr, sockfd);
      }
    }
    else if (strcmp("info", msg) == 0)
    {
      // Get container_dir.
      container_dir = read_msg_server(addr, sockfd);
      if (container_active(container_dir, container))
      {
        send_msg_server("Pid", addr, sockfd);
        send_msg_server(read_node(container_dir, container)->unshare_pid, addr, sockfd);
      }
      else
      {
        send_msg_server("NaN", addr, sockfd);
        container_info.container_dir = NULL;
        container_info.init_command[0] = NULL;
        container_info.unshare_pid = NULL;
        for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
        {
          container_info.drop_caplist[i] = INIT_VALUE;
        }
        // Read init command.
        msg = read_msg_server(addr, sockfd);
        if (strcmp(msg, "init") != 0)
        {
          continue;
        }
        for (int i = 0;;)
        {
          msg = read_msg_server(addr, sockfd);
          if (strcmp("endinit", msg) == 0)
          {
            break;
          }
          container_info.init_command[i] = strdup(msg);
          container_info.init_command[i + 1] = NULL;
          i++;
        }
        if (container_info.init_command[0] == NULL)
        {
          container_info.init_command[0] = "/bin/sh";
          container_info.init_command[1] = "-c";
          container_info.init_command[2] = "while :;do sleep 100s;done";
          container_info.init_command[3] = NULL;
        }
        msg = read_msg_server(addr, sockfd);
        if (strcmp(msg, "caplist") != 0)
        {
          continue;
        }
        for (int i = 0;;)
        {
          msg = read_msg_server(addr, sockfd);
          if (strcmp("endcaplist", msg) == 0)
          {
            break;
          }
          cap_from_name(msg, &container_info.drop_caplist[i]);
          i++;
        }
        container_info.container_dir = strdup(container_dir);
        pthread_create(&pthread_id, NULL, init_unshare_container, (void *)&container_info);
      }
    }
    else if (strcmp("pid", msg) == 0)
    {
      msg = read_msg_server(addr, sockfd);
      container_info.unshare_pid = strdup(msg);
      msg = read_msg_server(addr, sockfd);
      container_info.container_dir = strdup(msg);
      msg = read_msg_server(addr, sockfd);
      if (strcmp(msg, "caplist") != 0)
      {
        continue;
      }
      for (int i = 0;;)
      {
        msg = read_msg_server(addr, sockfd);
        if (strcmp("endcaplist", msg) == 0)
        {
          break;
        }
        drop_caplist[i] = strdup(msg);
        drop_caplist[i + 1] = NULL;
        i++;
      }
      // TODO(Moe-hacker)
      container = add_node(container_info.container_dir, container_info.unshare_pid, drop_caplist, env, mountpoint, container);
      // Send ${unshare_pid} to ruri.
      send_msg_server(container_info.unshare_pid, addr, sockfd);
      container_info.container_dir = NULL;
      container_info.init_command[0] = NULL;
      container_info.unshare_pid = NULL;
      for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
      {
        container_info.drop_caplist[i] = INIT_VALUE;
      }
    }
    else if (strcmp("kill", msg) == 0)
    {
      umount_all_containers(container);
      exit(0);
    }
    else if (strcmp("ps", msg) == 0)
    {
      read_all_nodes(container, addr, sockfd);
    }
  }
}
// Do some checks before chroot()
bool check_container(char *container_dir)
{
  // TODO(Moe-hacker): check if init binary exists.
  /*
   * It's called to by main() to check if we can run a container in container_dir.
   */
  // Check if container directory is given.
  if (container_dir == NULL)
  {
    fprintf(stderr, "\033[31mError: container directory is not set !\033[0m\n");
    return false;
  }
  // Refuse to use `/` for container directory.
  if (strcmp(container_dir, "/") == 0)
  {
    fprintf(stderr, "\033[31mError: `/` is not allowed to use as a container directory.\033[0m\n");
    return false;
  }
  // Check if we are running with root privileges.
  if (getuid() != 0)
  {
    fprintf(stderr, "\033[31mError: this program should be run with root privileges !\033[0m\n");
    return false;
  }
  // Check if $LD_PRELOAD is unset.
  char *ld_preload = getenv("LD_PRELOAD");
  if ((ld_preload != NULL) && (strcmp(ld_preload, "") != 0))
  {
    fprintf(stderr, "\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run.\033[0m\n");
    return false;
  }
  // Check if container directory exists.
  DIR *direxist = NULL;
  if ((direxist = opendir(container_dir)) == NULL)
  {
    fprintf(stderr, "\033[31mError: container directory does not exist !\033[0m\n");
    return false;
  }
  else
  {
    closedir(direxist);
  }
  return true;
}
// Run unshare container.
void run_unshare_container(struct CONTAINER_INFO *container_info, const bool no_warnings)
{
  /*
   * If rurid is not running, it will create namespaces itself.
   * Or it will connect to rurid and use setns() to join namespaces created by rurid.
   * After fork() to send itself to new namespaces, it will call to run_chroot_container().
   */
  // Set default init.
  if (container_info->init_command[0] == NULL)
  {
    container_info->init_command[0] = "/bin/su";
    container_info->init_command[1] = "-";
    container_info->init_command[2] = NULL;
  }
#ifdef __CONTAINER_DEV__
  printf("Run unshare container:\n");
  printf("%s%s\n", "container_dir: ", container_info->container_dir);
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
#endif
  pid_t unshare_pid = INIT_VALUE;
  // Set socket address.
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/container.sock");
  strcpy(addr.sun_path, socket_path);
  bool daemon_running = false;
  // Try to connect to container.sock and check if it's created by ruri daemon.
  // Container daemon will return `Nya!`.
  send_msg_client("Nya?", addr);
  char *msg = NULL;
  msg = read_msg_client(addr);
  if ((msg != NULL) && (strcmp("Nya!", msg) == 0))
  {
    daemon_running = true;
  }
  else
  {
    if (!no_warnings)
    {
      printf("\033[33mWarning: seems that container daemon is not running\033[0m\n");
    }
  }
  // Unshare itself into new namespaces.
  if (!daemon_running)
  {
    // Create namespace here because container_daemon is not running.
    if (unshare(CLONE_NEWNS) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that mount namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_NEWUTS) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that uts namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_NEWIPC) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that ipc namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_NEWPID) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that pid namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_NEWCGROUP) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that cgroup namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_NEWTIME) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that time namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_SYSVSEM) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that semaphore namespace is not supported on this device\033[0m\n");
    }
    if (unshare(CLONE_FILES) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that we could not unshare file descriptors with child process\033[0m\n");
    }
    if (unshare(CLONE_FS) == -1 && !no_warnings)
    {
      printf("\033[33mWarning: seems that we could not unshare filesystem information with child process\033[0m\n");
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
      fprintf(stderr, "\033[31mFork error\n");
    }
  }
  else
  {
    send_msg_client("info", addr);
    send_msg_client(container_info->container_dir, addr);
    msg = read_msg_client(addr);
    if (strcmp(msg, "NaN") == 0)
    {
      send_msg_client("init", addr);
      if (strcmp(container_info->init_command[0], "/bin/su") != 0)
      {
        for (int i = 0; i < 1023; i++)
        {
          if (container_info->init_command[i] != NULL)
          {
            send_msg_client(container_info->init_command[i], addr);
          }
          else
          {
            break;
          }
        }
      }
      send_msg_client("endinit", addr);
      container_info->init_command[0] = "/bin/su";
      container_info->init_command[1] = "-";
      container_info->init_command[2] = NULL;
      send_msg_client("caplist", addr);
      if (container_info->drop_caplist[0] != INIT_VALUE)
      {
        for (int i = 0; i < CAP_LAST_CAP + 1; i++)
        {
          // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN
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
      send_msg_client("endcaplist", addr);
    }
    // For setns()
    usleep(200000);
    // XXX
    // For setns(), we define it as char*.
    char *container_pid = NULL;
    container_pid = read_msg_client(addr);
#ifdef __CONTAINER_DEV__
    printf("%s%s\n", "Container pid from daemon:", container_pid);
#endif
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
    int fd = INIT_VALUE;
    fd = open(mount_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that mount namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0);
    }
    fd = open(pid_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that pid namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0);
    }
    fd = open(time_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that time namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0);
    }
    fd = open(uts_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that uts namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0);
    }
    fd = open(cgroup_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that cgroup namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0);
    }
    fd = open(ipc_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that ipc namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0);
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
      fprintf(stderr, "\033[31mFork error\n");
    }
  }
  // Check if unshare is enabled.
  if (unshare_pid == 0)
  {
    run_chroot_container(container_info, no_warnings);
  }
  return;
}
// Run chroot container.
void run_chroot_container(struct CONTAINER_INFO *container_info, const bool no_warnings)
{
  /*
   * It's called to by main(), run_unshare_container() and init_unshare_container()(container_daemon()).
   * It will chroot() to container_dir, call to init_container(), drop capabilities and exec() init command in container.
   */
  // Ignore SIGTTIN, if running in the background, SIGTTIN may kill it.
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTTIN);
  sigprocmask(SIG_BLOCK, &sigs, 0);
#ifdef __CONTAINER_DEV__
  printf("Run chroot container:\n");
  printf("%s%s\n", "container_dir: ", container_info->container_dir);
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
#endif
  // Set default init.
  if (container_info->init_command[0] == NULL)
  {
    container_info->init_command[0] = "/bin/su";
    container_info->init_command[1] = "-";
    container_info->init_command[2] = NULL;
  }
  // chroot into container.
  chroot(container_info->container_dir);
  chdir("/");
  // Check if system runtime files are already created.
  DIR *direxist = NULL;
  if ((direxist = opendir("/sys/kernel")) == NULL)
  {
    init_container();
  }
  else
  {
    closedir(direxist);
  }
  // Drop caps.
  if (container_info->drop_caplist[0] != INIT_VALUE)
  {
    for (int i = 0; i < CAP_LAST_CAP + 1; i++)
    {
      // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN
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
  // XXX
  // BUG: not work if init is /bin/su -
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
  // Use exec() family function because system() may be unavailable now.
  usleep(200000);
  if (execv(container_info->init_command[0], container_info->init_command) == -1)
  {
    // Catch exceptions.
    fprintf(stderr, "\033[31mFailed to execute init `%s`\n", container_info->init_command[0]);
    fprintf(stderr, "execv() returned: %d\n", errno);
    fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
    exit(1);
  }
}
// Kill&umount container.
void umount_container(char *container_dir)
{
  /*
   * It will try to connect to rurid, and rurid will kill init_unshare_container() process of container if the container is running.
   * Then it will umount() container_dir and other directories in it.
   */
  // TODO(Moe-hacker): umount() mountpoint
  //  Set socket address.
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/container.sock");
  strcpy(addr.sun_path, socket_path);
  // Try to connect to container.sock and check if it's created by ruri daemon.
  // Container daemon will return `Nya!`.
  send_msg_client("Nya?", addr);
  char *msg = NULL;
  msg = read_msg_client(addr);
  if ((msg == NULL) || (strcmp("Nya!", msg) != 0))
  {
    printf("\033[33mWarning: seems that container daemon is not running\033[0m\n");
  }
  else
  {
    send_msg_client("del", addr);
    send_msg_client(container_dir, addr);
    msg = read_msg_client(addr);
    if (strcmp(msg, "Fail") == 0)
    {
      fprintf(stderr, "\033[33mWarning: seems that container is not running\033[0m\n");
    }
  }
  // Get path to umount.
  char sys_dir[PATH_MAX];
  char proc_dir[PATH_MAX];
  char dev_dir[PATH_MAX];
  strcpy(sys_dir, container_dir);
  strcpy(proc_dir, container_dir);
  strcpy(dev_dir, container_dir);
  strcat(sys_dir, "/sys");
  strcat(proc_dir, "/proc");
  strcat(dev_dir, "/dev");
  // Force umount all directories for 10 times.
  printf("\033[1;38;2;254;228;208mUmount container.\n");
  for (int i = 1; i < 10; i++)
  {
    umount2(sys_dir, MNT_DETACH | MNT_FORCE);
    usleep(2000);
    umount2(dev_dir, MNT_DETACH | MNT_FORCE);
    usleep(2000);
    umount2(proc_dir, MNT_DETACH | MNT_FORCE);
    usleep(2000);
    umount2(container_dir, MNT_DETACH | MNT_FORCE);
    usleep(2000);
  }
  return;
}
int main(int argc, char **argv)
{
  /*
   * It will get command-line args, build the info of container and create a container or call to other functions.
   */
  // Set process name.
  prctl(PR_SET_NAME, "ruri", NULL, NULL, NULL);
  // Check if arguments are given.
  if (argc <= 1)
  {
    fprintf(stderr, "\033[31mError: too few arguments !\033[0m\n");
    show_helps(0);
    return 1;
  }
  // Set default value.
  bool use_unshare = false;
  bool no_warnings = false;
  char *container_dir = false;
  bool greetings = NULL;
  bool privileged = false;
  char *init[MAX_INIT_COMMANDS] = {NULL};
  char *env[MAX_ENVS] = {NULL};
  char *mountpoint[MAX_MOUNTPOINTS] = {NULL};
  struct CONTAINER_INFO *container_info = NULL;
  // These caps are kept by default:
  // CAP_SETGID,CAP_CHOWN,CAP_NET_RAW,CAP_DAC_OVERRIDE,CAP_FOWNER,CAP_FSETID,CAP_SETUID
  cap_value_t drop_caplist[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    drop_caplist[i] = INIT_VALUE;
  }
  cap_value_t drop_caplist_common[] = {CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND};
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
  for (int arg_num = 1; arg_num < argc; arg_num++)
  {
    //============== [Other options] ==============
    if (strcmp(argv[arg_num], "-v") == 0)
    {
      show_version_info();
      return 0;
    }
    if (strcmp(argv[arg_num], "-D") == 0)
    {
      container_daemon();
      return 0;
    }
    if (strcmp(argv[arg_num], "-K") == 0)
    {
      kill_daemon();
      return 0;
    }
    if (strcmp(argv[arg_num], "-h") == 0)
    {
      greetings = true;
      show_helps(greetings);
      return 0;
    }
    if (strcmp(argv[arg_num], "-l") == 0)
    {
      container_ps();
      return 0;
    }
    //=========End of [Other options]===========
    if (strcmp(argv[arg_num], "-u") == 0)
    {
      use_unshare = true;
    }
    else if (strcmp(argv[arg_num], "-U") == 0)
    {
      arg_num += 1;
      if (argv[arg_num] != NULL)
      {
        if (check_container(argv[arg_num]))
        {
          container_dir = realpath(argv[arg_num], NULL);
          umount_container(container_dir);
          return 0;
        }
      }
      else
      {
        fprintf(stderr, "\033[31mError: container directory is not set !\033[0m\n");
        return 1;
      }
    }
    else if (strcmp(argv[arg_num], "-d") == 0)
    {
      for (unsigned long i = 0; i < (sizeof(drop_caplist_unprivileged) / sizeof(drop_caplist_unprivileged[0])); i++)
      {
        drop_caplist[i] = drop_caplist_unprivileged[i];
      }
    }
    else if (strcmp(argv[arg_num], "-p") == 0)
    {
      privileged = true;
    }
    else if (strcmp(argv[arg_num], "-w") == 0)
    {
      no_warnings = true;
    }
    // XXX
    else if (strcmp(argv[arg_num], "-e") == 0)
    {
      arg_num++;
      if ((argv[arg_num] != NULL) && (argv[arg_num + 1] != NULL))
      {
        for (int i = 0; i < MAX_ENVS; i++)
        {
          if (env[i] == NULL)
          {
            env[i] = strdup(argv[arg_num]);
            arg_num++;
            env[i + 1] = strdup(argv[arg_num]);
            env[i + 2] = NULL;
            break;
          }
        }
      }
      else
      {
        fprintf(stderr, "%s\033[0m\n", "\033[31mError: unknow env");
        return 1;
      }
    }
    // XXX
    else if (strcmp(argv[arg_num], "-m") == 0)
    {
      arg_num++;
      if ((argv[arg_num] != NULL) && (argv[arg_num + 1] != NULL))
      {
        for (int i = 0; i < MAX_MOUNTPOINTS; i++)
        {
          if (mountpoint[i] == NULL)
          {
            mountpoint[i] = strdup(argv[arg_num]);
            arg_num++;
            mountpoint[i + 1] = strdup(argv[arg_num]);
            mountpoint[i + 2] = NULL;
            break;
          }
        }
      }
      else
      {
        fprintf(stderr, "%s\033[0m\n", "\033[31mError: unknow mountpoint");
        return 1;
      }
    }
    else if (strcmp(argv[arg_num], "--keep") == 0)
    {
      arg_num++;
      if (argv[arg_num] != NULL)
      {
        if (cap_from_name(argv[arg_num], &cap) == 0)
        {
          add_to_list(keep_caplist_extra, CAP_LAST_CAP + 1, cap);
        }
        else
        {
          fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", argv[arg_num], "`");
          return 1;
        }
      }
      else
      {
        fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", "(null)", "`");
        return 1;
      }
    }
    else if (strcmp(argv[arg_num], "--drop") == 0)
    {
      arg_num++;
      if (argv[arg_num] != NULL)
      {
        if (cap_from_name(argv[arg_num], &cap) == 0)
        {
          add_to_list(drop_caplist_extra, CAP_LAST_CAP + 1, cap);
        }
        else
        {
          fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", argv[arg_num], "`");
          return 1;
        }
      }
      else
      {
        fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", "(null)", "`");
        return 1;
      }
    }
    else if ((strchr(argv[arg_num], '/') && strcmp(strchr(argv[arg_num], '/'), argv[arg_num]) == 0) || (strchr(argv[arg_num], '.') && strcmp(strchr(argv[arg_num], '.'), argv[arg_num]) == 0))
    {

      // Get the absolute path of container.
      if (check_container(argv[arg_num]))
      {
        container_dir = realpath(argv[arg_num], NULL);
      }
      arg_num++;
      // Arguments after container_dir will be read as init command.
      // XXX
      int init_arg_num = 0;
      if (argv[arg_num])
      {
        while (arg_num <= argc)
        {
          init[init_arg_num] = argv[arg_num];
          init[init_arg_num + 1] = NULL;
          arg_num++;
          init_arg_num++;
        }
      }
      else
      {
        init[0] = NULL;
      }
    }
    else
    {
      fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow option `", argv[arg_num], "`");
      show_helps(greetings);
      return 1;
    }
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
  container_info = (struct CONTAINER_INFO *)malloc(sizeof(struct CONTAINER_INFO));
  container_info->container_dir = container_dir;
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
  // TODO(Moe-hacker)
  // 同时需完善dev log
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
  // TODO(Moe-hacker)
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
  // Pure-chroot and unshare container are two functions now.
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
