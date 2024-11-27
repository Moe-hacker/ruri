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
/*
 * This file provides functions to manage capability list.
 * But drop_caps() to set capabilities is in chroot.c, not here.
 */
// Add a cap to caplist.
void ruri_add_to_caplist(cap_value_t *_Nonnull list, cap_value_t cap)
{
	/*
	 * If cap is already in list, just do nothing and quit.
	 * list[] is initialized by RURI_INIT_VALUE,
	 * and the RURI_INIT_VALUE is the end of the list.
	 */
	// We do not add non-supported capabilities to caplist.
	if (!CAP_IS_SUPPORTED(cap)) {
		return;
	}
	// Add cap to caplist.
	if (!ruri_is_in_caplist(list, cap)) {
		for (int k = 0; true; k++) {
			if (list[k] == RURI_INIT_VALUE) {
				list[k] = cap;
				list[k + 1] = RURI_INIT_VALUE;
				break;
			}
		}
	}
}
// Check if the cap is in the list.
bool ruri_is_in_caplist(const cap_value_t *_Nonnull list, cap_value_t cap)
{
	/*
	 * If cap is in list, return true,
	 * else, return false.
	 * RURI_INIT_VALUE is the end of the list.
	 */
	for (int i = 0; true; i++) {
		if (list[i] == cap) {
			return true;
			break;
		}
		if (list[i] == RURI_INIT_VALUE) {
			break;
		}
	}
	return false;
}
// Del a cap from caplist.
void ruri_del_from_caplist(cap_value_t *_Nonnull list, cap_value_t cap)
{
	/*
	 * If the cap is not in list, just do nothing and quit.
	 * Or we will delete it from the list.
	 */
	for (int i = 0; true; i++) {
		if (list[i] == cap) {
			while (i <= RURI_CAP_LAST_CAP) {
				list[i] = list[i + 1];
				i++;
			}
			list[i - 1] = RURI_INIT_VALUE;
			return;
		}
		if (list[i] == RURI_INIT_VALUE) {
			return;
		}
	}
}
void ruri_build_caplist(cap_value_t caplist[], bool privileged, cap_value_t drop_caplist_extra[], cap_value_t keep_caplist_extra[])
{
	/*
	 * If privileged is true, we setup a full list of all capabilities,
	 * del keep_caplist_common[] from the list,
	 * and then add drop_caplist_extra[] to the list,
	 * and del keep_caplist_extra[] from the list.
	 *
	 * If privileged is false, we just add drop_caplist_extra[] to the list,
	 * and del keep_caplist_extra[] from the list.
	 *
	 * NOTE: keep_caplist_extra[] will cover drop_caplist_extra[],
	 * if they have the same capabilities.
	 */
	// Based on docker's default capability set.
	// And I removed some unneeded capabilities.
	cap_value_t keep_caplist_common[] = { CAP_CHOWN, CAP_DAC_OVERRIDE, CAP_FSETID, CAP_FOWNER, CAP_SETGID, CAP_SETUID, CAP_SETFCAP, CAP_SETPCAP, CAP_NET_BIND_SERVICE, CAP_SYS_CHROOT, CAP_KILL, CAP_AUDIT_WRITE, RURI_INIT_VALUE };
	// Set default caplist to drop.
	caplist[0] = RURI_INIT_VALUE;
	if (!privileged) {
		// Add all capabilities to caplist.
		for (int i = 0; CAP_IS_SUPPORTED(i); i++) {
			caplist[i] = i;
			caplist[i + 1] = RURI_INIT_VALUE;
		}
		// Del keep_caplist_common[] from caplist.
		for (int i = 0; true; i++) {
			if (keep_caplist_common[i] == RURI_INIT_VALUE) {
				break;
			}
			ruri_del_from_caplist(caplist, keep_caplist_common[i]);
		}
	}
	// Add drop_caplist_extra[] to caplist.
	if (drop_caplist_extra[0] != RURI_INIT_VALUE) {
		for (int i = 0; true; i++) {
			if (drop_caplist_extra[i] == RURI_INIT_VALUE) {
				break;
			}
			ruri_add_to_caplist(caplist, drop_caplist_extra[i]);
		}
	}
	// Del keep_caplist_extra[] from caplist.
	if (keep_caplist_extra[0] != RURI_INIT_VALUE) {
		for (int i = 0; true; i++) {
			if (keep_caplist_extra[i] == RURI_INIT_VALUE) {
				break;
			}
			ruri_del_from_caplist(caplist, keep_caplist_extra[i]);
		}
	}
}
