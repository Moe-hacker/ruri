// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
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
#include "include/nekofeng.h"
// NOLINTBEGIN
/*
 * This file provides the function
 * nekofeng_typewrite_layer() and nekofeng_clear_typewrite_layer().
 *
 * Usage:
 *
 *  struct NEKOFENG_LAYER layer;
 *  layer.layer = "\033[1;38;2;254;228;208mxxxxxxxxxxxx\n";
 *  layer.x_offset = 1;
 *  layer.y_offset = 14;
 *  nekofeng_typewrite_layer(&layer, 50000, true);
 *  sleep(2);
 *  nekofeng_clear_typewrite_layer(&layer, 50000);
 *
 * Do not care how it works, because I forgot,
 * and I am too lazy to read the code.
 *
 */
#ifndef RURI_CORE_ONLY
static int get_last_line_size(char32_t *_Nonnull buf)
{
	if (buf == NULL) {
		return 0;
	}
	char32_t *tmp = NULL;
	int ret = 0;
	for (size_t i = nekofeng_strlen(buf); i > 0; i--) {
		if (buf[i] == U'\n') {
			tmp = nekofeng_strdup(&buf[i + 1]);
			break;
		}
	}
	for (size_t i = 0; i < nekofeng_strlen(tmp); i++) {
		// Color.
		if (tmp[i] == U'\033') {
			for (size_t j = i; j < nekofeng_strlen(tmp); j++) {
				if (tmp[j] == U'm') {
					i = j;
					break;
				}
			}
			continue;
		}
		ret++;
	}
	free(tmp);
	return ret;
}
static char32_t *del_last_line(char32_t *_Nonnull buf)
{
	if (buf == NULL) {
		return NULL;
	}
	char32_t *tmp = nekofeng_strdup(buf);
	for (size_t i = nekofeng_strlen(buf); i > 0; i--) {
		if (buf[i] == U'\n') {
			tmp[i] = U'\0';
			break;
		}
	}
	free(buf);
	return tmp;
}
static int get_lines(char32_t *_Nonnull buf)
{
	int j = 0;
	for (size_t i = 0; i < nekofeng_strlen(buf); i++) {
		if (buf[i] == U'\n') {
			j++;
		}
	}
	return j;
}
static void nekofeng_printf(char32_t *_Nonnull str)
{
	nekofeng_spin_lock(&nekofeng_lock);
	for (size_t i = 0; i < nekofeng_strlen(str); i++) {
		char character[64] = { '\0' };
		mbstate_t state = { 0 };
		size_t len = c32rtomb(character, str[i], &state);
		if (len == (size_t)-1) {
			perror("c32rtomb");
			nekofeng_spin_unlock(&nekofeng_lock);
			return;
		}
		character[len] = '\0';
		printf("%s", character);
	}
	fflush(stdout);
	nekofeng_spin_unlock(&nekofeng_lock);
}
void nekofeng_typewrite_layer(struct NEKOFENG_LAYER *_Nonnull layer, useconds_t inr, bool blink)
{
	int y_offset = 0;
	printf("\033[%dH", nekofeng_y + layer->y_offset);
	printf("\033[%dG", nekofeng_x + layer->x_offset);
	fflush(stdout);
	for (size_t i = 0; i < nekofeng_strlen(layer->layer); i++) {
		// The next line.
		if (layer->layer[i] == U'\n') {
			y_offset++;
			printf("\033[%dH", nekofeng_y + layer->y_offset + y_offset);
			printf("\033[%dG", nekofeng_x + layer->x_offset);
			continue;
		}
		// '#' means a ' ' to cover the layer under it.
		if (layer->layer[i] == U'#') {
			printf(" ");
		} // Skip space.
		else if (layer->layer[i] != U' ') {
			// Color.
			if (layer->layer[i] == U'\033') {
				// Be mindful! This might overflow.
				char32_t tmp[1024] = { U'\0' };
				for (size_t j = i; j < nekofeng_strlen(layer->layer); j++) {
					tmp[j - i] = layer->layer[j];
					tmp[j - i + 1] = 0;
					if (layer->layer[j] == U'm') {
						i = j;
						nekofeng_printf(tmp);
						break;
					}
				}
				continue;
			}
			if (blink) {
				printf("#");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D\033[?25l");
				printf("£");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D\033[?25l");
				printf("&");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D\033[?25l");
				printf("*");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D\033[?25l");
			}
			char character[64] = { '\0' };
			mbstate_t state = { 0 };
			size_t len = c32rtomb(character, layer->layer[i], &state);
			if (len == (size_t)-1) {
				perror("c32rtomb");
				nekofeng_spin_unlock(&nekofeng_lock);
				return;
			}
			character[len] = '\0';
			printf("%s", character);
			fflush(stdout);
			usleep(inr);
		} else {
			printf("\033[1C\033[?25l");
		}
	}
}
void nekofeng_clear_typewrite_layer(struct NEKOFENG_LAYER *_Nonnull layer, useconds_t inr)
{
	int y_offset = get_lines(layer->layer);
	char32_t *buf = nekofeng_strdup(layer->layer);
	int x_offset = 0;
	for (int i = y_offset; i > 0; i--) {
		x_offset = get_last_line_size(buf);
		buf = del_last_line(buf);
		for (int j = x_offset; j > 0; j--) {
			printf("\033[%dH", nekofeng_y + layer->y_offset + i);
			printf("\033[%dG", nekofeng_x + layer->x_offset + j - 1);
			printf(" ");
			fflush(stdout);
			usleep(inr);
		}
	}
	free(buf);
}
#endif
// NOLINTEND