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
// Bool!!!
#if __STDC_VERSION__ < 202000L
#define bool _Bool
#define true ((_Bool) + 1u)
#define false ((_Bool) + 0u)
#endif
// Version info.
#define LIBK2V_MAJOR 0
#define LIBK2V_MINOR 1
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
char *k2v_open_file(char *path, size_t bufsize);
