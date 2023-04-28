//  ██╗ ██╗  ██╗   ███████╗
// ████████╗ ██║ ██╔══════╝
// ╚██╔═██╔╝ ██║ ██║
// ████████╗ ╚═╝ ██║
// ╚██╔═██╔╝ ██╗  ╚███████╗
// ╚═╝ ╚═╝  ╚═╝   ╚══════╝
// ╔═╝  ╔═║╔═║╔═║╔═╝╔═║╔═║╔╔ ╔╔ ╝╔═ ╔═╝  ║  ╔═║╔═ ╔═╝║ ║╔═║╔═╝╔═╝
// ║    ╔═╝╔╔╝║ ║║ ║╔╔╝╔═║║║║║║║║║ ║║ ║  ║  ╔═║║ ║║ ║║ ║╔═║║ ║╔═╝
// ══╝  ╝  ╝ ╝══╝══╝╝ ╝╝ ╝╝╝╝╝╝╝╝╝ ╝══╝  ══╝╝ ╝╝ ╝══╝══╝╝ ╝══╝══╝
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
#include "container.h"
// For centering output.
void show_n_char(int num)
{
  char *space = " ";
  int count;
  for (count = 1; count <= num; count++)
  {
    putchar(space[0]);
  }
  return;
}
// Greeting information.
// As an easter agg.
void show_greetings(void)
{
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  short row = size.ws_col;
  row -= 44;
  row /= 2;
  show_n_char(row);
  printf("%s\n", "\033[1;38;2;66;66;66m               ▅▅▀▀▀▀▀▀▀▀▀▀▀▀▅");
  show_n_char(row);
  printf("%s\n", "          ▅▅▀▀▀               ▀▀▅▅");
  show_n_char(row);
  printf("%s\n", "     ▅▅▅▀▀            ▅           ▀▅");
  show_n_char(row);
  printf("%s\n", "      ▅▀      ▅▀█▅▅▀▀▅▀▅        ▅▅  ▀▅");
  show_n_char(row);
  printf("%s\n", "     ▅▀   █▅▀▀  ▀     ▀ ▀▀▅▅    █ ▀▀▅ █");
  show_n_char(row);
  printf("%s\n", "    ▅▀   ▅▀  ▅▀      ▀▅    ▀▅   █▅███▀█");
  show_n_char(row);
  printf("%s\n", "  ▅▅█▀▅ █ ▅▅▀          ▀▀   █   ████   █");
  show_n_char(row);
  printf("%s\n", "      █ █ ▅▅▅▅▅        ▅▅▅▅▅ █  ▀█▀    █");
  show_n_char(row);
  printf("%s\n", "      █ █▀ ▅▅▅ ▀      ▀ ▅▅▅ ▀█   █     █");
  show_n_char(row);
  printf("%s\n", "      █ █ █\033[40;31m█▀█\033[0m\033[1;38;2;66;66;66m█        █\033[40;31m█▀█\033[0m\033[1;38;2;66;66;66m█ █   █     █");
  show_n_char(row);
  printf("%s\n", "     █  █ █\033[31m███\033[1;38;2;66;66;66m█        █\033[31m███\033[1;38;2;66;66;66m█ █   █     ▀▅");
  show_n_char(row);
  printf("%s\n", "    ▅▀  █  ▀▀▀          ▀▀▀  █   █      █");
  show_n_char(row);
  printf("%s\n", "  ▅▀▅▀ █                     █   █      █");
  show_n_char(row);
  printf("%s\n", " █   █ ▀▅ ▅▀▅   ▅▀▅   ▅▅     █   █      ▀▅");
  show_n_char(row);
  printf("%s\n", "▅█▅▅██▅ ▅██  ▀███ ▅████ ▀▅█▀▅▀   █       ▀▅");
  show_n_char(row);
  printf("%s\n", "███████ ▀██████████████████▀▀             █");
  show_n_char(row);
  printf("%s\n", " █    ▀▅  ██▀ ▀██▀▀██▀▀██▀█     █▀         █");
  show_n_char(row);
  printf("%s\n", " ▀▅     ▀▀█              ▅▀     █          █");
  show_n_char(row);
  printf("%s\n", "   ▀▅    █               █     ██        ▅▀");
  show_n_char(row);
  printf("%s\n", "     ▀▅▅▅▀                ▀▀▀▀▀ █        █");
  show_n_char(row);
  printf("%s\n", "        ▀                       ▀        ▀");
  show_n_char(row);
  printf("%s\n", "           「Keep moe,keep cool」\033[0m");
  return;
}
void show_version_info(void)
{
  printf("\033[1;38;2;254;228;208m%s%s%s", "moe-container ", _CONTAINER_VERSION, "\n");
  printf("Copyright (C) 2022-2023 Moe-hacker\n");
  printf("            (>_×)\n");
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
// Help pages.
void show_helps(bool greetings)
{
  if (greetings)
  {
    show_greetings();
  }
  printf("\033[1;38;2;254;228;208mUsage:\n");
  printf("  container [options] [container directory] (init command)\n");
  printf("Options:\n");
  printf("  -v          :Show version info\n");
  printf("  -h          :Show helps\n");
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
// Add a cap from caplist.
void add_to_list(cap_value_t *list, int length, cap_value_t cap)
{
  int j = 0;
  for (int i = 0; i <= length; i++)
  {
    if (list[i] == cap)
    {
      j = 1;
      break;
    }
  }
  if (j == 0)
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
// Run chroot container.
void chroot_container(char *container_dir, cap_value_t drop_caplist[], bool *use_unshare, bool *no_warnings, char *init[])
{
  // Check if container directory is given.
  if (!container_dir)
  {
    fprintf(stderr, "\033[31mError: container directory is not set !\033[0m\n");
    exit(1);
  }
  // Refuse to use `/` for container directory.
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
  // Check if $LD_PRELOAD is unset.
  char *ld_preload = getenv("LD_PRELOAD");
  if (ld_preload && strcmp(ld_preload, "") != 0)
  {
    fprintf(stderr, "\033[31mError: please unset $LD_PRELOAD before running this program or use su -c `COMMAND` to run.\033[0m\n");
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
  // Set default value if not using unshare.
  pid_t unshare_pid = INIT_VALUE;
  // Unshare itself into new namespaces.
  if (use_unshare)
  {
    prctl(PR_SET_NAME, "moe_unshare", NULL, NULL, NULL);
    // Try to create namespaces with unshare().
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
    if (unshare_pid != 0)
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
  if (unshare_pid == 0 || unshare_pid == INIT_VALUE)
  {
    // chroot into container.
    chroot(container_dir);
    chdir("/");
    mkdir("/sys", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
    mkdir("/proc", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
    mkdir("/dev", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
    // Check if system runtime files are already created.
    DIR *sysmounted;
    if ((sysmounted = opendir("/sys/kernel")) == NULL)
    {
      // umount /proc for two times because in my device,it has been mounted twice.
      umount("/proc");
      umount("/proc");
      // Fix issues in archlinux containers.
      mount("/", "/", NULL, MS_BIND, NULL);
      // mount proc,sys and dev.
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
      // Protect some system runtime directories.
      mount("/proc/bus", "/proc/bus", "proc", MS_BIND | MS_RDONLY, NULL);
      mount("/proc/fs", "/proc/fs", "proc", MS_BIND | MS_RDONLY, NULL);
      mount("/proc/irq", "/proc/irq", "proc", MS_BIND | MS_RDONLY, NULL);
      mount("/proc/sys", "/proc/sys", "proc", MS_BIND | MS_RDONLY, NULL);
      mount("/proc/asound", "/proc/asound", "proc", MS_BIND | MS_RDONLY, NULL);
      mount("/proc/scsi", "/proc/scsi", "proc", MS_BIND | MS_RDONLY, NULL);
      mount("/sys/firmware", "/sys/firmware", "sysfs", MS_BIND | MS_RDONLY, NULL);
      // For making dev nodes.
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
  return;
}
// Umount container.
void umount_container(char *container_dir)
{
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
  for (int i = 1; i < 10; i++)
  {
    umount2(sys_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
    umount2(dev_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
    umount2(proc_dir, MNT_DETACH | MNT_FORCE);
    usleep(200000);
  }
  return;
}
struct CONTAINER *add_node(char *container_dir, char *is_unshare, char *unshare_pid, struct CONTAINER *container)
{
  if (container == NULL)
  {
    container=(struct CONTAINER *)malloc(sizeof(struct CONTAINER));
    container->container_dir=strdup(container_dir);
    container->is_unshare = strdup(is_unshare);
    container->unshare_pid = strdup(unshare_pid);
    container->active_containers = 1;
    container->container=NULL;
  }
  else
  {
    container=add_node(container_dir, is_unshare, unshare_pid, container->container);
  }
  return container;
}
struct CONTAINER *del_node(struct CONTAINER *container){
  if(container==NULL){
    return container;
  }else{
    free(container);
    container=container->container;
    container=del_node(container);
  }
  return container;
}
struct CONTAINER *del_container(char *container_dir, struct CONTAINER *container)
{
  if(container==NULL){
    return container;
  }
  if (strcmp(container->container_dir, container_dir) == 0)
  {
    if(container->active_containers>1){
      container->active_containers--;
    }else{
      container=del_node(container);
    }
  }
  else
  {
    del_container(container_dir, container->container);
  }
  return container;
}
bool container_active(char *container_dir, struct CONTAINER *container)
{
  if (container == NULL)
  {
    return false;
  }
  else if (strcmp(container->container_dir, container_dir) == 0)
  {
    return true;
  }
  else
  {
    if(container_active(container_dir, container->container)){
      return true;
    }else{
      return false;
    }
  }
}
void add_active_containers(char *container_dir, struct CONTAINER *container)
{
  if (strcmp(container->container_dir, container_dir) == 0)
  {
    container->active_containers += 1;
  }
  else
  {
    add_active_containers(container_dir, container->container);
  }
}
void container_daemon(void)
{ 
  struct CONTAINER *container;
  /*将被删除
  container=add_node("x","x","x",container);
  container=add_node("y","x","x",container);
  container=add_node("z","x","x",container);
  container=del_container("x",container);
  if(container_active("x",container)){
    printf("x");
  }
  */
}
int main(int argc, char **argv)
{
  // Set process name.
  prctl(PR_SET_NAME, "moe_container", NULL, NULL, NULL);
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
  char *init[1024] = {0};
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
    else if (strcmp(argv[arg_num], "--daemon") == 0)
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
      for (int i = 0; i < (sizeof(drop_caplist_unprivileged) / sizeof(drop_caplist_unprivileged[0])); i++)
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
    else if ((strchr(argv[arg_num], '/') && strcmp(strchr(argv[arg_num], '/'), argv[arg_num]) == 0) || strchr(argv[arg_num], '.') && strcmp(strchr(argv[arg_num], '.'), argv[arg_num]) == 0)
    {
      container_dir = argv[arg_num];
      arg_num++;
      int init_arg_num = 0;
      if (argv[arg_num])
      {
        while (arg_num <= argc)
        {
          init[init_arg_num] = argv[arg_num];
          arg_num++;
          init_arg_num++;
        }
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
    for (int i = 0; i < (sizeof(drop_caplist_common) / sizeof(drop_caplist_common[0])); i++)
    {
      drop_caplist[i] = drop_caplist_common[i];
    }
  }
  // Comply with capability-set policy specified.
  if (drop_caplist_extra[0] != INIT_VALUE)
  {
    for (int i = 0; i <= (sizeof(drop_caplist_extra) / sizeof(drop_caplist_extra[0])); i++)
    {
      if (drop_caplist_extra[i] != INIT_VALUE)
      {
        add_to_list(drop_caplist, CAP_LAST_CAP + 1, drop_caplist_extra[i]);
      }
    }
  }
  if (keep_caplist_extra[0] != INIT_VALUE)
  {
    for (int i = 0; i <= (sizeof(keep_caplist_extra) / sizeof(keep_caplist_extra[0])); i++)
    {
      if (keep_caplist_extra[i] != INIT_VALUE)
      {
        del_from_list(drop_caplist, CAP_LAST_CAP + 1, keep_caplist_extra[i]);
      }
    }
  }
  // Set default init.
  if (!init[0])
  {
    init[0] = "/bin/su";
    init[1] = "-";
    init[2] = NULL;
  }
  chroot_container(container_dir, drop_caplist, use_unshare, no_warnings, init);
  return 0;
}
//  ██╗ ██╗  ███████╗   ████╗   ███████╗
// ████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
// ╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
// ████████╗ ██╔══╝   ██║   ██║ ██╔══╝
// ╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
//  ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝
