// ██╗ ██╗  ██╗   ███████╗
//████████╗ ██║ ██╔══════╝
//╚██╔═██╔╝ ██║ ██║
//████████╗ ╚═╝ ██║
//╚██╔═██╔╝ ██╗  ╚███████╗
// ╚═╝ ╚═╝  ╚═╝   ╚══════╝
//╔═╝  ╔═║╔═║╔═║╔═╝╔═║╔═║╔╔ ╔╔ ╝╔═ ╔═╝  ║  ╔═║╔═ ╔═╝║ ║╔═║╔═╝╔═╝
//║    ╔═╝╔╔╝║ ║║ ║╔╔╝╔═║║║║║║║║║ ║║ ║  ║  ╔═║║ ║║ ║║ ║╔═║║ ║╔═╝
//══╝  ╝  ╝ ╝══╝══╝╝ ╝╝ ╝╝╝╝╝╝╝╝╝ ╝══╝  ══╝╝ ╝╝ ╝══╝══╝╝ ╝══╝══╝
//Heders was written into container.h.
#include "container.h"
//Only for centering output.
void show_n_char(int num){
  char *space=" ";
  int count;
  for (count = 1; count <= num; count++){
    putchar(space[0]);
  }
}
//Greeting information.
//As an easter agg.
void greeting(){
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  short row=size.ws_col;
  row-=44;
  row/=2;
  show_n_char(row);
  printf("%s\n","\033[30m               ▅▅▀▀▀▀▀▀▀▀▀▀▀▀▅");
  show_n_char(row);
  printf("%s\n","          ▅▅▀▀▀               ▀▀▅▅");
  show_n_char(row);
  printf("%s\n","     ▅▅▅▀▀            ▅           ▀▅");
  show_n_char(row);
  printf("%s\n","      ▅▀      ▅▀█▅▅▀▀▅▀▅        ▅▅  ▀▅");
  show_n_char(row);
  printf("%s\n","     ▅▀   █▅▀▀  ▀     ▀ ▀▀▅▅    █ ▀▀▅ █");
  show_n_char(row);
  printf("%s\n","    ▅▀   ▅▀  ▅▀      ▀▅    ▀▅   █▅███▀█");
  show_n_char(row);
  printf("%s\n","  ▅▅█▀▅ █ ▅▅▀          ▀▀   █   ████   █");
  show_n_char(row);
  printf("%s\n","      █ █ ▅▅▅▅▅        ▅▅▅▅▅ █  ▀█▀    █");
  show_n_char(row);
  printf("%s\n","      █ █▀ ▅▅▅ ▀      ▀ ▅▅▅ ▀█   █     █");
  show_n_char(row);
  printf("%s\n","      █ █ █\033[40;31m█▀█\033[0m\033[30m█        █\033[40;31m█▀█\033[0m\033[30m█ █   █     █");
  show_n_char(row);
  printf("%s\n","     █  █ █\033[31m███\033[30m█        █\033[31m███\033[30m█ █   █     ▀▅");
  show_n_char(row);
  printf("%s\n","    ▅▀  █  ▀▀▀          ▀▀▀  █   █      █");
  show_n_char(row);
  printf("%s\n","  ▅▀▅▀ █                     █   █      █");
  show_n_char(row);
  printf("%s\n"," █   █ ▀▅ ▅▀▅   ▅▀▅   ▅▅     █   █      ▀▅");
  show_n_char(row);
  printf("%s\n","▅█▅▅██▅ ▅██  ▀███ ▅████ ▀▅█▀▅▀   █       ▀▅");
  show_n_char(row);
  printf("%s\n","███████ ▀██████████████████▀▀             █");
  show_n_char(row);
  printf("%s\n"," █    ▀▅  ██▀ ▀██▀▀██▀▀██▀█     █▀         █");
  show_n_char(row);
  printf("%s\n"," ▀▅     ▀▀█              ▅▀     █          █");
  show_n_char(row);
  printf("%s\n","   ▀▅    █               █     ██        ▅▀");
  show_n_char(row);
  printf("%s\n","     ▀▅▅▅▀                ▀▀▀▀▀ █        █");
  show_n_char(row);
  printf("%s\n","        ▀                       ▀        ▀");
  show_n_char(row);
  printf("%s\n","           「Keep moe,keep cool」");
}
//Run unshare container.
void chroot_container(char *CONTAINER_DIR){
  greeting();
  //chroot into container.
  chroot(CONTAINER_DIR);
  chdir("/");
  printf("\033[1;38;2;166;227;161mRun unshare container.\033[0m\n");
  //umount /proc for two times because in my device,it has been mounted twice.
  umount("/proc");
  umount("/proc");
  //mount proc,sys and dev.
  mount("proc","/proc","proc",MS_NOSUID|MS_NOEXEC|MS_NODEV,NULL);
  //For /sys,we make it read-only.
  mount("sysfs","/sys","sysfs",MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_RDONLY,NULL);
  mount("tmpfs","/dev","tmpfs",MS_NOSUID,"size=65536k,mode=755");
  //Continue mounting some other directories in /dev.
  mkdir("/dev/pts", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("devpts","/dev/pts","devpts",0,"gid=4,mode=620");
  mkdir("/dev/shm", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("tmpfs","/dev/shm","tmpfs",MS_NOSUID|MS_NOEXEC|MS_NODEV,"mode=1777");
  mkdir("/dev/mqune", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("mqune","/dev/mqune","mqune",0,NULL);
  //Protect some system runtime directories.
  mount("/proc/bus","/proc/bus","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/fs","/proc/fs","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/irq","/proc/irq","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/sys","/proc/sys","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/asound","/proc/asound","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/scsi","/proc/scsi","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/sys/firmware","/sys/firmware","sysfs",MS_BIND|MS_RDONLY,NULL);
  //For making dev nodes
  int dev;
  //Create system runtime nodes in /dev and then fix permissions.
  dev=makedev(1,3);
  mknod("/dev/null",S_IFCHR,dev);
  chmod("/dev/null", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(5,1);
  mknod("/dev/console", S_IFCHR, dev);
  chown("/dev/console", 0, 5);
  chmod("/dev/console", S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH);
  dev=makedev(1,5);
  mknod("/dev/zero",S_IFCHR,dev);
  chmod("/dev/zero", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(5,2);
  mknod("/dev/ptmx",S_IFCHR,dev);
  chown("/dev/ptmx", 0, 5);
  chmod("/dev/ptmx", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(5,0);
  mknod("/dev/tty",S_IFCHR,dev);
  chown("/dev/tty", 0, 5);
  chmod("/dev/tty", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(1,8);
  mknod("/dev/random",S_IFCHR,dev);
  chmod("/dev/random", S_IRUSR|S_IRGRP|S_IROTH);
  dev=makedev(1,9);
  mknod("/dev/urandom",S_IFCHR,dev);
  chmod("/dev/urandom", S_IRUSR|S_IRGRP|S_IROTH);
  mkdir("/dev/net", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  dev=makedev(10,200);
  mknod("/dev/net/tun",S_IFCHR,dev);
  //Create some system runtime link files in /dev.
  symlink("/proc/self/fd", "/dev/fd");
  symlink("/proc/self/fd/0", "/dev/stdin");
  symlink("/proc/self/fd/1", "/dev/stdout");
  symlink("/proc/self/fd/2", "/dev/stderr");
  symlink("/dev/null", "/dev/tty0");
  //Lower permissions by dropping caps.
  if (DROP_CAPS==1){
    //Caps to drop from docker default containers.
    if(DROP_CAP_SYS_ADMIN==1){
      cap_drop_bound(CAP_SYS_ADMIN);
    }
    if(DROP_CAP_SYS_MODULE==1){
      cap_drop_bound(CAP_SYS_MODULE);
    }
    if(DROP_CAP_SYS_RAWIO==1){
      cap_drop_bound(CAP_SYS_RAWIO);
    }
    if(DROP_CAP_SYS_PACCT==1){
      cap_drop_bound(CAP_SYS_PACCT);
    }
    if(DROP_CAP_SYS_NICE==1){
      cap_drop_bound(CAP_SYS_NICE);
    }
    if(DROP_CAP_SYS_RESOURCE==1){
      cap_drop_bound(CAP_SYS_RESOURCE);
    }
    if(DROP_CAP_SYS_TTY_CONFIG==1){
      cap_drop_bound(CAP_SYS_TTY_CONFIG);
    }
    if(DROP_CAP_AUDIT_CONTROL==1){
      cap_drop_bound(CAP_AUDIT_CONTROL);
    }
    if(DROP_CAP_MAC_OVERRIDE==1){
      cap_drop_bound(CAP_MAC_OVERRIDE);
    }
    if(DROP_CAP_MAC_ADMIN==1){
      cap_drop_bound(CAP_MAC_ADMIN);
    }
    if(DROP_CAP_NET_ADMIN==1){
      cap_drop_bound(CAP_NET_ADMIN);
    }
    if(DROP_CAP_SYSLOG==1){
      cap_drop_bound(CAP_SYSLOG);
    }
    if(DROP_CAP_DAC_READ_SEARCH==1){
      cap_drop_bound(CAP_DAC_READ_SEARCH);
    }
    if(DROP_CAP_LINUX_IMMUTABLE==1){
      cap_drop_bound(CAP_LINUX_IMMUTABLE);
    }
    if(DROP_CAP_NET_BROADCAST==1){
      cap_drop_bound(CAP_NET_BROADCAST);
    }
    if(DROP_CAP_IPC_LOCK==1){
      cap_drop_bound(CAP_IPC_LOCK);
    }
    if(DROP_CAP_IPC_OWNER==1){
      cap_drop_bound(CAP_IPC_OWNER);
    }
    if(DROP_CAP_SYS_PTRACE==1){
      cap_drop_bound(CAP_SYS_PTRACE);
    }
    if(DROP_CAP_SYS_BOOT==1){
      cap_drop_bound(CAP_SYS_BOOT);
    }
    if(DROP_CAP_LEASE==1){
      cap_drop_bound(CAP_LEASE);
    }
    if(DROP_CAP_WAKE_ALARM==1){
      cap_drop_bound(CAP_WAKE_ALARM);
    }
    if(DROP_CAP_BLOCK_SUSPEND==1){
      cap_drop_bound(CAP_BLOCK_SUSPEND);
    }
  }
  if(DROP_MORE_CAPS==1){
    //In docker,these caps will be kept.
    //Dropping these caps is usually not necessary.
    if(DROP_CAP_SYS_CHROOT==1){
      cap_drop_bound(CAP_SYS_CHROOT);
    }
    if(DROP_CAP_SETPCAP==1){
      cap_drop_bound(CAP_SETPCAP);
    }
    if(DROP_CAP_MKNOD==1){
      cap_drop_bound(CAP_MKNOD);
    }
    if(DROP_CAP_AUDIT_WRITE==1){
      cap_drop_bound(CAP_AUDIT_WRITE);
    }
    if(DROP_CAP_CHOWN==1){
      cap_drop_bound(CAP_CHOWN);
    }
    if(DROP_CAP_NET_RAW==1){
      cap_drop_bound(CAP_NET_RAW);
    }
    if(DROP_CAP_DAC_OVERRIDE==1){
      cap_drop_bound(CAP_DAC_OVERRIDE);
    }
    if(DROP_CAP_FOWNER==1){
      cap_drop_bound(CAP_FOWNER);
    }
    if(DROP_CAP_FSETID==1){
      cap_drop_bound(CAP_FSETID);
    }
    if(DROP_CAP_KILL==1){
      cap_drop_bound(CAP_KILL);
    }
    if(DROP_CAP_SETGID==1){
      cap_drop_bound(CAP_SETGID);
    }
    if(DROP_CAP_NET_BIND_SERVICE==1){
      cap_drop_bound(CAP_NET_BIND_SERVICE);
    }
    if(DROP_CAP_SETFCAP==1){
      cap_drop_bound(CAP_SETFCAP);
    }
  }
  //Login to container.
  //Use exec() family function because system() is unavailable now.
  char *login[]={"/bin/su","-",NULL};
  execv(login[0],login);
}
//main() starts here.
int main(int argc,char **argv){
  if (argc==1){
    printf("Chroot directory not set");
    exit(0);
  }
  //Unset $LD_PRELOAD to run binaries in container.
  unsetenv("LD_PRELOAD");
  //Check if we are running with root permissions.
  if (getuid()!=0){
    //exec() is more powerful than system(),isn't that?
    char *privilege[]={"sudo",BINARY_PATH,argv[1],NULL};
    execvp(privilege[0],privilege);
    //We should exit here to avoid running the following part without root permissions.
    exit(0);
  }
  if (USE_UNSHARE==1){
    //Try to create namespaces with unshare().
    if(unshare(CLONE_NEWNS) == -1){
      printf("Seems that mount namespace is not supported on this device\n");
    }
    if(unshare(CLONE_NEWUTS) == -1){
      printf("Seems that uts namespace is not supported on this device\n");
    }
    if(unshare(CLONE_NEWIPC) == -1){
      printf("Seems that ipc namespace is not supported on this device\n");
    }
    if(unshare(CLONE_NEWPID) == -1){
      printf("Seems that pid namespace is not supported in this host\n");
    }
    if(unshare(CLONE_FILES) == -1){
      printf("Seems that we could not unshare fds\n");
    }
    if(unshare(CLONE_FS) == -1){
      printf("Seems that we could not unshare filesystem information.\n");
    }
    //Fork itself into namespace.
    //This can fix 'can't fork: out of memory` issue.
    int pid=fork();
    //Run container in the forked process.
    if (pid==0) {
      chroot_container(argv[1]);
    }
    //Fix `can't access tty` issue.
    waitpid(pid, NULL, 0);
  }else{
    chroot_container(argv[1]);
  }
  return 0;
}
// ██╗ ██╗  ███████╗   ████╗   ███████╗
//████████╗ ██╔════╝ ██╔═══██╗ ██╔════╝
//╚██╔═██╔╝ █████╗   ██║   ██║ █████╗
//████████╗ ██╔══╝   ██║   ██║ ██╔══╝
//╚██╔═██╔╝ ███████╗ ╚██████╔╝ ██║
// ╚═╝ ╚═╝  ╚══════╝  ╚═════╝  ╚═╝