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
// Connect to daemon.
bool connect_to_daemon(struct sockaddr_un *addr)
{
  /*
   * Set socket address and check if daemon is running.
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