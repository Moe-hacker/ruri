// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of cprintf, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2024 Moe-hacker
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
#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#ifndef _Nullable
#define _Nullable
#endif
#ifndef _Nonnull
#define _Nonnull
#endif
void __cprintf(const char *_Nonnull buf);
void __cfprintf(FILE *_Nonnull stream, const char *_Nonnull buf);
// Get the size of the string to print.
// We give another 514 bytes to avoid buffer overflow.
// We call snprintf() twice, but never mind, it's fast enough.
#define cprintf_get_bufsize(format, ...) (snprintf(NULL, 0, format, ##__VA_ARGS__) > 0 ? (size_t)snprintf(NULL, 0, format, ##__VA_ARGS__) + 514 : 0)
// The `base` color.
extern char *cprintf_base_color;
/*
 * cprintf() is a macro,
 * first, we get the size of the string to print,
 * we use sprintf() to write it to buf[],
 * so that we only need to parse the string in buf[].
 */
#define cprintf(format, ...)                                                 \
	{                                                                    \
		char *__cprintf_buf = NULL;                                  \
		size_t bufsize = cprintf_get_bufsize(format, ##__VA_ARGS__); \
		if (bufsize != 0) {                                          \
			__cprintf_buf = malloc(bufsize);                     \
			sprintf(__cprintf_buf, format, ##__VA_ARGS__);       \
			__cprintf(__cprintf_buf);                            \
			free(__cprintf_buf);                                 \
		}                                                            \
	}
#define cfprintf(stream, format, ...)                                        \
	{                                                                    \
		char *__cprintf_buf = NULL;                                  \
		size_t bufsize = cprintf_get_bufsize(format, ##__VA_ARGS__); \
		if (bufsize != 0) {                                          \
			__cprintf_buf = malloc(bufsize);                     \
			sprintf(__cprintf_buf, format, ##__VA_ARGS__);       \
			__cfprintf(stream, __cprintf_buf);                   \
			free(__cprintf_buf);                                 \
		}                                                            \
	}
#define CPRINTF_MAJOR 1
#define CPRINTF_MINOR 4
