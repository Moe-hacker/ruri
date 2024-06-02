// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of libk2v, with ABSOLUTELY NO WARRANTY.
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
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
// Bool!!!
#if __STDC_VERSION__ < 202000L
#ifndef bool
#define bool _Bool
#define true ((_Bool) + 1u)
#define false ((_Bool) + 0u)
#endif
#endif
// Version info.
#define LIBK2V_MAJOR 1
#define LIBK2V_MINOR 0
// Warning.
extern bool k2v_stop_at_warning;
extern bool k2v_show_warning;
// Functions.
char *key_get_char(const char *key, const char *buf);
int key_get_int(const char *key, const char *buf);
float key_get_float(const char *key, const char *buf);
bool key_get_bool(const char *key, const char *buf);
int key_get_int_array(const char *key, const char *buf, int *array);
int key_get_char_array(const char *key, const char *buf, char *array[]);
int key_get_float_array(const char *key, const char *buf, float *array);
bool have_key(const char *key, const char *buf);
char *k2v_open_file(const char *path, size_t bufsize);
void k2v_to_shell(const char *buf);
char *char_to_k2v(const char *key, const char *val);
char *int_to_k2v(const char *key, int val);
char *bool_to_k2v(const char *key, bool val);
char *float_to_k2v(const char *key, float val);
char *char_array_to_k2v(const char *key, char *const *val, int len);
char *int_array_to_k2v(const char *key, int *val, int len);
char *float_array_to_k2v(const char *key, float *val, int len);
size_t k2v_get_filesize(const char *path);
#define k2v_add_config(type, __k2v_buf, ...)                  \
	({                                                    \
		char *__k2v_tmp = type##_to_k2v(__VA_ARGS__); \
		size_t __k2v_size = 4;                        \
		if (__k2v_buf != NULL) {                      \
			__k2v_size += strlen(__k2v_buf);      \
		}                                             \
		__k2v_size += strlen(__k2v_tmp) + 4;          \
		__k2v_buf = realloc(__k2v_buf, __k2v_size);   \
		strcat(__k2v_buf, __k2v_tmp);                 \
		free(__k2v_tmp);                              \
		__k2v_tmp = strdup(__k2v_buf);                \
		free(__k2v_buf);                              \
		__k2v_tmp;                                    \
	})
