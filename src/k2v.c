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
// Warnings && stop at warning.
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
// Get file size.
size_t k2v_get_filesize(const char *path)
{
	int fd = open(path, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		fprintf(stderr, "\033[31mNo such file or directory:%s\n\033[0m", path);
		if (k2v_stop_at_warning) {
			exit(1);
		} else {
			return 0;
		}
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t ret = filestat.st_size;
	close(fd);
	// To avoid overflow.
	return (size_t)ret + 3;
}
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
	// If both start and end is 0, return NULL.
	if (start == 0 && end == 0) {
		return NULL;
	}
	// NULL string.
	if (str == NULL || str[0] == '\0') {
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
				// If `end` is the start of `buf`, just return NULL.
				ret = NULL;
				break;
			}
			// If we reach the end of buf, just return NULL.
			if (i == strlen(buf)) {
				ret = NULL;
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
	const char *ptr = buf;
	// Remove null line and space.
	for (size_t i = 0; i < strlen(buf) - 1; i++) {
		if (ptr[i] != '\n' && ptr[i] != ' ') {
			break;
		}
		ptr = &ptr[i + 1];
	}
	char *line = cuts(ptr, 0, '\n');
	char *ret = NULL;
	// Check if we have a line to read.
	if (line == NULL) {
		return NULL;
	}
	// Seems stupid...
	// It works, do not change.
	ret = strdup(line);
	free(line);
	return ret;
}
static char *goto_next_line(const char *buf)
{
	// Remove null line.
	const char *ptr = buf;
	for (size_t i = 0; i < strlen(buf) - 1; i++) {
		if (ptr[i] != '\n' && ptr[i] != ' ') {
			break;
		}
		ptr = &ptr[i + 1];
	}
	// NULL will returned here if no `\n` found.
	return (strchr(ptr, '\n'));
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
	// For other string, we think it's not null, at least.
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
			// Check if we have a valid left value.
			tmp = cuts(line, 0, '=');
			if (tmp == NULL) {
				warning("\033[31mlibk2v warning: unrecognized line: %s\n\033[0m", line);
				goto _continue;
			}
			free(tmp);
			// Check if we have a valid right value.
			tmp = cuts(line, '=', 0);
			if (tmp == NULL) {
				warning("\033[31mlibk2v warning: unrecognized line: %s\n\033[0m", line);
				goto _continue;
			}
			if (!is_null_val(tmp)) {
				free(tmp);
				// Right value only have two valid formats: "val" or ["val1","val2"].
				tmp = cuts(line, '[', ']');
				if (tmp == NULL) {
					tmp = cuts(line, '"', '"');
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
		ptr = goto_next_line(ptr);
		ptr = &ptr[1];
	}
}
static char *key_get_right(const char *key, const char *buf)
{
	/*
	 * Get the right value of `=` for the `key`.
	 * The value returned will be used in other functions.
	 */
	// NULL check.
	if (key == NULL || buf == NULL) {
		return NULL;
	}
	const char *ptr = buf;
	char *ret = NULL;
	char *line = NULL;
	char *tmp = NULL;
	while (true) {
		free(line);
		// Goto the first valid line.
		line = get_first_line(ptr);
		// We reached the end but there is no `key` found.
		if (line == NULL) {
			return NULL;
		}
		// Skip comment line.
		if (line[0] != '#') {
			tmp = cuts(line, 0, '=');
			// Check if `left` matchs the `key` given.
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
		// Goto the next line.
		ptr = goto_next_line(ptr);
		ptr = &ptr[1];
	}
	return ret;
}
bool have_key(const char *key, const char *buf)
{
	/*
	 * Check if we have the `key` in `buf`.
	 * Since I never used this function, it might have bugs.
	 */
	// NULL check.
	if (key == NULL || buf == NULL) {
		return false;
	}
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
						// Right value only have two valid formats: "val" or ["val1","val2"].
						tmp = cuts(line, '[', ']');
						if (tmp == NULL) {
							tmp = cuts(line, '"', '"');
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
		ptr = goto_next_line(ptr);
		ptr = &ptr[1];
	}
	return ret;
}
char *key_get_char(const char *key, const char *buf)
{
	// Default return value: NULL.
	if (key == NULL || buf == NULL) {
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
	// Default return value: 0.
	// NULL check.
	if (key == NULL || buf == NULL) {
		return 0;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return 0;
	}
	char *val = cuts(tmp, '"', '"');
	if (val == NULL) {
		return 0;
	}
	ret = atoi(val);
	return ret;
}
float key_get_float(const char *key, const char *buf)
{
	// Default return value: 0.
	// NULL check
	if (key == NULL || buf == NULL) {
		return 0;
	}
	float ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return 0;
	}
	char *val = cuts(tmp, '"', '"');
	if (val == NULL) {
		return 0;
	}
	ret = (float)atof(val);
	return ret;
}
bool key_get_bool(const char *key, const char *buf)
{
	// Default return value: false.
	// NULL check.
	if (key == NULL || buf == NULL) {
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
	// Return lenth of the array we get.
	// Default return value: 0.
	if (buf == NULL) {
		return 0;
	}
	if (is_null_val(buf)) {
		return 0;
	}
	int ret = 0;
	char *tmp = NULL;
	const char *ptr = buf;
	while (true) {
		tmp = cuts(ptr, '"', '"');
		// Invalid format.
		if (tmp == NULL) {
			return 0;
		}
		array[ret] = atoi(tmp);
		ret++;
		ptr = strchr(ptr, ',');
		if (ptr == NULL) {
			free(tmp);
			break;
		}
		// Goto next value.
		ptr = &ptr[1];
		free(tmp);
	}
	return ret;
}
static int char_to_float_array(const char *buf, float *array)
{
	// Return lenth of the array we get.
	// Default return value: 0.
	if (buf == NULL) {
		return 0;
	}
	if (is_null_val(buf)) {
		return 0;
	}
	int ret = 0;
	char *tmp = NULL;
	const char *ptr = buf;
	while (true) {
		tmp = cuts(ptr, '"', '"');
		// Invalid format.
		if (tmp == NULL) {
			return 0;
		}
		array[ret] = (float)atof(tmp);
		ret++;
		ptr = strchr(ptr, ',');
		if (ptr == NULL) {
			free(tmp);
			break;
		}
		// Goto next value.
		ptr = &ptr[1];
		free(tmp);
	}
	return ret;
}
static int char_to_char_array(const char *buf, char *array[])
{
	// Return lenth of the array we get.
	// Default return value: 0.
	// We will not alloc memory for `array`.
	if (buf == NULL || array == NULL) {
		return 0;
	}
	if (is_null_val(buf)) {
		return 0;
	}
	int ret = 0;
	char *tmp = NULL;
	const char *ptr = buf;
	while (true) {
		tmp = cuts(ptr, '"', '"');
		// Invalid format.
		if (tmp == NULL) {
			return 0;
		}
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
	// Return lenth of the array we get.
	// Default return value: 0.
	// NULL check, we will not alloc memory for array.
	if (key == NULL || buf == NULL || array == NULL) {
		return 0;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return 0;
	}
	ret = char_to_int_array(tmp, array);
	free(tmp);
	return ret;
}
int key_get_char_array(const char *key, const char *buf, char *array[])
{
	// Return lenth of the array we get.
	// Default return value: 0.
	// NULL check, we will not alloc memory for array.
	if (key == NULL || buf == NULL || array == NULL) {
		return 0;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return 0;
	}
	ret = char_to_char_array(tmp, array);
	free(tmp);
	return ret;
}
int key_get_float_array(const char *key, const char *buf, float *array)
{
	// Return lenth of the array we get.
	// Default return value: 0.
	// NULL check, we will not alloc memory for array.
	if (key == NULL || buf == NULL || array == NULL) {
		return 0;
	}
	int ret = 0;
	char *tmp = key_get_right(key, buf);
	if (tmp == NULL) {
		return 0;
	}
	ret = char_to_float_array(tmp, array);
	free(tmp);
	return ret;
}
char *k2v_open_file(const char *path, size_t bufsize)
{
	/*
	 * It will automatically call malloc(2),
	 * open config file specified by `path`,
	 * read the file to ret, and do basic checks.
	 * If config file does not exist, return NULL.
	 */
	// NULL check.
	if (path == NULL) {
		return NULL;
	}
	// bufsize+1 might avoid overflow(I hope).
	char *ret = (char *)malloc(bufsize + 1);
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
static void print_shell_array(const char *buf)
{
	// NULL check.
	if (buf == NULL) {
		return;
	}
	printf("(");
	for (size_t i = 0; i < strlen(buf); i++) {
		if (buf[i] == '"') {
			printf("%c", buf[i]);
			i++;
			if (buf[i] == ',') {
				printf(" ");
			} else {
				printf("%c", buf[i]);
			}
		} else {
			printf("%c", buf[i]);
		}
	}
	printf(")\n");
}
static void print_key_to_shell(const char *key, const char *buf)
{
	// NULL check.
	if (key == NULL || buf == NULL) {
		return;
	}
	char *right = key_get_right(key, buf);
	char *test = NULL;
	if (right == NULL) {
		return;
	}
	if (!is_null_val(right)) {
		test = cuts(right, '[', ']');
		if (test == NULL) {
			test = cuts(right, '"', '"');
			if (test != NULL) {
				printf("%s=\"%s\"\n", key, test);
				free(test);
			}
		} else {
			printf("%s=", key);
			print_shell_array(test);
		}
	} else {
		printf("%s=\"\"\n", key);
	}
	free(right);
}
void k2v_to_shell(const char *buf)
{
	// NULL check.
	if (buf == NULL) {
		return;
	}
	const char *ptr = buf;
	char *line = NULL;
	char *key = NULL;
	while (true) {
		free(line);
		line = get_first_line(ptr);
		if (line == NULL) {
			return;
		}
		if (line[0] != '#') {
			key = cuts(line, 0, '=');
			if (key != NULL) {
				print_key_to_shell(key, buf);
				free(key);
			}
		}
		ptr = goto_next_line(ptr);
		ptr = &ptr[1];
	}
}
char *char_to_k2v(const char *key, const char *val)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *ret = NULL;
	if (val != NULL) {
		ret = malloc(strlen(key) + strlen(val) + 8);
		sprintf(ret, "%s=\"%s\"\n", key, val);
	} else {
		ret = malloc(strlen(key) + 8);
		sprintf(ret, "%s=\"\"\n", key);
	}
	return ret;
}
char *int_to_k2v(const char *key, int val)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *ret = malloc(strlen(key) + 12 + 8);
	sprintf(ret, "%s=\"%d\"\n", key, val);
	return ret;
}
char *bool_to_k2v(const char *key, bool val)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *ret = malloc(strlen(key) + 8 + 8);
	sprintf(ret, "%s=\"%s\"\n", key, val ? "true" : "false");
	return ret;
}
char *float_to_k2v(const char *key, float val)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *buf = malloc(strlen(key) + 400 + 8);
	sprintf(buf, "%s=\"%f\"\n", key, val);
	char *ret = strdup(buf);
	free(buf);
	return ret;
}
char *char_array_to_k2v(const char *key, char *const *val, int len)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *buf = malloc(strlen(key) + 8);
	if (len == 0) {
		sprintf(buf, "%s=[]\n", key);
		char *ret = strdup(buf);
		free(buf);
		return ret;
	}
	size_t size = strlen(key) + 8;
	sprintf(buf, "%s=[", key);
	char *tmp = NULL;
	for (int i = 0; i < len; i++) {
		tmp = malloc(strlen(val[i]) + 8);
		sprintf(tmp, "\"%s\"", val[i]);
		size += strlen(val[i]) + 8;
		buf = realloc(buf, size);
		strcat(buf, tmp);
		if (i != len - 1) {
			strcat(buf, ",");
		} else {
			strcat(buf, "]");
		}
		free(tmp);
	}
	strcat(buf, "\n");
	char *ret = strdup(buf);
	free(buf);
	return ret;
}
char *int_array_to_k2v(const char *key, int *val, int len)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *buf = malloc(strlen(key) + 12 * (size_t)len + 8);
	if (len == 0) {
		sprintf(buf, "%s=[]\n", key);
		char *ret = strdup(buf);
		free(buf);
		return ret;
	}
	sprintf(buf, "%s=[", key);
	char *tmp = malloc(12);
	for (int i = 0; i < len; i++) {
		sprintf(tmp, "\"%d\"", val[i]);
		strcat(buf, tmp);
		if (i != len - 1) {
			strcat(buf, ",");
		} else {
			strcat(buf, "]");
		}
	}
	strcat(buf, "\n");
	char *ret = strdup(buf);
	free(buf);
	free(tmp);
	return ret;
}
char *float_array_to_k2v(const char *key, float *val, int len)
{
	// NULL check.
	if (key == NULL) {
		return NULL;
	}
	char *buf = malloc(strlen(key) + 400 * (size_t)len + 8);
	if (len == 0) {
		sprintf(buf, "%s=[]\n", key);
		char *ret = strdup(buf);
		free(buf);
		return ret;
	}
	sprintf(buf, "%s=[", key);
	char *tmp = malloc(400);
	for (int i = 0; i < len; i++) {
		sprintf(tmp, "\"%f\"", val[i]);
		strcat(buf, tmp);
		if (i != len - 1) {
			strcat(buf, ",");
		} else {
			strcat(buf, "]");
		}
	}
	strcat(buf, "\n");
	char *ret = strdup(buf);
	free(buf);
	free(tmp);
	return ret;
}
