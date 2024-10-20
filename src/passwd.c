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
char *line_get_username(char *p)
{
	char *ret = malloc(128);
	for (int i = 0;; i++) {
		if (p[i] == ':') {
			break;
		}
		ret[i] = p[i];
		ret[i + 1] = '\0';
	}
	return ret;
}
uid_t line_get_uid(char *p)
{
	uid_t ret = 0;
	int j = 0;
	for (int i = 0;; i++) {
		if (p[i] == ':') {
			j++;
			if (j == 3) {
				for (int k = i + 1;; k++) {
					if (p[k] == ':') {
						return ret;
					}
					ret = ret * 10 + (uid_t)(p[k] - '0');
				}
			}
		}
	}
}
char *get_username(uid_t uid)
{
	/*
	 * Get username by uid.
	 */
	int fd = open("/etc/passwd", O_RDONLY | O_CLOEXEC);
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = malloc((size_t)size + 1);
	read(fd, buf, (size_t)size);
	buf[size] = '\0';
	close(fd);
	char *p = buf;
	uid_t tmpuid;
	char *tmpusername;
	while (true) {
		tmpusername = line_get_username(p);
		tmpuid = line_get_uid(p);
		if (tmpuid == uid) {
			free(buf);
			return tmpusername;
		}
		free(tmpusername);
		p = strchr(p, '\n');
		if (p == NULL) {
			break;
		}
		p = p + 1;
	}
	free(buf);
	return NULL;
}