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
#include "include/k2v.h"
// Warning.
#define warning(...)                                                                              \
	{                                                                                         \
		if (k2v_show_warning) {                                                           \
			fprintf(stderr, ##__VA_ARGS__);                                           \
		}                                                                                 \
		if (k2v_stop_at_warning) {                                                        \
			fprintf(stderr, "\033[31mlibk2v stop_at_warning set, exit now\n\033[0m"); \
			exit(EXIT_FAILURE);                                                       \
		}                                                                                 \
	}
// For warning() macro.
// We use global variables here, because we need it to be simple for developers.
bool k2v_stop_at_warning = false;
bool k2v_show_warning = true;
static char *cuts(const char *str, char start, char end)
{
	/*
	 * Cut the string from start to end.
	 * Set start or end to 0 to skip check for it.
	 * The return value will not contain the start or end.
	 *
	 * Example for return value:
	 *
	 * char *str = "+111-";
	 *
	 * cuts(str, '+', '-') = "111"
	 * cuts(str,  0,  '-') = "+111"
	 * cuts(str, '+',  0) = "111-"
	 *
	 */
	// Null string.
	if (str[0] == '\0') {
		return NULL;
	}
	char *buf = NULL;
	char *ret = NULL;
	// Search for start char.
	if (start != 0) {
		for (size_t i = 0; i < strlen(str); i++) {
			if (str[i] == start) {
				// Get the string after `start`.
				// '\0' means nothing left after `start`, so just return NULL.
				if (str[i + 1] != '\0') {
					buf = (strdup(&str[i + 1]));
				} else {
					return NULL;
				}
				break;
			}
		}
	} else {
		buf = strdup(str);
	}
	// Check if we still have a non-null buf.
	// It works, do not change.
	if (buf == NULL) {
		return NULL;
	}
	// Search for end char.
	if (end != 0) {
		for (size_t i = 0; i < strlen(buf); i++) {
			if (buf[i] == end) {
				// Check if we have character before `end`.
				if (i > 0) {
					// Set end to '\0'.
					// String after `end` will be ignored by strdup(2).
					buf[i] = '\0';
					ret = strdup(buf);
					break;
				}
				// If `end` is the start of `str`, just return NULL.
				ret = NULL;
				break;
			}
		}
	} else {
		ret = strdup(buf);
	}
	free(buf);
	// Return the string we get.
	return ret;
}
static char *get_first_line(const char *buf)
{
	/*
	 * Get the first line in `buf`.
	 * It will automatically remove spaces at the start of the line.
	 */
	char *ptr = cuts(buf, 0, '\n');
	char *ret = NULL;
	// Check if we have a line to read.
	if (ptr == NULL) {
		return NULL;
	}
	// Remove spaces.
	if (ptr[0] == ' ') {
		for (size_t i = 0; i < strlen(ptr); i++) {
			if (ptr[i] != ' ') {
				ret = strdup(&ptr[i]);
				break;
			}
		}
	} else {
		ret = strdup(ptr);
	}
	free(ptr);
	return ret;
}
static bool is_null_val(const char *buf)
{
	/*
	 * Check if the right value is null.
	 * It's used for do_basic_check().
	 */
	if (buf == NULL) {
		return false;
	}
	// "" is a null value.
	if (strcmp(buf, "\"\"") == 0) {
		return true;
	}
	// [] is a null array.
	if (strcmp(buf, "[]") == 0) {
		return true;
	}
	// [""] is also a null array.
	if (strcmp(buf, "[\"\"]") == 0) {
		return true;
	}
	return false;
}
static void do_basic_check(const char *buf)
{
	/*
	 * Do some basic checks when reading the config file.
	 * It can not make any changes of config file, just show warning.
	 * But the warning() macro will exit if k2v_stop_at_warning is set.
	 */
	const char *ptr = buf;
	char *line = NULL;
	char *tmp = NULL;
	while (true) {
		free(line);
		line = get_first_line(ptr);
		// Reached the end of buf.
		if (line == NULL) {
			return;
		}
		// Check if this is a comment line.
		if (line[0] != '#') {
			// Check if we have a legal left value.
			tmp = cuts(line, 0, '=');
			if (tmp == NULL) {
				warning("\033[31mlibk2v warning: unrecognized line: %s\n\033[0m", line);
				goto _continue;
			}
			free(tmp);
			// Check if we have a legal right value.
			tmp = cuts(line, '=', 0);
			if (tmp == NULL) {
				warning("\033[31mlibk2v warning: unrecognized line: %s\n\033[0m", line);
				goto _continue;
			}
			if (!is_null_val(tmp)) {
				free(tmp);
				// Right value only have two legal formats: "val" or ["val1","val2"].
				tmp = cuts(line, '"', '"');
				if (tmp == NULL) {
					tmp = cuts(line, '[', ']');
					if (tmp == NULL) {
						warning("\033[31mlibk2v warning: unrecognized line: %s\n\033[0m", line);
						goto _continue;
					}
				}
			}
			free(tmp);
		}
_continue:
		// Goto the next line.
		ptr = strchr(ptr, '\n');
		ptr = &ptr[1];
	}
}
static char *key_get_right(const char *key, const char *buf)
{
	/*
	 * Get the right value of `=` for the `key`.
	 * The value returned will be used in other functions.
	 */
	const char *ptr = buf;
	char *ret = NULL;
	char *line = NULL;
	char *tmp = NULL;
	while (true) {
		free(line);
		line = get_first_line(ptr);
		if (line == NULL) {
			return NULL;
		}
		if (line[0] != '#') {
			tmp = cuts(line, 0, '=');
			if (tmp != NULL) {
				if (strcmp(tmp, key) == 0) {
					free(tmp);
					ret = cuts(line, '=', 0);
					free(line);
					break;
				}
				free(tmp);
			}
		}
		ptr = strchr(ptr, '\n');
		ptr = &ptr[1];
	}
	return ret;
}
bool have_key(const char *key, const char *buf)
{
	/*
	 * Check if we have the `key` in `buf`.
	 */
	const char *ptr = buf;
	bool ret = false;
	char *line = NULL;
	char *tmp = NULL;
	while (true) {
		free(line);
		line = get_first_line(ptr);
		if (line == NULL) {
			break;
		}
		if (line[0] != '#') {
			tmp = cuts(line, 0, '=');
			if (tmp != NULL) {
				if (strcmp(tmp, key) == 0) {
					free(tmp);
					tmp = cuts(line, '=', 0);
					if (!is_null_val(tmp)) {
						free(tmp);
						// Right value only have two legal formats: "val" or ["val1","val2"].
						tmp = cuts(line, '"', '"');
						if (tmp == NULL) {
							tmp = cuts(line, '[', ']');
							if (tmp == NULL) {
								free(line);
								return false;
							}
						}
					}
					ret = true;
					free(tmp);
					free(line);
					break;
				}
				free(tmp);
			}
		}
		ptr = strchr(ptr, '\n');
		ptr = &ptr[1];
	}
	return ret;
}
char *key_get_char(const char *key, const char *buf)
{
	if (buf == NULL) {
		return NULL;
	}
	char *ret = NULL;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return NULL;
	}
	ret = cuts(tmp, '"', '"');
	free(tmp);
	return ret;
}
int key_get_int(const char *key, const char *buf)
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return -1;
	}
	char *val = cuts(tmp, '"', '"');
	if (val == NULL) {
		return -1;
	}
	ret = atoi(val);
	return ret;
}
float key_get_float(const char *key, const char *buf)
{
	if (buf == NULL) {
		return -1;
	}
	float ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return -1;
	}
	char *val = cuts(tmp, '"', '"');
	if (val == NULL) {
		return -1;
	}
	ret = (float)atof(val);
	return ret;
}
bool key_get_bool(const char *key, const char *buf)
{
	if (buf == NULL) {
		return false;
	}
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return false;
	}
	char *val = cuts(tmp, '"', '"');
	free(tmp);
	if (val == NULL) {
		return false;
	}
	if (strcmp(val, "true") == 0) {
		free(val);
		return true;
	}
	free(val);
	return false;
}
static int char_to_int_array(const char *buf, int *array)
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = NULL;
	const char *ptr = buf;
	while (true) {
		tmp = cuts(ptr, '"', '"');
		array[ret] = atoi(tmp);
		ret++;
		ptr = strchr(ptr, ',');
		if (ptr == NULL) {
			free(tmp);
			break;
		}
		ptr = &ptr[1];
		free(tmp);
	}
	return ret;
}
static int char_to_float_array(const char *buf, float *array)
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = NULL;
	const char *ptr = buf;
	while (true) {
		tmp = cuts(ptr, '"', '"');
		array[ret] = (float)atof(tmp);
		ret++;
		ptr = strchr(ptr, ',');
		if (ptr == NULL) {
			free(tmp);
			break;
		}
		ptr = &ptr[1];
		free(tmp);
	}
	return ret;
}
static int char_to_char_array(const char *buf, char *array[])
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = NULL;
	const char *ptr = buf;
	while (true) {
		tmp = cuts(ptr, '"', '"');
		array[ret] = strdup(tmp);
		array[ret + 1] = NULL;
		ret++;
		ptr = strchr(ptr, ',');
		if (ptr == NULL) {
			free(tmp);
			break;
		}
		ptr = &ptr[1];
		free(tmp);
	}
	return ret;
}
int key_get_int_array(const char *key, const char *buf, int *array)
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return -1;
	}
	ret = char_to_int_array(tmp, array);
	free(tmp);
	return ret;
}
int key_get_char_array(const char *key, const char *buf, char *array[])
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return -1;
	}
	ret = char_to_char_array(tmp, array);
	free(tmp);
	return ret;
}
int key_get_float_array(const char *key, const char *buf, float *array)
{
	if (buf == NULL) {
		return -1;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return -1;
	}
	ret = char_to_float_array(tmp, array);
	free(tmp);
	return ret;
}
char *k2v_open_file(char *path, size_t bufsize)
{
	/*
	 * It will automatically call malloc(2),
	 * open config file specified by `path`,
	 * read the file to ret, and do basic checks.
	 * If config file does not exist, return NULL.
	 */
	char *ret = (char *)malloc(bufsize);
	int fd = open(path, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		free(ret);
		return NULL;
	}
	ssize_t len = read(fd, ret, bufsize);
	ret[len] = '\0';
	do_basic_check(ret);
	return ret;
}
