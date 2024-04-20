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
#include "include/cprintf.h"
#if __STDC_VERSION__ < 202000L
#define bool _Bool
#define true ((_Bool) + 1u)
#define false ((_Bool) + 0u)
#endif
static void print_rgb_color(const char *color)
{
	char buf[17];
	for (size_t i = 1; i < strlen(color) - 1; i++) {
		buf[i - 1] = color[i];
		buf[i] = 0;
	}
	printf("\033[1;38;2;%sm", buf);
}
static void fprint_rgb_color(FILE *stream, const char *color)
{
	char buf[17];
	for (size_t i = 1; i < strlen(color) - 1; i++) {
		buf[i - 1] = color[i];
		buf[i] = 0;
	}
	fprintf(stream, "\033[1;38;2;%sm", buf);
}
static bool is_rgb_color(const char *color)
{
	int sem = 0;
	if (atoi(color) > 255) {
		return false;
	}
	for (size_t i = 1; i < strlen(color) - 1; i++) {
		if (color[i] == ';') {
			sem++;
			if (atoi(&color[i + 1]) > 255) {
				return false;
			}
		}
		if (sem > 2) {
			return false;
		}
		if (!isdigit(color[i]) && color[i] != ';') {
			return false;
		}
	}
	if (sem != 2) {
		return false;
	}
	return true;
}
static const char *cfprintf_print_color(FILE *stream, const char *buf)
{
	/*
	 * Only valid {color} will be recognized,
	 * and for other '{' without 'color}', we print a '{'.
	 * we return the pointer to the last character that is
	 * not recognized as color.
	 */
	const char *ret = buf;
	char color[17] = { '\0' };
	for (int i = 0; i < 16; i++) {
		if (buf[i] == '}') {
			color[i] = buf[i];
			color[i + 1] = 0;
			ret = &(buf[i]);
			break;
		}
		color[i] = buf[i];
		color[i + 1] = 0;
	}
	if (strcmp(color, "{clear}") == 0) {
		fprintf(stream, "\033[0m");
	} else if (strcmp(color, "{black}") == 0) {
		fprintf(stream, "\033[30m");
	} else if (strcmp(color, "{red}") == 0) {
		fprintf(stream, "\033[31m");
	} else if (strcmp(color, "{green}") == 0) {
		fprintf(stream, "\033[32m");
	} else if (strcmp(color, "{yellow}") == 0) {
		fprintf(stream, "\033[33m");
	} else if (strcmp(color, "{blue}") == 0) {
		fprintf(stream, "\033[34m");
	} else if (strcmp(color, "{purple}") == 0) {
		fprintf(stream, "\033[35m");
	} else if (strcmp(color, "{cyan}") == 0) {
		fprintf(stream, "\033[36m");
	} else if (strcmp(color, "{white}") == 0) {
		fprintf(stream, "\033[37m");
	} else if (strcmp(color, "{base}") == 0) {
		fprintf(stream, CPRINTF_BASE_COLOR);
	} else if (is_rgb_color(color)) {
		fprint_rgb_color(stream, color);
	} else {
		ret = buf;
		fprintf(stream, "{");
	}
	return ret;
}
static const char *cprintf_print_color(const char *buf)
{
	/*
	 * Only valid {color} will be recognized,
	 * and for other '{' without 'color}', we print a '{'.
	 * we return the pointer to the last character that is
	 * not recognized as color.
	 */
	const char *ret = buf;
	char color[17] = { '\0' };
	for (int i = 0; i < 16; i++) {
		if (buf[i] == '}') {
			color[i] = buf[i];
			color[i + 1] = 0;
			ret = &(buf[i]);
			break;
		}
		color[i] = buf[i];
		color[i + 1] = 0;
	}
	if (strcmp(color, "{clear}") == 0) {
		printf("\033[0m");
	} else if (strcmp(color, "{black}") == 0) {
		printf("\033[30m");
	} else if (strcmp(color, "{red}") == 0) {
		printf("\033[31m");
	} else if (strcmp(color, "{green}") == 0) {
		printf("\033[32m");
	} else if (strcmp(color, "{yellow}") == 0) {
		printf("\033[33m");
	} else if (strcmp(color, "{blue}") == 0) {
		printf("\033[34m");
	} else if (strcmp(color, "{purple}") == 0) {
		printf("\033[35m");
	} else if (strcmp(color, "{cyan}") == 0) {
		printf("\033[36m");
	} else if (strcmp(color, "{white}") == 0) {
		printf("\033[37m");
	} else if (strcmp(color, "{base}") == 0) {
		printf(CPRINTF_BASE_COLOR);
	} else if (is_rgb_color(color)) {
		print_rgb_color(color);
	} else {
		ret = buf;
		printf("{");
	}
	return ret;
}
void __cprintf(const char *buf)
{
	const char *p = NULL;
	p = buf;
	for (size_t i = 0; i < strlen(buf); i++) {
		// Search for '{'.
		if (*p == '{') {
			// *p will be moved because we need to skip the {color} string.
			p = cprintf_print_color(p);
		} else {
			printf("%c", *p);
		}
		// Recompute the value of i.
		i = (size_t)(p - buf);
		// Goto the next charactor.
		p = &(p[1]);
	}
	// We will always reset the color in the end.
	printf("\033[0m");
}
void __cfprintf(FILE *stream, const char *buf)
{
	const char *p = NULL;
	p = buf;
	for (size_t i = 0; i < strlen(buf); i++) {
		// Search for '{'.
		if (*p == '{') {
			// *p will be moved because we need to skip the {color} string.
			p = cfprintf_print_color(stream, p);
		} else {
			fprintf(stream, "%c", *p);
		}
		// Recompute the value of i.
		i = (size_t)(p - buf);
		// Goto the next charactor.
		p = &(p[1]);
	}
	// We will always reset the color in the end.
	fprintf(stream, "\033[0m");
}
size_t cprintf_get_bufsize(const char *format, ...)
{
	/*
	 * Get the size we need to malloc() for the string buffer.
	 * Note that it will give more extra size to avoid buffer overflow.
	 */
	va_list ap;
	va_start(ap, format);
	size_t ret = 0;
	char *buf = NULL;
	ret += strlen(format);
	for (size_t i = 0; i < strlen(format); i++) {
		if (format[i] == '%') {
			i++;
			buf = va_arg(ap, char *);
			switch (format[i]) {
			case 's': {
				// For string, we get the lenth of it.
				ret += strlen(buf);
			}
			default: {
				// For other format, we use a 114 byte buffer.
				// If we don't know the number, just use homo way!
				ret += 114;
			}
			}
		}
	}
	// The homo way to avoid buffer overflow.
	return ret + 514;
}
