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
/*
 * If the code is hard to write,
 * it should be hard to read.
 */
// The macro __RURI_DEV__ will enable extra logs.
// Do not uncomment it, use `-D__RURI_DEV__` to compile instead.
// #define __RURI_DEV__
// Show error msg and exit.
void error(char *msg)
{
  /*
   * Show error message and exit here.
   * You can never know if a customer will order a rice at the bar.
   * It's a `moe` program, but also should be standardized and rigorous.
   */
  fprintf(stderr, "\033[31m%s\033[0m\n", msg);
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "  .^.   .^.");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "  /⋀\\_ﾉ_/⋀\\");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", " /ﾉｿﾉ\\ﾉｿ丶)|");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "|ﾙﾘﾘ >  x )ﾘ");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "ﾉノ㇏  ^ ﾉ|ﾉ");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "      ⠁⠁");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "If you think something is wrong, please report at:");
  fprintf(stderr, "\033[4;1;38;2;254;228;208m%s\033[0m\n", "https://github.com/Moe-hacker/ruri/issues");
  exit(1);
}
// Greeting information.
// As an easter agg.
void show_greetings()
{
  /*
   * Nothing's useful at this function, just for fun.
   */
  // Get the size of terminal.
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  unsigned short col = size.ws_col;
  if (col % 2 == 1)
  {
    col -= 1;
  }
  // For centering output.
  char space[col / 2 + 1];
  space[0] = '\000';
  if (col > 46)
  {
    col /= 2;
    col -= 22;
    for (unsigned short i = 1; i <= col; i++)
    {
      strcat(space, " ");
    }
  }
  else
  {
    strcat(space, "");
  }
  printf("%s%s\n", space, "\033[1;38;2;66;66;66m               ▅▅▀▀▀▀▀▀▀▀▀▀▀▀▅");
  printf("%s%s\n", space, "          ▅▅▀▀▀               ▀▀▅▅");
  printf("%s%s\n", space, "     ▅▅▅▀▀            ▅           ▀▅");
  printf("%s%s\n", space, "      ▅▀      ▅▀█▅▅▀▀▅▀▅        ▅▅  ▀▅");
  printf("%s%s\n", space, "     ▅▀   █▅▀▀  ▀     ▀ ▀▀▅▅    █ ▀▀▅ █");
  printf("%s%s\n", space, "    ▅▀   ▅▀  ▅▀      ▀▅    ▀▅   █▅███▀█");
  printf("%s%s\n", space, "  ▅▅█▀▅ █ ▅▅▀          ▀▀   █   ████   █");
  printf("%s%s\n", space, "      █ █ ▅▅▅▅▅        ▅▅▅▅▅ █  ▀█▀    █");
  printf("%s%s\n", space, "      █ █▀ ▅▅▅ ▀      ▀ ▅▅▅ ▀█   █     █");
  printf("%s%s\n", space, "      █ █ █\033[40;31m█▀█\033[0m\033[1;38;2;66;66;66m█        █\033[40;31m█▀█\033[0m\033[1;38;2;66;66;66m█ █   █     █");
  printf("%s%s\n", space, "     █  █ █\033[31m███\033[1;38;2;66;66;66m█        █\033[31m███\033[1;38;2;66;66;66m█ █   █     ▀▅");
  printf("%s%s\n", space, "    ▅▀  █  ▀▀▀          ▀▀▀  █   █      █");
  printf("%s%s\n", space, "  ▅▀▅▀ █                     █   █      █");
  printf("%s%s\n", space, " █   █ ▀▅ ▅▀▅   ▅▀▅   ▅▅     █   █      ▀▅");
  printf("%s%s\n", space, "▅█▅▅██▅ ▅██  ▀███ ▅████ ▀▅█▀▅▀   █       ▀▅");
  printf("%s%s\n", space, "███████ ▀██████████████████▀▀             █");
  printf("%s%s\n", space, " █    ▀▅  ██▀ ▀██▀▀██▀▀██▀█     █▀         █");
  printf("%s%s\n", space, " ▀▅     ▀▀█              ▅▀     █          █");
  printf("%s%s\n", space, "   ▀▅    █               █     ██        ▅▀");
  printf("%s%s\n", space, "     ▀▅▅▅▀                ▀▀▀▀▀ █        █");
  printf("%s%s\n", space, "        ▀                       ▀        ▀");
  printf("%s\n", "");
}
// For `ruri -v`.
void show_version_info()
{
  /*
   * Just show version info and license.
   * Version info is defined in macro RURI_VERSION.
   */
  printf("\n");
  printf("\033[1;38;2;254;228;208m%s%s%s", "ruri ", RURI_VERSION, "\n");
  printf("\n");
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
}
// For `ruri -h`.
void show_helps(bool greetings)
{
  /*
   * Help page of ruri.
   * I think you can understand...
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
  printf("  -hh                   :Show helps and commandline examples\n");
  printf("  -D                    :Run rurid\n");
  printf("  -K                    :Kill rurid\n");
  printf("  -t                    :Check if rurid is running\n");
  printf("  -l                    :List all running unshare containers\n");
  printf("  -U [container_dir]    :Umount&kill a container\n");
  printf("Args for running a container:\n");
  printf("  -u                    :Enable unshare feature\n");
  printf("  -d                    :Drop more capabilities for better security\n");
  printf("  -p                    :Run privileged container\n");
  printf(" --keep [cap]           :Keep the specified cap\n");
  printf(" --drop [cap]           :Drop the specified cap\n");
  printf("  -e [env] [value]      :Set env to its value *Not work if init command is like `su -`\n");
  printf("  -m [dir] [mountpoint] :Mount dir to mountpoint\n");
  printf("  -w                    :Disable warnings\n");
  printf("Default init command is `/bin/su` if it's not set\n");
  printf("This program should be run with root privileges\n");
  printf("Please unset $LD_PRELOAD before running this program\033[0m\n");
}
// For `ruri -hh`.
void show_examples()
{
  /*
   * Command line examples.
   * I hope you can understand...
   */
  printf("\n");
  printf("\033[1;38;2;254;228;208m#Quickly setup a container(with rootfstool):\n");
  printf("  \033[32mgit \033[33mclone \033[35mhttps://github.com/Moe-hacker/rootfstool\n");
  printf("  \033[32mcd \033[35mrootfstool\n");
  printf("  \033[32m./rootfstool \033[33mdownload \033[34m-d \033[35malpine \033[34m-v \033[35medge\n");
  printf("  \033[32mmkdir \033[35m/tmp/alpine\n");
  printf("  \033[32msudo tar \033[34m-xvf \033[35mrootfs.tar.xz \033[34m-C \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#Run chroot container:\n");
  printf("  \033[32msudo ruri \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#Very simple as you can see.\n");
  printf("#About the capabilities:\n");
  printf("#Run privileged chroot container:\n");
  printf("  \033[32msudo ruri \033[34m-p \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#But if you want to make the container more secure:\n");
  printf("  \033[32msudo ruri \033[34m-d \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#If you want to run privileged chroot container,\n");
  printf("#but you don't want to give the container cap_sys_chroot privileges:\n");
  printf("  \033[32msudo ruri \033[34m-p --drop \033[36mcap_sys_chroot \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#If you want to run chroot container with common privileges,\n");
  printf("#but you want cap_sys_admin to be kept:\n");
  printf("  \033[32msudo ruri \033[34m--keep \033[36mcap_sys_admin \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#About unshare:\n");
  printf("#Unshare container's capability options are same with chroot.\n");
  printf("#But it's recommended to start rurid before running unshare containers:\n");
  printf("  \033[32msudo ruri \033[34m-D\n");
  printf("\033[1;38;2;254;228;208m#Run unshare container:\n");
  printf("  \033[32msudo ruri \033[34m-u \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#List running containers:\n");
  printf("  \033[32msudo ruri \033[34m-l\n");
  printf("\033[1;38;2;254;228;208m#Umount the container:\n");
  printf("  \033[32msudo ruri \033[34m-U \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#Finally, kill the daemon:\n");
  printf("  \033[32msudo ruri \033[34m-K\n");
}
// Return the same value as mkdir()
int mkdirs(char *dir, mode_t mode)
{
  /*
   * A very simple implementation of mkdir -p
   * I don't know why it seems that there isn't an existing function to do this...
   */
  char buf[PATH_MAX];
  for (unsigned long i = 1; i < strlen(dir); i++)
  {
    if (dir[i] == '/')
    {
      buf[0] = '/';
      for (unsigned long j = 1; j < i; j++)
      {
        buf[j] = dir[j];
        buf[j + 1] = '\0';
      }
      mkdir(buf, mode);
    }
  }
  return mkdir(dir, mode);
}
// Add a cap to caplist.
void add_to_list(cap_value_t *list, int length, cap_value_t cap)
{
  /*
   * If the cap is already in list, just do nothing and quit.
   * Caps are initialized by INIT_VALUE, and the INIT_VALUE will be ignored when dropping caps.
   */
#ifdef __RURI_DEV__
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
}
// Del a cap from caplist.
void del_from_list(cap_value_t *list, int length, cap_value_t cap)
{
  /*
   * If the cap is not in list, just do nothing and quit.
   * Or we will overwrite it and caps after it with theirs next cap to keep the list continuous.
   */
#ifdef __RURI_DEV__
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
}
// Add a node to CONTAINERS struct.
struct CONTAINERS *add_node(char *container_dir, char *unshare_pid, char drop_caplist[CAP_LAST_CAP + 1][128], char *env[MAX_ENVS], char mountpoint[MAX_MOUNTPOINTS][PATH_MAX], struct CONTAINERS *container)
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
    for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
    {
      if (drop_caplist[i][0] != '\0')
      {
        container->drop_caplist[i] = strdup(drop_caplist[i]);
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
        container->env[i] = strdup(env[i]);
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
        container->mountpoint[i] = strdup(mountpoint[i]);
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
  container->container = add_node(container_dir, unshare_pid, drop_caplist, env, mountpoint, container->container);
  return container;
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
    // If container matches container_dir.
    if (strcmp(container->container_dir, container_dir) == 0)
    {
      return container;
    }
    // If not, try the next node.
    return read_node(container_dir, container->container);
  }
  // Will never be run.
  return NULL;
}
// Delete a container from CONTAINERS struct.
struct CONTAINERS *del_container(char *container_dir, struct CONTAINERS *container)
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
  // If container matches container_dir.
  if (strcmp(container->container_dir, container_dir) == 0)
  {
    return true;
  }
  // If not, try the next struct.
  return container_active(container_dir, container->container);
}
// For daemon.
ssize_t send_msg_daemon(char *msg, struct sockaddr_un addr, int sockfd)
{
  /*
   * It will accept a new connection and write msg to socket.
   * Although the returned value has never been used, it will return the number written.
   */
#ifdef __RURI_DEV__
  printf("%s%s\n", "Daemon send msg: ", msg);
#endif
  unsigned int size = sizeof(addr);
  // Accept a connection.
  int sock_new = accept4(sockfd, (struct sockaddr *)&addr, &size, SOCK_CLOEXEC);
  // Set timeout duration.
  struct timeval timeout = {3, 0};
  setsockopt(sock_new, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sock_new, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Send messages.
  return write(sock_new, msg, strlen(msg));
}
// For client.
ssize_t send_msg_client(char *msg, struct sockaddr_un addr)
{
  /*
   * It will send msg to socket and quit.
   * Although the returned value has never been used, it will return the number written.
   */
#ifdef __RURI_DEV__
  printf("%s%s\n", "Client send msg: ", msg);
#endif
  int sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
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
  if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    return -1;
  }
  // Send messages.
  return send(sockfd, msg, strlen(msg), 0);
}
// For daemon, return the messages have been read.
char *read_msg_daemon(struct sockaddr_un addr, int sockfd)
{
  /*
   * It will return the messages have been read.
   * free() the memory of msg after used it to avoid leak of memory.
   */
  char buf[PATH_MAX] = {0};
  static const char *ret = NULL;
  unsigned int size = sizeof(addr);
  // Accept a connection.
  int sock_new = accept4(sockfd, (struct sockaddr *)&addr, &size, SOCK_CLOEXEC);
  // Set timeout duration.
  struct timeval timeout = {3, 0};
  setsockopt(sock_new, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sock_new, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Read messages.
  if (read(sock_new, buf, PATH_MAX) == -1)
  {
    ret = NULL;
  }
  else
  {
    ret = strdup(buf);
  }
  close(sock_new);
#ifdef __RURI_DEV__
  if (ret != NULL)
  {
    printf("%s%s\n", "Daemon read msg: ", ret);
  }
  else
  {
    printf("%s\n", "Daemon read msg: NULL");
  }
#endif
  return (char *)ret;
}
// For client, return the messages have been read.
char *read_msg_client(struct sockaddr_un addr)
{
  /*
   * It will return the messages have been read.
   * free() the memory of msg after used it to avoid leak of memory.
   */
  char buf[PATH_MAX] = {0};
  static const char *ret = NULL;
  int sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
  if (sockfd < 0)
  {
    perror("socket");
  }
  // Set timeout duration.
  struct timeval timeout = {1, 100};
  setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Connect to daemon.
  if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
  {
    return NULL;
  }
  // Read messages.
  if (read(sockfd, buf, PATH_MAX) == -1)
  {
    ret = NULL;
  }
  else
  {
    ret = strdup(buf);
  }
  close(sockfd);
#ifdef __RURI_DEV__
  if (ret != NULL)
  {
    printf("%s%s\n", "Client read msg: ", ret);
  }
  else
  {
    printf("%s\n", "Client read msg: NULL");
  }
#endif
  return (char *)ret;
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
// For `ruri -l`
void container_ps()
{
  /*
   * It will connect to rurid and list running containers.
   * If rurid is not running, just show error and exit.
   */
  // Set socket address.
  struct sockaddr_un addr;
  if (!connect_to_daemon(&addr))
  {
    error("Daemon not running.");
  }
  // Message to read.
  char *msg = NULL;
  // rurid will return the info of running containers.
  send_msg_client(FROM_CLIENT__GET_PS_INFO, addr);
  printf("\033[1;38;2;254;228;208mCONTAINER_DIR\033[1;38;2;152;245;225m:\033[1;38;2;123;104;238mUNSHARE_PID\n");
  printf("\033[1;38;2;152;245;225m=========================\n");
  while (true)
  {
    msg = read_msg_client(addr);
    // End of container info.
    if (strcmp(msg, FROM_DAEMON__END_OF_PS_INFO) == 0)
    {
      free(msg);
      msg = NULL;
      break;
    }
    // Print the received container info.
    printf("\033[1;38;2;254;228;208m%s", msg);
    free(msg);
    msg = NULL;
    msg = read_msg_client(addr);
    printf("\033[1;38;2;152;245;225m:\033[1;38;2;123;104;238m%s\n", msg);
    free(msg);
    msg = NULL;
  }
}
// Connect to daemon.
bool connect_to_daemon(struct sockaddr_un *addr)
{
  /*
   * Set socket address and check if rurid is running.
   */
  // Set socket address.
  addr->sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if ((tmpdir == NULL) || (strcmp(tmpdir, "") == 0))
  {
    tmpdir = "/tmp";
  }
  char socket_path[PATH_MAX] = {0};
  strcat(socket_path, tmpdir);
  strcat(socket_path, "/");
  strcat(socket_path, SOCKET_FILE);
  strcpy(addr->sun_path, socket_path);
  // Try to connect to socket file and check if it's created by ruri daemon.
  send_msg_client(FROM_CLIENT__TEST_MESSAGE, *addr);
  char *msg = NULL;
  msg = read_msg_client(*addr);
  if ((msg == NULL) || (strcmp(FROM_DAEMON__TEST_MESSAGE, msg) != 0))
  {
    return false;
  }
  free(msg);
  return true;
}
// For `ruri -K`
void kill_daemon()
{
  /*
   * It will just send `kill` to rurid.
   * If rurid is not running, show error and exit.
   */
  // Set socket address.
  struct sockaddr_un addr;
  if (!connect_to_daemon(&addr))
  {
    error("Daemon not running");
  }
  // Rurid will kill itself after received this message.
  send_msg_client(FROM_CLIENT__KILL_DAEMON, addr);
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
   * It is called as a child process of container_daemon()
   * It will call to unshare(), send unshare_pid after fork() and other information to container_daemon()
   * and call to run_chroot_container() to exec init command.
   * Note that on the devices that has pid ns enabled, if init process died, all processes in the container will be die.
   */
  // pthread_create() only allows one argument.
  struct CONTAINER_INFO *container_info = (struct CONTAINER_INFO *)arg;
#ifdef __RURI_DEV__
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
  // Try to create namespaces with unshare(), no warnings to show because daemon will be run in the background.
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
  if (unshare_pid > 0)
  {
    char *container_dir = strdup(container_info->container_dir);
    // Set socket address.
    struct sockaddr_un addr;
    connect_to_daemon(&addr);
    char container_pid[1024];
    sprintf(container_pid, "%d", unshare_pid);
    send_msg_client(FROM_PTHREAD__REGISTER_CONTAINER, addr);
    send_msg_client(FROM_PTHREAD__UNSHARE_CONTAINER_PID, addr);
    send_msg_client(container_pid, addr);
    send_msg_client(container_info->container_dir, addr);
    send_msg_client(FROM_PTHREAD__CAP_TO_DROP, addr);
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
// Run after chroot(), called by run_chroot_container()
void init_container()
{
  /*
   * It'll be run after chroot(), so `/` is the root dir of container now.
   * The device list and permissions are the same as common docker container.
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
// Daemon process used to store unshare container information and init unshare container.
void container_daemon()
{
  /*
   * 100% shit code at container_daemon.
   * If the code is hard to write,
   * it should be hard to read nya~
   */
  // Set process name.
  prctl(PR_SET_NAME, "rurid");
  // Ignore SIGTTIN, since rurid is running in the background, SIGTTIN may kill it.
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTTIN);
  sigprocmask(SIG_BLOCK, &sigs, 0);
  // For pthread_create()
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
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    container_info.drop_caplist[i] = INIT_VALUE;
  }
  pid_t unshare_pid = 0;
  char drop_caplist[CAP_LAST_CAP + 1][128];
  drop_caplist[0][0] = '\0';
  char *env[MAX_ENVS] = {NULL};
  char mountpoint[MAX_MOUNTPOINTS][PATH_MAX];
  mountpoint[0][0] = '\0';
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
  // Fork itself into the background.
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
        unshare_pid = atoi(read_node(container_dir, container)->unshare_pid);
        kill(unshare_pid, SIGKILL);
        send_msg_daemon(FROM_DAEMON__CONTAINER_KILLED, addr, sockfd);
        // Extra mountpoints will also be umounted in ruri client.
        send_msg_daemon(FROM_DAEMON__MOUNTPOINT, addr, sockfd);
        for (int i = 0;;)
        {
          if (read_node(container_dir, container)->mountpoint[i] != NULL)
          {
            send_msg_daemon(read_node(container_dir, container)->mountpoint[i + 1], addr, sockfd);
            i += 2;
          }
          else
          {
            break;
          }
        }
        send_msg_daemon(FROM_DAEMON__END_OF_MOUNTPOINT, addr, sockfd);
        // Deregister the container.
        container = del_container(container_dir, container);
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
          if (read_node(container_dir, container)->env[i] != NULL)
          {
            send_msg_daemon(read_node(container_dir, container)->env[i], addr, sockfd);
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
          if (read_node(container_dir, container)->drop_caplist[i] != NULL)
          {
            send_msg_daemon(read_node(container_dir, container)->drop_caplist[i], addr, sockfd);
            i++;
          }
          else
          {
            break;
          }
        }
        send_msg_daemon(FROM_DAEMON__END_OF_CAP_TO_DROP, addr, sockfd);
        send_msg_daemon(FROM_DAEMON__UNSHARE_CONTAINER_PID, addr, sockfd);
        send_msg_daemon(read_node(container_dir, container)->unshare_pid, addr, sockfd);
        goto _continue;
      }
      // If container is not active, init and register it.
      else
      {
        send_msg_daemon(FROM_DAEMON__CONTAINER_NOT_RUNNING, addr, sockfd);
        container_info.container_dir = NULL;
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
        container_info.container_dir = strdup(container_dir);
        free(container_dir);
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
      // Register the container.
      container = add_node(container_info.container_dir, container_info.unshare_pid, drop_caplist, env, mountpoint, container);
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
      msg = NULL;
      container_dir = strdup(read_msg_daemon(addr, sockfd));
      if (container_dir == NULL)
      {
        goto _continue;
      }
      container = del_container(container_dir, container);
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
// Do some checks before chroot()
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
// For run_unshare_container().
pid_t init_unshare_container(bool no_warnings)
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
pid_t join_ns_from_daemon(struct CONTAINER_INFO *container_info, struct sockaddr_un addr, bool no_warnings)
{
  /*
   * Request container_pid from daemon, use setns() to join namespaces and then fork() itself into them.
   * If container is not running, it will send the info to daemon, and daemon will register it and send its container_pid back.
   */
  pid_t unshare_pid = INIT_VALUE;
  char *msg = NULL;
  char *container_pid = NULL;
  send_msg_client(FROM_CLIENT__REGISTER_A_CONTAINER, addr);
  send_msg_client(container_info->container_dir, addr);
  msg = read_msg_client(addr);
  if (strcmp(msg, FROM_DAEMON__CONTAINER_NOT_RUNNING) == 0)
  {
    // Send init command to daemon.
    send_msg_client(FROM_CLIENT__INIT_COMMAND, addr);
    if (strcmp(container_info->init_command[0], "/bin/su") != 0)
    {
      for (int i = 0; i < 1023; i++)
      {
        if (container_info->init_command[i] != NULL)
        {
          send_msg_client(container_info->init_command[i], addr);
          free(container_info->init_command[i]);
          container_info->init_command[i] = NULL;
        }
        else
        {
          break;
        }
      }
      container_info->init_command[0] = strdup("/bin/su");
      container_info->init_command[1] = NULL;
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
  }
  else
  {
    for (int i = 0; i < MAX_ENVS; i++)
    {
      msg = read_msg_client(addr);
      if (strcmp(msg, FROM_DAEMON__END_OF_ENV) == 0)
      {
        break;
      }
      container_info->env[i] = strdup(msg);
      container_info->env[i + 1] = NULL;
      free(msg);
      msg = NULL;
    }
    free(msg);
    msg = read_msg_client(addr);
    free(msg);
    for (int i = 0;;)
    {
      msg = read_msg_client(addr);
      if (strcmp(msg, FROM_DAEMON__END_OF_CAP_TO_DROP) == 0)
      {
        break;
      }
      cap_from_name(msg, &container_info->drop_caplist[i]);
      container_info->drop_caplist[i + 1] = INIT_VALUE;
      i++;
      free(msg);
      msg = NULL;
    }
  }
  // Fix a bug that read_msg_client() returns NULL because container has not been registered properly.
  usleep(400000);
  // Ignore FROM_DAEMON__UNSHARE_CONTAINER_PID.
  msg = read_msg_client(addr);
  free(msg);
  msg = NULL;
  // Pid for setns().
  msg = read_msg_client(addr);
  container_pid = strdup(msg);
  free(msg);
  msg = NULL;
#ifdef __RURI_DEV__
  printf("%s%s\n", "Container pid from daemon:", container_pid);
#endif
  // Use setns() to enter namespaces created by rurid.
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
    if (strcmp(read_msg_client(addr), FROM_DAEMON__INIT_IS_ACTIVE) != 0)
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
   * If rurid is not running, it will create namespaces itself.
   * Or it will connect to rurid and use setns() to join namespaces created by rurid.
   * After fork() to send itself to new namespaces, it will call to run_chroot_container().
   */
  // Set default init.
  if (container_info->init_command[0] == NULL)
  {
    container_info->init_command[0] = strdup("/bin/su");
    container_info->init_command[1] = NULL;
  }
#ifdef __RURI_DEV__
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
  // Message to read.
  char *msg = NULL;
  bool daemon_running = false;
  if (connect_to_daemon(&addr))
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
  free(msg);
  msg = NULL;
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
  // Use exec() family function because system() may be unavailable now.
  usleep(200000);
  if (execv(container_info->init_command[0], container_info->init_command) == -1)
  {
    // Catch exceptions.
    fprintf(stderr, "\033[31mFailed to execute init `%s`\n", container_info->init_command[0]);
    fprintf(stderr, "execv() returned: %d\n", errno);
    fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
    error("QwQ");
  }
}
// Kill&umount container.
void umount_container(char *container_dir)
{
  /*
   * It will try to connect to rurid, and rurid will kill daemon_init_unshare_container() process of container if the container is running.
   * Then it will umount() container_dir and other directories in it.
   */
  // Set socket address.
  struct sockaddr_un addr;
  char *msg = NULL;
  char mountpoint[MAX_MOUNTPOINTS / 2][PATH_MAX];
  mountpoint[0][0] = '\0';
  if (!connect_to_daemon(&addr))
  {
    printf("\033[33mWarning: seems that container daemon is not running nya~\033[0m\n");
  }
  else
  {
    // Kill the container from daemon.
    send_msg_client(FROM_CLIENT__KILL_A_CONTAINER, addr);
    send_msg_client(container_dir, addr);
    msg = read_msg_client(addr);
    if (strcmp(msg, FROM_DAEMON__CONTAINER_NOT_RUNNING) == 0)
    {
      fprintf(stderr, "\033[33mWarning: seems that container is not running nya~\033[0m\n");
      free(msg);
      msg = NULL;
    }
    else
    {
      free(msg);
      msg = NULL;
      msg = read_msg_client(addr);
      free(msg);
      msg = NULL;
      // Get other mountpoints.
      for (int i = 0;;)
      {
        msg = read_msg_client(addr);
        if (strcmp(msg, FROM_DAEMON__END_OF_MOUNTPOINT) == 0)
        {
          free(msg);
          msg = NULL;
          break;
        }
        strcpy(mountpoint[i], msg);
        mountpoint[i + 1][0] = '\0';
        free(msg);
        msg = NULL;
      }
    }
  }
  // Get path to umount.
  char sys_dir[PATH_MAX];
  char proc_dir[PATH_MAX];
  char dev_dir[PATH_MAX];
  char to_umountpoint[PATH_MAX];
  strcpy(sys_dir, container_dir);
  strcpy(proc_dir, container_dir);
  strcpy(dev_dir, container_dir);
  strcat(sys_dir, "/sys");
  strcat(proc_dir, "/proc");
  strcat(dev_dir, "/dev");
  printf("\033[1;38;2;254;228;208mUmount container.\n");
  // Umount other mountpoints.
  for (int i = 0;;)
  {
    if (mountpoint[i][0] != 0)
    {
      strcpy(to_umountpoint, container_dir);
      strcat(to_umountpoint, mountpoint[i]);
      for (int j = 0; j < 10; j++)
      {
        umount2(to_umountpoint, MNT_DETACH | MNT_FORCE | MNT_EXPIRE);
        umount(to_umountpoint);
        usleep(20000);
      }
      i++;
    }
    else
    {
      break;
    }
  }
  // Force umount system runtime directories for 10 times.
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
}
// It works on my machine!!!
int main(int argc, char **argv)
{
  /*
   * 100% shit-code in main().
   * At least it works...
   */
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
  // These caps are kept by default:
  // CAP_SETGID,CAP_CHOWN,CAP_NET_RAW,CAP_DAC_OVERRIDE,CAP_FOWNER,CAP_FSETID,CAP_SETUID.
  cap_value_t drop_caplist[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    drop_caplist[i] = INIT_VALUE;
  }
  cap_value_t drop_caplist_common[] = {CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND, CAP_SYS_TIME};
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
    //============== [Other options] ==============
    if (strcmp(argv[index], "-v") == 0)
    {
      show_version_info();
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
    //=========End of [Other options]===========
    if (strcmp(argv[index], "-u") == 0)
    {
      use_unshare = true;
    }
    else if (strcmp(argv[index], "-U") == 0)
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
  // Set $PATH to the common value in GNU/Linux, because $PATH in termux will not work in containers.
  setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
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
