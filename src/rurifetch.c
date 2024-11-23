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
/*
 * A neofetch-like program for ruri.
 * Nothing useful, just for fun.
 */
static void __ruri_fetch(char **logo, char **info)
{
	int j = 0;
	for (int i = 0; logo[i] != NULL; i++) {
		j = i - 1;
		if (j >= 0 && info[j] != NULL) {
			cprintf("%s%s\n", logo[i], info[j]);
			j++;
		} else {
			cprintf("%s\n", logo[i]);
		}
	}
}
void ruri_fetch(void)
{
	char *ruri_logo[24] = { NULL };
	// clang-format off
	ruri_logo[0]  = "{base}                _-###-_                ";
	ruri_logo[1]  = "{base}             _##  ***  ##_             ";
	ruri_logo[2]  = "{base}          _##    * * *    ##_          ";
	ruri_logo[3]  = "{base}       ###       * * *       ###       ";
	ruri_logo[4]  = "{base}     ##          * * *          ##     ";
	ruri_logo[5]  = "{base}   #**** _       * * *       _ ****#   ";
	ruri_logo[6]  = "{base}   # * *_ **__   * * *   __**_ * * #   ";
	ruri_logo[7]  = "{base}   #   * _**_ *_ * * * _* _**_ *   #   ";
	ruri_logo[8]  = "{base}   #      **_*  * *** *  *_**      #   ";
	ruri_logo[9]  = "{base}   #          ****+++****          #   ";
	ruri_logo[10] = "{base}   #      **`*  * *** *  *`**      #   ";
	ruri_logo[11] = "{base}   #   * `**` *` * * * `* `**` *   #   ";
	ruri_logo[12] = "{base}   # * *` **``   * * *   ``**` * * #   ";
	ruri_logo[13] = "{base}   #**** `       * * *       ` ****#   ";
	ruri_logo[14] = "{base}     ##          * * *          ##     ";
	ruri_logo[15] = "{base}       ###       * * *       ###       ";
	ruri_logo[16] = "{base}         `##     * * *     ##`         ";
	ruri_logo[17] = "{base}           `##    ***    ##`           ";
	ruri_logo[18] = "{base}              ```-###-```              ";
	ruri_logo[19] = NULL;
	// clang-format on
	char *ruri_info[24] = { NULL };
	ruri_info[0] = "{91;207;250}Moe-hacker{white}@{91;207;250}Github";
	ruri_info[1] = "{white}-----------------";
	ruri_info[2] = "{91;207;250}Project{white}: ruri";
	ruri_info[3] = "{91;207;250}License{white}: MIT";
	char version_info[128] = { '\0' };
	sprintf(version_info, "{91;207;250}Version{white}: %s", RURI_VERSION);
	ruri_info[4] = version_info;
#if !defined(RURI_COMMIT_ID)
#define RURI_COMMIT_ID "unknown"
#endif
	char commit_id[128] = { '\0' };
	sprintf(commit_id, "{91;207;250}Commit{white}: %s", RURI_COMMIT_ID);
	ruri_info[5] = commit_id;
	char host_arch[128] = { '\0' };
	sprintf(host_arch, "{91;207;250}Architecture{white}: %s", RURI_HOST_ARCH);
	ruri_info[6] = host_arch;
	struct stat st;
	char binary_size[128] = { '\0' };
	if (stat("/proc/self/exe", &st) == 0) {
		sprintf(binary_size, "{91;207;250}Binary size{white}: %ldK", (st.st_size / 1024));
	} else {
		sprintf(binary_size, "{91;207;250}Binary size{white}: unknown");
	}
	ruri_info[7] = binary_size;
	char compiler_info[128] = { '\0' };
	sprintf(compiler_info, "{91;207;250}Compiler{white}: %s", __VERSION__);
	ruri_info[8] = compiler_info;
	char build_date[128] = { '\0' };
	sprintf(build_date, "{91;207;250}Build date{white}: %s", __DATE__);
	ruri_info[9] = build_date;
	char cprintf_version[128] = { '\0' };
	sprintf(cprintf_version, "{91;207;250}cprintf{white}: %d.%d", CPRINTF_MAJOR, CPRINTF_MINOR);
	ruri_info[10] = cprintf_version;
	char libk2v_version[128] = { '\0' };
	sprintf(libk2v_version, "{91;207;250}libk2v{white}: %d.%d", LIBK2V_MAJOR, LIBK2V_MINOR);
	ruri_info[11] = libk2v_version;
#if !defined(LIBCAP_MAJOR) || !defined(LIBCAP_MINOR)
	ruri_info[12] = "{91;207;250}libcap{white}: unknown";
#else
	char libcap_version[128] = { '\0' };
	sprintf(libcap_version, "{91;207;250}libcap{white}: %d.%d", LIBCAP_MAJOR, LIBCAP_MINOR);
	ruri_info[12] = libcap_version;
#endif
#if !defined(SCMP_VER_MAJOR) || !defined(SCMP_VER_MINOR) || !defined(SCMP_VER_MICRO)
	ruri_info[13] = "{91;207;250}libseccomp{white}: unknown";
#else
	char libseccomp_version[128] = { '\0' };
	sprintf(libseccomp_version, "{91;207;250}libseccomp{white}: %d.%d.%d", SCMP_VER_MAJOR, SCMP_VER_MINOR, SCMP_VER_MICRO);
	ruri_info[13] = libseccomp_version;
#endif
	ruri_info[14] = " ";
	ruri_info[15] = "[black]   [red]   [green]   [yellow]   [blue]   [purple]   [cyan]   [white]   [clear]";
	ruri_info[16] = "\033[48;5;243m   \033[48;5;196m   \033[48;5;46m   \033[48;5;226m   \033[48;5;33m   \033[48;5;201m   \033[48;5;51m   \033[48;5;15m   \033[0m";
	ruri_info[17] = NULL;
	__ruri_fetch(ruri_logo, ruri_info);
}