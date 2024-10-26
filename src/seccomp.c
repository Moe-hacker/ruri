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
// Setup seccomp filter rule, with libseccomp.
void setup_seccomp(const struct CONTAINER *container)
{
	/*
	 * Based on docker's default seccomp profile.
	 * NOTE: This profile is not fully tested.
	 */
	scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);
	// I hope this is the right way to write the seccomp rule...
	if (is_in_caplist(container->drop_caplist, CAP_SYS_PACCT)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(acct), 0);
	}
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(add_key), 0);
	if (is_in_caplist(container->drop_caplist, CAP_SYS_ADMIN)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(bpf), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(lookup_dcookie), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(mount), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(quotactl), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(setns), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(swapon), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(swapoff), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(umount), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(umount2), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(unshare), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(vm86), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(vm86old), 0);
	}
	if (is_in_caplist(container->drop_caplist, CAP_SYS_TIME)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clock_adjtime), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clock_settime), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(settimeofday), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(stime), 0);
	}
	if (is_in_caplist(container->drop_caplist, CAP_SYS_MODULE)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(create_module), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(delete_module), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(finit_module), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(init_module), 0);
	}
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(get_kernel_syms), 0);
	if (is_in_caplist(container->drop_caplist, CAP_SYS_NICE)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(get_mempolicy), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(mbind), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(set_mempolicy), 0);
	}
	if (is_in_caplist(container->drop_caplist, CAP_SYS_RAWIO)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(ioperm), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(iopl), 0);
	}
	if (is_in_caplist(container->drop_caplist, CAP_SYS_PTRACE)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(kcmp), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(process_vm_readv), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(process_vm_writev), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(ptrace), 0);
	}
	if (is_in_caplist(container->drop_caplist, CAP_SYS_BOOT)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(kexec_file_load), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(kexec_load), 0);
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(reboot), 0);
	}
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(keyctl), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(move_pages), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(nfsservctl), 0);
	if (is_in_caplist(container->drop_caplist, CAP_DAC_READ_SEARCH)) {
		seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(open_by_handle_at), 0);
	}
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(perf_event_open), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(personality), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pivot_root), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(query_module), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(request_key), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sysfs), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(_sysctl), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(uselib), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(userfaultfd), 0);
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(ustat), 0);
	// Disable no_new_privs bit by default.
	seccomp_attr_set(ctx, SCMP_FLTATR_CTL_NNP, 0);
	// Load seccomp rules.
	seccomp_load(ctx);
	log("{base}Seccomp filter loaded\n");
}
