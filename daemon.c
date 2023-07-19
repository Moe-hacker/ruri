#include "ruri.h"
void container_daemon()
{
  /*
   * 100% shit code at container_daemon.
   * If the code is hard to write,
   * it should be hard to read.
   */
  /*
   *
   * TODO(Moe-hacker):
   * 遵守caplist mountpoint env
   *
   */
  // Set process name.
  prctl(PR_SET_NAME, "rurid");
  // Ignore SIGTTIN, if running in the background, SIGTTIN may kill it.
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
  // Set default value.
  // Message to read.
  char *msg = NULL;
  // Container info.
  char *container_dir = NULL;
  // Info of a new container.
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
  pid_t unshare_pid = 0;
  char *drop_caplist[CAP_LAST_CAP + 1] = {NULL};
  char *env[MAX_ENVS] = {NULL};
  char *mountpoint[MAX_MOUNTPOINTS] = {NULL};
  // Create socket
  int sockfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
  if (sockfd < 0)
  {
    error("Error: cannot create socket QwQ");
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
  // Create socket file
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
    if (msg == NULL)
    {
      goto _continue;
    }
    // Test message.
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
      if (container_active(container_dir, container))
      {
        unshare_pid = atoi(read_node(container_dir, container)->unshare_pid);
        kill(unshare_pid, SIGKILL);
        container = del_container(container_dir, container);
        send_msg_daemon(FROM_DAEMON__CONTAINER_KILLED, addr, sockfd);
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
      if (container_active(container_dir, container))
      {
        send_msg_daemon(FROM_DAEMON__UNSHARE_CONTAINER_PID, addr, sockfd);
        send_msg_daemon(read_node(container_dir, container)->unshare_pid, addr, sockfd);
        goto _continue;
      }
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
        for (int i = 0;;)
        {
          msg = read_msg_daemon(addr, sockfd);
          if (msg == NULL)
          {
            goto _continue;
          }
          if (strcmp(FROM_CLIENT__END_OF_CAP_TO_DROP, msg) == 0)
          {
            free(msg);
            msg = NULL;
            break;
          }
          cap_from_name(msg, &container_info.drop_caplist[i]);
          free(msg);
          msg = NULL;
          i++;
        }
        container_info.container_dir = strdup(container_dir);
        free(container_dir);
        pthread_create(&pthread_id, NULL, daemon_init_unshare_container, (void *)&container_info);
        goto _continue;
      }
      goto _continue;
    }
    // Get container info from subprocess and add them to container struct.
    else if (strcmp(FROM_PTHREAD__UNSHARE_CONTAINER_PID, msg) == 0)
    {
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_info.unshare_pid = strdup(msg);
      free(msg);
      msg = NULL;
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      container_info.container_dir = strdup(msg);
      if (msg == NULL)
      {
        goto _continue;
      }
      msg = read_msg_daemon(addr, sockfd);
      if (msg == NULL)
      {
        goto _continue;
      }
      for (int i = 0;;)
      {
        msg = read_msg_daemon(addr, sockfd);
        if (msg == NULL)
        {
          goto _continue;
        }
        if (strcmp(FROM_PTHREAD__END_OF_CAP_TO_DROP, msg) == 0)
        {
          free(msg);
          msg = NULL;
          break;
        }
        drop_caplist[i] = strdup(msg);
        drop_caplist[i + 1] = NULL;
        free(msg);
        msg = NULL;
        i++;
      }
      // TODO(Moe-hacker)
      container = add_node(container_info.container_dir, container_info.unshare_pid, drop_caplist, env, mountpoint, container);
      // Send ${unshare_pid} to ruri.
      send_msg_daemon(container_info.unshare_pid, addr, sockfd);
      container_info.container_dir = NULL;
      container_info.init_command[0] = NULL;
      container_info.unshare_pid = NULL;
      for (int i = 0; i < (CAP_LAST_CAP + 1); i++)
      {
        container_info.drop_caplist[i] = INIT_VALUE;
      }
      goto _continue;
    }
    // Kill daemon itself.
    else if (strcmp(FROM_CLIENT__KILL_DAEMON, msg) == 0)
    {
      free(msg);
      msg = NULL;
      umount_all_containers(container);
      // It will exit at main()
      exit(EXIT_SUCCESS);
    }
    // Get info of all registered containers.
    else if (strcmp(FROM_CLIENT__GET_PS_INFO, msg) == 0)
    {
      free(msg);
      msg = NULL;
      read_all_nodes(container, addr, sockfd);
      goto _continue;
    }
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
    // Jump to the next loop.
  _continue:
    continue;
  }
}