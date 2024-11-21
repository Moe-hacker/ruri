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
#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <sys/syscall.h>
// This program should be compiled with -lpthread.
#include <pthread.h>
#ifndef _Nullable
#define _Nullable
#endif
#ifndef _Nonnull
#define _Nonnull
#endif
// WARNING: magic number! Do not change!
#define X_SIZE 36
#define Y_SIZE 2
struct LAYER {
	/*
	 * This is the smallest unit of the animation.
	 * It represents one frame of an action.
	 * The name is taken by historical reasons.
	 */
	// The string to be printed.
	char *layer;
	// The offset of the x-axis.
	int x_offset;
	// The offset of the y-axis.
	int y_offset;
};
struct ACTION {
	/*
	 * This is a doubly linked list,
	 * because we want to playback the action.
	 */
	// The layer to be printed.
	struct LAYER *layer;
	// The pointer to the last action.
	struct ACTION *prior;
	// The pointer to the next action.
	struct ACTION *next;
};
// The offset of the x-axis.
extern int x;
// The offset of the y-axis.
extern int y;
// The lock for multi-threading.
// This lock is used for print_layer() and clear_layer().
extern atomic_flag lock;
// Function list.
void nekofeng_spin_lock(atomic_flag *_Nonnull lock);
void nekofeng_spin_unlock(atomic_flag *_Nonnull lock);
void nekofeng_play_action(struct ACTION *_Nonnull action, useconds_t inr, unsigned int keep);
void nekofeng_playback_action(struct ACTION *_Nonnull action, useconds_t inr, unsigned int keep);
void nekofeng_free_action(struct ACTION *_Nonnull action);
struct ACTION *nekofeng_add_action(struct ACTION *_Nonnull action, int x_offset, int y_offset, char *_Nonnull layer);
void nekofeng_face(useconds_t inr, unsigned int keep);
void nekofeng_mouth(useconds_t inr, unsigned int keep);
void nekofeng_ahoge(useconds_t inr, unsigned int keep);
void nekofeng_blink_lefteye(useconds_t inr, unsigned int keep);
void nekofeng_blink_righteye(useconds_t inr, unsigned int keep);
void nekofeng_typewrite_layer(struct LAYER *_Nonnull layer, useconds_t inr, bool blink);
void nekofeng_clear_typewrite_layer(struct LAYER *_Nonnull layer, useconds_t inr);
