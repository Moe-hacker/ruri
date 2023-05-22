/*
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \\|     |//  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=---='
 *          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *                     佛祖保佑        永无BUG
 */
#include "ruri.h"
// For centering output.
void show_n_spaces(int n)
{
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
  // Do not show greeting if command-line args are wrong.
  if (greetings)
  {
    show_greetings();
  }
  printf("\033[1;38;2;254;228;208mUsage:\n");
  printf("  ruri [options] [container directory] (init command)\n");
  printf("Options:\n");
  printf("  -v          :Show version info\n");
  printf("  -h          :Show helps\n");
  printf("  -D          :Run rurid\n");
  printf("  -u          :Enable unshare feature\n");
  printf("  -U          :Try to umount container,please reboot your device instead for better security\n");
  printf("  -d          :Drop more capabilities for better security\n");
  printf("  -p          :Run privileged container\n");
  printf(" --keep [cap] :Keep the specified cap\n");
  printf(" --drop [cap] :Drop the specified cap\n");
  printf("  -w          :Disable warnings\n");
  printf("This program should be run with root privileges\n");
  printf("Unset $LD_PRELOAD before running this program to fix issues in termux\033[0m\n");
  return;
}
// Add a cap to caplist.
void add_to_list(cap_value_t *list, int length, cap_value_t cap)
{
  bool in = false;
  // Check if the cap to add is already in caplist.
  for (int i = 0; i <= length; i++)
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
    for (int k = 0; k <= length; k++)
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
  for (int i = 0; i <= length; i++)
  {
    if (list[i] == cap)
    {
      while (i <= length - 1)
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
struct CONTAINERS *add_node(char *container_dir, char *unshare_pid, char *drop_caplist[CAP_LAST_CAP + 1], struct CONTAINERS *container)
{
  if (container == NULL)
  {
    // Request memory of container struct.
    container = (struct CONTAINERS *)malloc(sizeof(struct CONTAINERS));
    container->container_dir = strdup(container_dir);
    container->unshare_pid = strdup(unshare_pid);
    for (int i = 0; i <= (CAP_LAST_CAP + 1); i++)
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
    return container;
  }
  else
  {
    container->container = add_node(container_dir, unshare_pid, drop_caplist, container->container);
    return container;
  }
}
// Return info of a container.
struct CONTAINERS *read_node(char *container_dir, struct CONTAINERS *container)
{
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
  else
  {
    return NULL;
  }
}
// Delete a node from CONTAINERS struct.
struct CONTAINERS *del_node(struct CONTAINERS *container)
{
  if (container == NULL)
  {
    return container;
  }
  else
  {
    container = container->container;
    container = del_node(container);
  }
  return container;
}
// Delete a container from CONTAINERS struct.
struct CONTAINERS *del_container(char *container_dir, struct CONTAINERS *container)
{
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
  char *msg;
  unsigned int size = sizeof(addr);
  // Accept a connection.
  int sock_new = accept(sockfd, (struct sockaddr *)&addr, &size);
  // Set timeout duration.
  struct timeval timeout = {3, 0};
  setsockopt(sock_new, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  setsockopt(sock_new, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  // Maybe unnecessary.
  msg = (char *)malloc(4096);
  // Read messages.
  read(sock_new, msg, 4096);
  close(sock_new);
  return msg;
}
// For client, return the messages have been read.
char *read_msg_client(struct sockaddr_un addr)
{
  char *msg;
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
  // Maybe unnecessary.
  msg = (char *)malloc(4096);
  // Read messages.
  read(sockfd, msg, 4096);
  close(sockfd);
  return msg;
}
// For daemon, init an unshare container in the background.
void *init_unshare_container(void *arg)
{
  // pthread_create() only allows one argument.
  struct CONTAINER_INFO *container_info = (struct CONTAINER_INFO *)arg;
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
    if (!tmpdir || strcmp(tmpdir, "") == 0)
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
    // Redirect stdin/stdout.
    freopen("/dev/null", "r", stdout);
    freopen("/dev/zero", "r", stdout);
    bool no_warinings = true;
    run_chroot_container(container_info->container_dir, container_info->drop_caplist, &no_warinings, container_info->init_command);
  }
  return NULL;
}
// Run after chroot(), called by run_chroot_container()
void init_container(void)
{
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
// TODO:
// 遵守caplist
// XXX
// Received messages and reply contents:
// --------------------------------------------------------------------------------------------------------------------------
// |                                 read                               |            send             |      comment
// --------------------------------------------------------------------------------------------------------------------------
// |                                 Nya?                               |            Nya!             | Test messasge
// |                          del+${container_dir}                      |            OK/Fail          | Kill a container
// |                                 info                               |                             | wait for ${container_dir}
// |                          ${container_dir}                          |   Pid+$container_pid//NaN   | Read container_dir, check if container is already running and send container_pid to ruri
// |     init+${init_command}+endinit+caplist+${caplist}+endcaplist     |                             | Read information of container and init container
// |pid+${container_pid}+${contaiiner_dir}+caplist+${caplist}+endcaplist|                             | Read container info from child process
void container_daemon(void)
{
  // Set process name.
  prctl(PR_SET_NAME, "rurid", NULL, NULL, NULL);
  pthread_t pthread_id;
  // Check if we are running with root privileges.
  if (getuid() != 0)
  {
    fprintf(stderr, "\033[31mError: this program should be run with root privileges !\033[0m\n");
    exit(1);
  }
  // Check if $LD_PRELOAD is unset.
  char *ld_preload = getenv("LD_PRELOAD");
  if (ld_preload && strcmp(ld_preload, "") != 0)
  {
    fprintf(stderr, "\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run.\033[0m\n");
    exit(1);
  }
  // Create container struct.
  struct CONTAINERS *container = NULL;
  // Set default value.
  // Message to read.
  char *msg;
  // Container info.
  char *container_dir;
  struct CONTAINER_INFO container_info;
  container_info.container_dir = NULL;
  *container_info.init_command = NULL;
  container_info.unshare_pid = NULL;
  for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
  {
    container_info.drop_caplist[i] = INIT_VALUE;
  }
  pid_t unshare_pid;
  char *drop_caplist[CAP_LAST_CAP + 1];
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
  if (!tmpdir || strcmp(tmpdir, "") == 0)
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
  if (strcmp("Nya!", read_msg_client(addr)) == 0)
  {
    close(sockfd);
    printf("\033[31mDaemon already running.\n");
    exit(1);
  }
  else
  {
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
    msg = read_msg_server(addr, sockfd);
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
        *container_info.init_command = NULL;
        container_info.unshare_pid = NULL;
        for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
        {
          container_info.drop_caplist[i] = INIT_VALUE;
        }
        // Read init command.
        read_msg_server(addr, sockfd);
        int i = 0;
        while (true)
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
        read_msg_server(addr, sockfd);
        i = 0;
        while (true)
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
      read_msg_server(addr, sockfd);
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
      container = add_node(container_info.container_dir, container_info.unshare_pid, drop_caplist, container);
      // Send ${unshare_pid} to ruri.
      send_msg_server(container_info.unshare_pid, addr, sockfd);
      container_info.container_dir = NULL;
      *container_info.init_command = NULL;
      container_info.unshare_pid = NULL;
      for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
      {
        container_info.drop_caplist[i] = INIT_VALUE;
      }
    }
  }
}
// Used for run_chroot_container, do some checks before chroot()
bool check_container(char *container_dir)
{
  // Check if container directory is given.
  if (container_dir == NULL)
  {
    fprintf(stderr, "\033[31mError: container directory is not set !\033[0m\n");
    return false;
  }
  // Refuse to use `/` for container directory.
  // FIXME:
  // Seems that this line will crash on Android 13. I dont't know why now.
  // Gdb logs:
  // Breakpoint 2, check_container (
  // container_dir=0x7ffffffdb0 "./t") at container.c:601
  // 601       if (strcmp(container_dir, "/") == 0)
  // (gdb) c
  // Continuing.
  //
  // Program received signal SIGSEGV, Segmentation fault.
  // 0x0000007ff4505a10 in __strlen_aarch64 ()
  //  from /apex/com.android.runtime/lib64/bionic/libc.so
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
  if (ld_preload && (strcmp(ld_preload, "") != 0))
  {
    fprintf(stderr, "\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run.\033[0m\n");
    return false;
  }
  // Check if container directory exists.
  DIR *direxist;
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
void run_unshare_container(char *container_dir, cap_value_t drop_caplist[], bool *no_warnings, char *init[])
{
  // Set default init.
  if (init[0] == NULL)
  {
    init[0] = "/bin/su";
    init[1] = "-";
    init[2] = NULL;
  }
  pid_t unshare_pid = INIT_VALUE;
  // Get the absolute path of container.
  realpath(container_dir, container_dir);
  // Set socket address.
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if (!tmpdir || (strcmp(tmpdir, "") == 0))
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
  if (strcmp("Nya!", read_msg_client(addr)) == 0)
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
    send_msg_client(container_dir, addr);
    if (strcmp(read_msg_client(addr), "NaN") == 0)
    {
      send_msg_client("init", addr);
      for (int i = 0; true; i++)
      {
        if (init[i] != NULL)
        {
          send_msg_client(init[i], addr);
        }
        else
        {
          break;
        }
      }
      send_msg_client("endinit", addr);
      init[0] = "/bin/su";
      init[1] = "-";
      init[2] = NULL;
      if (drop_caplist[0] != INIT_VALUE)
      {
        for (int i = 0; i < CAP_LAST_CAP + 1; i++)
        {
          if (drop_caplist[i] != INIT_VALUE)
          {
            send_msg_client(cap_to_name(drop_caplist[i]), addr);
            // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN
            if (!drop_caplist[i])
            {
              send_msg_client(cap_to_name(0), addr);
            }
          }
        }
      }
      send_msg_client("endcaplist", addr);
    }
    // For setns()
    usleep(200000);
    char *container_pid = read_msg_client(addr);
    char cgroup_ns_file[PATH_MAX];
    char ipc_ns_file[PATH_MAX];
    char mount_ns_file[PATH_MAX];
    char pid_ns_file[PATH_MAX];
    char time_ns_file[PATH_MAX];
    char uts_ns_file[PATH_MAX];
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
      setns(fd, 0) == 0 ?: perror("setns");
    }
    fd = open(pid_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that pid namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0) == 0 ?: perror("setns");
    }
    fd = open(time_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that time namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0) == 0 ?: perror("setns");
    }
    fd = open(uts_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that uts namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0) == 0 ?: perror("setns");
    }
    fd = open(cgroup_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that cgroup namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0) == 0 ?: perror("setns");
    }
    fd = open(ipc_ns_file, O_RDONLY | O_CLOEXEC);
    if (fd < 0 && !no_warnings)
    {
      printf("\033[33mWarning: seems that ipc namespace is not supported on this device\033[0m\n");
    }
    else
    {
      setns(fd, 0) == 0 ?: perror("setns");
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
    run_chroot_container(container_dir, drop_caplist, no_warnings, init);
  }
  return;
}
// Run chroot container.
// Also used for run_unshare_container and init_unshare_container.
void run_chroot_container(char *container_dir, cap_value_t drop_caplist[], bool *no_warnings, char **init)
{
  // Set default init.
  if (init[0] == NULL)
  {
    init[0] = "/bin/su";
    init[1] = "-";
    init[2] = NULL;
  }
  if (!check_container(container_dir))
  {
    exit(1);
  }
  // chroot into container.
  chroot(container_dir);
  chdir("/");
  // Check if system runtime files are already created.
  DIR *direxist;
  if ((direxist = opendir("/sys/kernel")) == NULL)
  {
    init_container();
  }
  else
  {
    closedir(direxist);
  }
  // Drop caps.
  if (drop_caplist[0] != INIT_VALUE)
  {
    for (int i = 0; i < CAP_LAST_CAP + 1; i++)
    {
      if (drop_caplist[i] != INIT_VALUE)
      {
        if (cap_drop_bound(drop_caplist[i]) != 0 && !no_warnings)
        {
          fprintf(stderr, "\033[33mWarning: Failed to drop cap `%s`\n", cap_to_name(drop_caplist[i]));
          fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
        }
      }
      // 0 is a nullpoint on some device,so I have to use this way for CAP_CHOWN
      if (!drop_caplist[i])
      {
        if (cap_drop_bound(0) != 0 && !no_warnings)
        {
          fprintf(stderr, "\033[33mWarning: Failed to drop cap `%s`\n", cap_to_name(0));
          fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
        }
      }
    }
  }
  // Login to container.
  // Use exec() family function because system() may be unavailable now.
  usleep(200000);
  if (execv(init[0], init) == -1)
  {
    // Catch exceptions.
    fprintf(stderr, "\033[31mFailed to execute init `%s`\n", init[0]);
    fprintf(stderr, "execv() returned: %d\n", errno);
    fprintf(stderr, "error reason: %s\033[0m\n", strerror(errno));
    exit(1);
  }
}
// Kill&umount container.
void umount_container(char *container_dir)
{
  realpath(container_dir, container_dir);
  if (strcmp(container_dir, "/") == 0)
  {
    fprintf(stderr, "\033[31mError: `/` is not allowed to use as a container directory.\033[0m\n");
    exit(1);
  }
  // Check if we are running with root privileges.
  if (getuid() != 0)
  {
    fprintf(stderr, "\033[31mError: this program should be run with root privileges !\033[0m\n");
    exit(1);
  }
  // Check if container directory exists.
  DIR *direxist;
  if ((direxist = opendir(container_dir)) == NULL)
  {
    fprintf(stderr, "\033[31mError: container directory does not exist !\033[0m\n");
    exit(1);
  }
  else
  {
    closedir(direxist);
  }
  // Set socket address.
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  // In termux, $TMPDIR is not /tmp, so we get $TMPDIR for tmp path.
  char *tmpdir = getenv("TMPDIR");
  if (!tmpdir || (strcmp(tmpdir, "") == 0))
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
  if (strcmp("Nya!", read_msg_client(addr)) != 0)
  {
    printf("\033[33mWarning: seems that container daemon is not running\033[0m\n");
  }
  else
  {
    send_msg_client("del", addr);
    send_msg_client(container_dir, addr);
    if (strcmp(read_msg_client(addr), "Fail") == 0)
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
  printf("\033[1;38;2;254;228;208mUmounting container......\n");
  for (int i = 1; i < 10; i++)
  {
    umount2(sys_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
    umount2(dev_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
    umount2(proc_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
    umount2(container_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
  }
  return;
}
int main(int argc, char **argv)
{
  // Set process name.
  prctl(PR_SET_NAME, "ruri", NULL, NULL, NULL);
  // Check if arguments are given.
  if (argc <= 1)
  {
    fprintf(stderr, "\033[31mError: too few arguments !\033[0m\n");
    show_helps(0);
    exit(1);
  }
  // Set default value.
  bool on = true;
  bool *use_unshare = NULL;
  bool *no_warnings = NULL;
  char *container_dir = NULL;
  bool *greetings = NULL;
  bool *privileged = NULL;
  char *init[1024] = {NULL};
  // These caps are kept by default:
  // CAP_SETGID,CAP_CHOWN,CAP_NET_RAW,CAP_DAC_OVERRIDE,CAP_FOWNER,CAP_FSETID,CAP_SETUID
  cap_value_t drop_caplist[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i <= (CAP_LAST_CAP + 1); i++)
  {
    drop_caplist[i] = INIT_VALUE;
  }
  cap_value_t drop_caplist_common[] = {CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND};
  cap_value_t drop_caplist_unprivileged[] = {CAP_SYS_ADMIN, CAP_SYS_MODULE, CAP_SYS_RAWIO, CAP_SYS_PACCT, CAP_SYS_NICE, CAP_SYS_RESOURCE, CAP_SYS_TTY_CONFIG, CAP_AUDIT_CONTROL, CAP_MAC_OVERRIDE, CAP_MAC_ADMIN, CAP_NET_ADMIN, CAP_SYSLOG, CAP_DAC_READ_SEARCH, CAP_LINUX_IMMUTABLE, CAP_NET_BROADCAST, CAP_IPC_LOCK, CAP_IPC_OWNER, CAP_SYS_PTRACE, CAP_SYS_BOOT, CAP_LEASE, CAP_WAKE_ALARM, CAP_BLOCK_SUSPEND, CAP_SYS_CHROOT, CAP_SETPCAP, CAP_MKNOD, CAP_AUDIT_WRITE, CAP_SETFCAP, CAP_KILL, CAP_NET_BIND_SERVICE, CAP_SYS_TIME, CAP_AUDIT_READ, CAP_PERFMON, CAP_BPF, CAP_CHECKPOINT_RESTORE};
  cap_value_t keep_caplist_extra[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i <= (CAP_LAST_CAP + 1); i++)
  {
    keep_caplist_extra[i] = INIT_VALUE;
  }
  cap_value_t drop_caplist_extra[CAP_LAST_CAP + 1] = {};
  for (int i = 0; i <= (CAP_LAST_CAP + 1); i++)
  {
    drop_caplist_extra[i] = INIT_VALUE;
  }
  cap_value_t cap = -1;
  // Parse command-line arguments.
  for (int arg_num = 1; arg_num < argc; arg_num++)
  {
    if (strcmp(argv[arg_num], "-v") == 0)
    {
      show_version_info();
      exit(0);
    }
    else if (strcmp(argv[arg_num], "-D") == 0)
    {
      container_daemon();
      exit(0);
    }
    else if (strcmp(argv[arg_num], "-h") == 0)
    {
      greetings = &on;
      show_helps(greetings);
      exit(0);
    }
    else if (strcmp(argv[arg_num], "-u") == 0)
    {
      use_unshare = &on;
    }
    else if (strcmp(argv[arg_num], "-U") == 0)
    {
      arg_num += 1;
      if (argv[arg_num] != NULL)
      {
        umount_container(argv[arg_num]);
        exit(0);
      }
      else
      {
        fprintf(stderr, "\033[31mError: container directory is not set !\033[0m\n");
        exit(1);
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
      privileged = &on;
    }
    else if (strcmp(argv[arg_num], "-w") == 0)
    {
      no_warnings = &on;
    }
    else if (strcmp(argv[arg_num], "--keep") == 0)
    {
      arg_num++;
      if (cap_from_name(argv[arg_num], &cap) == 0)
      {
        add_to_list(keep_caplist_extra, CAP_LAST_CAP + 1, cap);
      }
      else
      {
        fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", argv[arg_num], "`");
        exit(1);
      }
    }
    else if (strcmp(argv[arg_num], "--drop") == 0)
    {
      arg_num++;
      if (cap_from_name(argv[arg_num], &cap) == 0)
      {
        add_to_list(drop_caplist_extra, CAP_LAST_CAP + 1, cap);
      }
      else
      {
        fprintf(stderr, "%s%s%s\033[0m\n", "\033[31mError: unknow capability `", argv[arg_num], "`");
        exit(1);
      }
    }
    else if ((strchr(argv[arg_num], '/') && strcmp(strchr(argv[arg_num], '/'), argv[arg_num]) == 0) || (strchr(argv[arg_num], '.') && strcmp(strchr(argv[arg_num], '.'), argv[arg_num]) == 0))
    {
      container_dir = argv[arg_num];
      arg_num++;
      // Arguments after container_dir will be read as init command.
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
      exit(1);
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
    for (unsigned long i = 0; i <= (sizeof(drop_caplist_extra) / sizeof(drop_caplist_extra[0])); i++)
    {
      if (drop_caplist_extra[i] != INIT_VALUE)
      {
        add_to_list(drop_caplist, CAP_LAST_CAP + 1, drop_caplist_extra[i]);
      }
    }
  }
  if (keep_caplist_extra[0] != INIT_VALUE)
  {
    for (unsigned long i = 0; i <= (sizeof(keep_caplist_extra) / sizeof(keep_caplist_extra[0])); i++)
    {
      if (keep_caplist_extra[i] != INIT_VALUE)
      {
        del_from_list(drop_caplist, CAP_LAST_CAP + 1, keep_caplist_extra[i]);
      }
    }
  }
  // Pure-chroot and unshare container are two functions now.
  if (use_unshare)
  {
    run_unshare_container(container_dir, drop_caplist, no_warnings, init);
  }
  else
  {
    run_chroot_container(container_dir, drop_caplist, no_warnings, init);
  }
  return 0;
}
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
