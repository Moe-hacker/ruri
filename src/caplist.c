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
// Add a cap to caplist.
void add_to_caplist(cap_value_t *list, cap_value_t cap)
{
	/*
	 * If cap is already in list, just do nothing and quit.
	 * list[] is initialized by INIT_VALUE, and the INIT_VALUE will be ignored when dropping caps.
	 */
	bool in_list = false;
	// Check if the cap to add is already in caplist.
	for (int i = 0; i < CAP_LAST_CAP; i++) {
		if (list[i] == INIT_VALUE) {
			break;
		}
		if (list[i] == cap) {
			in_list = true;
			break;
		}
	}
	// Add cap to caplist.
	if (!in_list) {
		for (int k = 0; k < CAP_LAST_CAP; k++) {
			if (list[k] == INIT_VALUE) {
				list[k] = cap;
				list[k + 1] = INIT_VALUE;
				break;
			}
		}
	}
}
// Check if the cap includes in the list.
bool is_in_caplist(const cap_value_t *list, cap_value_t cap)
{
	/*
	 * For setup_seccomp().
	 */
	bool ret = false;
	// Check if the cap to add is already in caplist.
	for (int i = 0; i < CAP_LAST_CAP; i++) {
		if (list[i] == cap) {
			ret = true;
			break;
		}
		if (list[i] == INIT_VALUE) {
			break;
		}
	}
	return ret;
}
// Del a cap from caplist.
void del_from_caplist(cap_value_t *list, cap_value_t cap)
{
	/*
	 * If the cap is not in list, just do nothing and quit.
	 * Or we will delete it from the list.
	 */
	for (int i = 0; i < CAP_LAST_CAP; i++) {
		if (list[i] == cap) {
			while (i < CAP_LAST_CAP) {
				list[i] = list[i + 1];
				i++;
			}
			list[i] = INIT_VALUE;
			break;
		}
	}
}
