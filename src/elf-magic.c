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
 *
 */
#include "include/ruri.h"
// Get ELF magic number and mask for cross_arch specified.
struct MAGIC *get_magic(const char *cross_arch)
{
	struct MAGIC *ret = (struct MAGIC *)malloc(sizeof(struct MAGIC));
	if (strcmp(cross_arch, "aarch64") == 0) {
		ret->magic = magicof(aarch64);
		ret->mask = maskof(aarch64);
	} else if (strcmp(cross_arch, "alpha") == 0) {
		ret->magic = magicof(alpha);
		ret->mask = maskof(alpha);
	} else if (strcmp(cross_arch, "arm") == 0) {
		ret->magic = magicof(arm);
		ret->mask = maskof(arm);
	} else if (strcmp(cross_arch, "armeb") == 0) {
		ret->magic = magicof(armeb);
		ret->mask = maskof(armeb);
	} else if (strcmp(cross_arch, "cris") == 0) {
		ret->magic = magicof(cris);
		ret->mask = maskof(cris);
	} else if (strcmp(cross_arch, "hexagon") == 0) {
		ret->magic = magicof(hexagon);
		ret->mask = maskof(hexagon);
	} else if (strcmp(cross_arch, "hppa") == 0) {
		ret->magic = magicof(hppa);
		ret->mask = maskof(hppa);
	} else if (strcmp(cross_arch, "i386") == 0) {
		ret->magic = magicof(i386);
		ret->mask = maskof(i386);
	} else if (strcmp(cross_arch, "loongarch64") == 0) {
		ret->magic = magicof(loongarch64);
		ret->mask = maskof(loongarch64);
	} else if (strcmp(cross_arch, "m68k") == 0) {
		ret->magic = magicof(m68k);
		ret->mask = maskof(m68k);
	} else if (strcmp(cross_arch, "microblaze") == 0) {
		ret->magic = magicof(microblaze);
		ret->mask = maskof(microblaze);
	} else if (strcmp(cross_arch, "mips") == 0) {
		ret->magic = magicof(mips);
		ret->mask = maskof(mips);
	} else if (strcmp(cross_arch, "mips64") == 0) {
		ret->magic = magicof(mips64);
		ret->mask = maskof(mips64);
	} else if (strcmp(cross_arch, "mips64el") == 0) {
		ret->magic = magicof(mips64el);
		ret->mask = maskof(mips64el);
	} else if (strcmp(cross_arch, "mipsel") == 0) {
		ret->magic = magicof(mipsel);
		ret->mask = maskof(mipsel);
	} else if (strcmp(cross_arch, "mipsn32") == 0) {
		ret->magic = magicof(mipsn32);
		ret->mask = maskof(mipsn32);
	} else if (strcmp(cross_arch, "mipsn32el") == 0) {
		ret->magic = magicof(mipsn32el);
		ret->mask = maskof(mipsn32el);
	} else if (strcmp(cross_arch, "ppc") == 0) {
		ret->magic = magicof(ppc);
		ret->mask = maskof(ppc);
	} else if (strcmp(cross_arch, "ppc64") == 0) {
		ret->magic = magicof(ppc64);
		ret->mask = maskof(ppc64);
	} else if (strcmp(cross_arch, "ppc64le") == 0) {
		ret->magic = magicof(ppc64le);
		ret->mask = maskof(ppc64le);
	} else if (strcmp(cross_arch, "riscv32") == 0) {
		ret->magic = magicof(riscv32);
		ret->mask = maskof(riscv32);
	} else if (strcmp(cross_arch, "riscv64") == 0) {
		ret->magic = magicof(riscv64);
		ret->mask = maskof(riscv64);
	} else if (strcmp(cross_arch, "s390x") == 0) {
		ret->magic = magicof(s390x);
		ret->mask = maskof(s390x);
	} else if (strcmp(cross_arch, "sh4") == 0) {
		ret->magic = magicof(sh4);
		ret->mask = maskof(sh4);
	} else if (strcmp(cross_arch, "sh4eb") == 0) {
		ret->magic = magicof(sh4eb);
		ret->mask = maskof(sh4eb);
	} else if (strcmp(cross_arch, "sparc") == 0) {
		ret->magic = magicof(sparc);
		ret->mask = maskof(sparc);
	} else if (strcmp(cross_arch, "sparc32plus") == 0) {
		ret->magic = magicof(sparc32plus);
		ret->mask = maskof(sparc32plus);
	} else if (strcmp(cross_arch, "sparc64") == 0) {
		ret->magic = magicof(sparc64);
		ret->mask = maskof(sparc64);
	} else if (strcmp(cross_arch, "x86_64") == 0) {
		ret->magic = magicof(x86_64);
		ret->mask = maskof(x86_64);
	} else if (strcmp(cross_arch, "xtensa") == 0) {
		ret->magic = magicof(xtensa);
		ret->mask = maskof(xtensa);
	} else if (strcmp(cross_arch, "xtensaeb") == 0) {
		ret->magic = magicof(xtensaeb);
		ret->mask = maskof(xtensaeb);
	} else {
		error("\033[31mError: unknow architecture: %s\nSupported architectures: aarch64, alpha, arm, armeb, cris, hexagon, hppa, i386, loongarch64, m68k, microblaze, mips, mips64, mips64el, mipsel, mipsn32, mipsn32el, ppc, ppc64, ppc64le, riscv32, riscv64, s390x, sh4, sh4eb, sparc, sparc32plus, sparc64, x86_64, xtensa, xtensaeb\n", cross_arch);
	}
	return ret;
}
