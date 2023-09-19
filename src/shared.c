// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2023 Moe-hacker
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
// Show error msg and exit.
void error(char *msg)
{
  /*
   * Show error message and exit here.
   * You can never know if a customer will order a rice at the bar.
   * It's a `moe` program, but also should be standardized and rigorous.
   */
  fprintf(stderr, "\033[31m%s\033[0m\n", msg);
  // A very cute catgirl nya~~
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "  .^.   .^.");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "  /⋀\\_ﾉ_/⋀\\");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", " /ﾉｿﾉ\\ﾉｿ丶)|");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", " ﾙﾘﾘ >  x )ﾘ");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "ﾉノ㇏  ^ ﾉ|ﾉ");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "      ⠁⠁");
  fprintf(stderr, "\033[1;38;2;254;228;208m%s\033[0m\n", "If you think something is wrong, please report at:");
  fprintf(stderr, "\033[4;1;38;2;254;228;208m%s\033[0m\n", "https://github.com/Moe-hacker/ruri/issues");
  exit(1);
}
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
  // Yes, it's Hoppou!
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
   * macro RURI_COMMIT_ID is defined in Makefile.
   */
  printf("\n");
  printf("\033[1;38;2;254;228;208m      ●●●●  ●   ● ●●●●   ●●●\n");
  printf("      ●   ● ●   ● ●   ●   ●\n");
  printf("      ●●●●  ●   ● ●●●●    ●\n");
  printf("      ●  ●  ●   ● ●  ●    ●\n");
  printf("      ●   ●  ●●●  ●   ●  ●●●\n");
  printf("  Licensed under the MIT License\n");
  printf("    <https://mit-license.org>\n");
  printf("Copyright (C) 2022-2023 Moe-hacker\n");
  printf("%s%s%s", "     ruri version : ", RURI_VERSION, "\n");
  printf("%s%s%s\033[0m", "     Commit id    : ", RURI_COMMIT_ID, "\n");
  printf("\n");
}
// For `ruri -V`.
void show_version_code()
{
  printf("%s\n", RURI_VERSION);
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
  printf("\033[1;38;2;254;228;208mLightweight, User-friendly Linux-container Implementation\n");
  printf("\n");
  printf("Usage:\n");
  printf("  ruri OPTIONS\n");
  printf("  ruri [ARGS] CONTAINER_DIRECTORY [COMMAND [ARG]...]\n");
  printf("\n");
  printf("OPTIONS:\n");
  printf("  -v                     Show version info\n");
  printf("  -V                     Show version code\n");
  printf("  -h                     Show helps\n");
  printf("  -hh                    Show helps and commandline examples\n");
  printf("  -D                     Run daemon\n");
  printf("  -K                     Kill daemon\n");
  printf("  -t                     Check if daemon is running\n");
  printf("  -l                     List all running unshare containers\n");
  printf("  -U [container_dir]     Umount&kill a container\n");
  printf("\n");
  printf("ARGS:\n");
  printf("  -u                     Enable unshare feature\n");
  printf("  -n                     Set NO_NEW_PRIVS Flag\n");
  printf("  -s                     Enable Seccomp\n");
  printf("  -d                     Drop more capabilities for lower privilege\n");
  printf("  -p                     Run privileged container\n");
  printf(" --keep [cap]            Keep the specified cap\n");
  printf(" --drop [cap]            Drop the specified cap\n");
  printf("  -e [env] [value]       Set env to its value *Not work if init command is like `su -`\n");
  printf("  -m [dir] [mountpoint]  Mount dir to mountpoint\n");
  printf("  -w                     Disable warnings\n");
  printf("\n");
  printf("Default command to run is `/bin/su` if it's not given\n");
  printf("This program should be run with root privileges\n");
  printf("Please unset $LD_PRELOAD before running this program\n");
  printf("For a full user guide, see `man ruri`\033[0m\n");
  printf("\n");
}
// For `ruri -hh`.
void show_examples()
{
  /*
   * Command line examples.
   * I think you can understand...
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
  printf("#But it's recommended to start daemon before running unshare containers:\n");
  printf("  \033[32msudo ruri \033[34m-D\n");
  printf("\033[1;38;2;254;228;208m#Run unshare container:\n");
  printf("  \033[32msudo ruri \033[34m-u \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#List running containers:\n");
  printf("  \033[32msudo ruri \033[34m-l\n");
  printf("\033[1;38;2;254;228;208m#Umount the container:\n");
  printf("  \033[32msudo ruri \033[34m-U \033[35m/tmp/alpine\n");
  printf("\033[1;38;2;254;228;208m#Finally, kill the daemon:\n");
  printf("  \033[32msudo ruri \033[34m-K\n");
  printf("\n");
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