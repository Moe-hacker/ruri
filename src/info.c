// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2024 Moe-hacker
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
#include "include/ruri.h"
// As an easter egg.
void AwA(void)
{
	/*
	 * Nothing is useful at this function, just for fun.
	 */
	// Get the size of terminal.
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	u_short col = size.ws_col;
	if (col % 2 == 1) {
		col -= 1;
	}
	// For centering output.
	char space[col / 2 + 1];
	space[0] = '\0';
	if (col > 60) {
		col /= 2;
		col -= 28;
		memset(space, ' ', col * sizeof(char));
		space[col] = '\0';
	} else {
		strcat(space, "");
	}
	printf("%s%s\n", space, "\033[1;38;2;255;255;255m              ██                        ██");
	printf("%s%s\n", space, "            ██  ██          ██        ██  ██");
	printf("%s%s\n", space, "            ██    ████        ██    ██      ██");
	printf("%s%s\n", space, "          ██          ██    ██    ████      ██");
	printf("%s%s\n", space, "          ██      ██████████████████          ██");
	printf("%s%s\n", space, "        ██      ██                  ██        ██");
	printf("%s%s\n", space, "        ██    ██                      ████    ██");
	printf("%s%s\n", space, "      ████████        ██      ██          ████  ██");
	printf("%s%s\n", space, "      ██    ██        ██    ██  ██    ██    ██  ██");
	printf("%s%s\n", space, "    ████      ██    ██  ████  ██    ██  ██    ██████");
	printf("%s%s\n", space, "    ██        ██  ██    ██      ████  ██  ██  ████████");
	printf("%s%s\n", space, "    ██      ██  ██                          ████");
	printf("%s%s\n", space, "    ██        ██                    ██████    ██");
	printf("%s%s\n", space, "  ████        ██    ████          ██      ██  ██");
	printf("%s%s\n", space, "  ██          ██        ██          \033[1;38;2;255;0;0m██  ██\033[1;38;2;255;255;255m    ██");
	printf("%s%s\n", space, "  ██          ██          ██          \033[1;38;2;255;0;0m██\033[1;38;2;255;255;255m      ██");
	printf("%s%s\n", space, "  ██          ██    ██████          \033[1;38;2;255;0;0m██  ██\033[1;38;2;255;255;255m      ██");
	printf("%s%s\n", space, "  ████    ██  ██                                ██");
	printf("%s%s\n", space, "    ████  ██████          ██    ██            ██");
	printf("%s%s\n", space, "      ██████  ████          ████          ████");
	printf("%s%s\n", space, "                ████                    ████");
	printf("%s%s\n", space, "                    ████████████████████");
	printf("%s\n", "");
}
// For `ruri -v`.
void show_version_info(void)
{
	/*
	 * Just show version info and license.
	 * Version info is defined in macro RURI_VERSION.
	 * RURI_COMMIT_ID is defined in Makefile.
	 */
	printf("\n");
	printf("\033[1;38;2;254;228;208m      ●●●●  ●   ● ●●●●   ●●●\n");
	printf("      ●   ● ●   ● ●   ●   ●\n");
	printf("      ●●●●  ●   ● ●●●●    ●\n");
	printf("      ●  ●  ●   ● ●  ●    ●\n");
	printf("      ●   ●  ●●●  ●   ●  ●●●\n");
	printf("  Licensed under the MIT License\n");
	printf("    <https://mit-license.org>\n");
	printf("Copyright (C) 2022-2024 Moe-hacker\n");
	printf("%s%s%s", "ruri version     :    ", RURI_VERSION, "\n");
	printf("%s%s%s", "Commit id        :    ", RURI_COMMIT_ID, "\n");
	printf("%s%s\n", "Compiler version :    ", __VERSION__);
	printf("%s%s\n", "Build date       :    ", __TIMESTAMP__);
	printf("\033[0m\n");
}
// For `ruri -V`.
void show_version_code(void)
{
	/*
	 * The version code is not standard now,
	 * so in fact it's very useless.
	 * Maybe it can be useful one day...
	 */
	printf("%s\n", RURI_VERSION);
}
// For `ruri -h`.
void show_helps(void)
{
	/*
	 * Help page of ruri.
	 * I think you can understand...
	 */
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
	printf("  -H                     Show helps and commandline examples\n");
	printf("  -D                     Run daemon\n");
	printf("  -K                     Kill daemon\n");
	printf("  -t                     Check if daemon is running\n");
	printf("  -T                     Check if daemon is running (No output)\n");
	printf("  -l                     List all running unshare containers\n");
	printf("  -U [container_dir]     Umount&kill a container\n");
	printf("\n");
	printf("ARGS:\n");
	printf("  -a [arch]              Simulate architecture via binfmt_misc & QEMU, need `-q`\n");
	printf("  -q [path]              Specify the path of QEMU\n");
	printf("  -u                     Enable unshare feature\n");
	printf("  -n                     Set NO_NEW_PRIVS Flag\n");
	printf("  -s                     Enable built-in Seccomp profile\n");
	printf("  -d                     Drop more capabilities for lower privilege\n");
	printf("  -p                     Run privileged container\n");
	printf("  -r                     Run rootless container\n");
	printf(" --keep [cap]            Keep the specified cap\n");
	printf(" --drop [cap]            Drop the specified cap\n");
	printf("  -e [env] [value]       Set env to its value *Not work if init command is like `su -`\n");
	printf("  -m [dir/dev/img] [dir] Mount dir/block-device/image to mountpoint\n");
	printf("  -S                     Bind-mount /dev/, /sys/ and /proc/ from host\n");
	printf("  -w                     Disable warnings\n");
	printf("\n");
	printf("Default command to run is `/bin/su` if it's not set\n");
	printf("The path of qemu is the absolute path of qemu binary in the chroot container\n");
	printf("This program should be run with root privileges\n");
	printf("Please unset $LD_PRELOAD before running this program\n");
	printf("For a full user guide, see `man ruri`\033[0m\n");
	printf("\n");
}
// For `ruri -H`.
void show_examples(void)
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
