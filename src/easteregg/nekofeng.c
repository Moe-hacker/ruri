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
/*
 * This file was the main.c in nekofeng project.
 * Now, it provides the function AwA() as the easteregg of ruri.
 */
// The global variables are defined here.
int x;
int y;
atomic_flag lock = ATOMIC_FLAG_INIT;
// The spin lock.
void spin_lock(atomic_flag *lock)
{
	while (atomic_flag_test_and_set(lock)) {
	}
}
// The spin unlock.
void spin_unlock(atomic_flag *lock)
{
	atomic_flag_clear(lock);
}
// init() function for getting window size.
static void init()
{
	printf("\033c");
	// Use ioctl(2) to get the window size.
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	x = size.ws_col / 2 - X_SIZE / 2;
	y = size.ws_row / 2 - Y_SIZE / 2;
}
// TODO: WIP.
void *test0(void *arg)
{
	face(100000, 15);
	return arg;
}
void *test1(void *arg)
{
	close_and_open_lefteye(100000, 1);
	blink_lefteye(100000, 5);
	return arg;
}
void *test2(void *arg)
{
	close_and_open_righteye(100000, 1);
	blink_righteye(100000, 5);
	return arg;
}
void *test3(void *arg)
{
	mouth(100000, 15);
	return arg;
}
void AwA()
{
	printf("\033[?25l");
	init();
	struct LAYER layer;
	layer.layer = "\033[1;38;2;254;228;208m\n"
		      "          Keep moe.\n"
		      "          Keep cool.\n"
		      "         Keep hacking.\n"
		      "Keep on the side of technology.\n\n"
		      "      But talk is cheap,\n"
		      "       Show me the code.\n";
	layer.x_offset = 3;
	layer.y_offset = -2;
	typewrite_layer(&layer, 50000, true);
	sleep(2);
	clear_typewrite_layer(&layer, 50000);
	pthread_t t0, t1, t2, t3;
	pthread_create(&t0, NULL, test0, NULL);
	pthread_create(&t3, NULL, test3, NULL);
	pthread_create(&t1, NULL, test1, NULL);
	pthread_create(&t2, NULL, test2, NULL);
	sleep(15);
	printf("\n\033[?25h");
}
