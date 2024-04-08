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
// See https://stackoverflow.com/questions/55641889/access-build-id-at-runtime
extern char build_id_start;
extern char build_id_end;
static char *get_build_id(void)
{
	/*
	 * Just like its name.
	 */
	static char ret[128] = { '\0' };
	char buf[4] = { '\0' };
	for (char *s = &build_id_start + 16; s < &build_id_end; s++) {
		sprintf(buf, "%x", *s);
		strcat(ret, buf);
	}
	return ret;
}
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
	printf("%s%s%s", "ruri version .....:  ", RURI_VERSION, "\n");
	printf("%s%s%s", "Commit id ........:  ", RURI_COMMIT_ID, "\n");
	printf("%s%d%s%d%s", "libcap ...........:  ", LIBCAP_MAJOR, ".", LIBCAP_MINOR, "\n");
	printf("%s%d%s%d%s%d%s", "libseccomp .......:  ", SCMP_VER_MAJOR, ".", SCMP_VER_MINOR, ".", SCMP_VER_MICRO, "\n");
	printf("%s%d%s%d%s", "libk2v ...........:  ", LIBK2V_MAJOR, ".", LIBK2V_MINOR, "\n");
	printf("%s%s\n", "Compiler version .:  ", __VERSION__);
	printf("%s%s\n", "Build date .......:  ", __TIMESTAMP__);
	printf("%s%s\n", "Build ID .........:  ", get_build_id());
	printf("\nThere is NO WARRANTY, to the extent permitted by law\n");
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
	printf("\033[1;38;2;254;228;208mruri %s %s\n\n", RURI_VERSION, RURI_COMMIT_ID);
	printf("Lightweight, User-friendly Linux-container Implementation\n");
	printf("\n");
	printf("Usage:\n");
	printf("  ruri [OPTIONS]...\n");
	printf("  ruri [ARGS]... [CONTAINER_DIRECTORY]... [COMMAND [ARGS]...]\n");
	printf("\n");
	printf("OPTIONS:\n");
	printf("  -v, --version ...................: Show version info\n");
	printf("  -V, --version-code ..............: Show version code\n");
	printf("  -h, --help ......................: Show helps\n");
	printf("  -H, --show-examples .............: Show helps and commandline examples\n");
	printf("  -U, --umount [container_dir] ....: Umount a container\n");
	printf("\n");
	printf("ARGS:\n");
	printf("  -D, --dump-config ...............: Dump the config.\n");
	printf("  -o, --output [config file] ......: Set output file of `-D` option\n");
	printf("  -c, --config [config file] ......: Use config file\n");
	printf("  -a, --arch [arch] ...............: Simulate architecture via binfmt_misc (*)\n");
	printf("  -q, --qemu-path [path] ..........: Specify the path of QEMU\n");
	printf("  -u, --unshare ...................: Enable unshare feature\n");
	printf("  -n, --no-new-privs ..............: Set NO_NEW_PRIVS Flag\n");
	printf("  -N, --no-rurienv ................: Do not use .rurienv file\n");
	printf("  -s, --enable-seccomp ............: Enable built-in Seccomp profile\n");
	printf("  -p, --privileged ................: Run privileged container\n");
	printf("  -r, --rootless ..................: Run rootless container\n");
	printf("  -k, --keep [cap] ................: Keep the specified cap\n");
	printf("  -d, --drop [cap] ................: Drop the specified cap\n");
	printf("  -e, --env [env] [value] .........: Set environment variables to its value (**)\n");
	printf("  -m, --mount [dir/dev/img] [dir] .: Mount dir/block-device/image to mountpoint\n");
	printf("  -M, --ro-mount [dir/dev/img] [dir] Mount dir/block-device/image as read-only\n");
	printf("  -S, --host-runtime ..............: Bind-mount /dev/, /sys/ and /proc/ from host\n");
	printf("  -R, --read-only .................: Mount / as read-only\n");
	printf("  -w, --no-warnings ...............: Disable warnings\n");
	printf("\n");
	printf("(*) :  `-a` option also need `-q` is set\n");
	printf("(**): Will not work if [COMMAND [ARGS]...] is like `/bin/su -`\n");
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
	printf("\033[1;38;2;254;228;208m# Quickly setup a container(with rootfstool):\n");
	printf("  \033[32mgit \033[33mclone \033[35mhttps://github.com/Moe-hacker/rootfstool\n");
	printf("  \033[32mcd \033[35mrootfstool\n");
	printf("  \033[32m./rootfstool \033[33mdownload \033[34m-d \033[35malpine \033[34m-v \033[35medge\n");
	printf("  \033[32mmkdir \033[35m/tmp/alpine\n");
	printf("  \033[32msudo tar \033[34m-xvf \033[35mrootfs.tar.xz \033[34m-C \033[35m/tmp/alpine\n");
	printf("\033[1;38;2;254;228;208m# Run chroot container:\n");
	printf("  \033[32msudo ruri \033[35m/tmp/alpine\n");
	printf("\033[1;38;2;254;228;208m# Very simple as you can see.\n");
	printf("# About the capabilities:\n");
	printf("# Run privileged chroot container:\n");
	printf("  \033[32msudo ruri \033[34m-p \033[35m/tmp/alpine\n");
	printf("\033[1;38;2;254;228;208m# If you want to run privileged chroot container,\n");
	printf("# but you don't want to give the container cap_sys_chroot privileges:\n");
	printf("  \033[32msudo ruri \033[34m-p -d \033[36mcap_sys_chroot \033[35m/tmp/alpine\n");
	printf("\033[1;38;2;254;228;208m# If you want to run chroot container with common privileges,\n");
	printf("# but you want cap_sys_admin to be kept:\n");
	printf("  \033[32msudo ruri \033[34m-k \033[36mcap_sys_admin \033[35m/tmp/alpine\n");
	printf("\033[1;38;2;254;228;208m# About unshare:\n");
	printf("# Unshare container's capability options are same with chroot.\n");
	printf("\033[1;38;2;254;228;208m# Run unshare container:\n");
	printf("  \033[32msudo ruri \033[34m-u \033[35m/tmp/alpine\n");
	printf("\033[1;38;2;254;228;208m# Umount the container:\n");
	printf("  \033[32msudo ruri \033[34m-U \033[35m/tmp/alpine\n");
	printf("\n");
}
