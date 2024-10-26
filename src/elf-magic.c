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
// Get ELF magic number and mask for cross_arch specified.
struct MAGIC *get_magic(const char *cross_arch)
{
	/*
	 * I know that this seems to be a little bit stupid,
	 * but we have no other ways to match the architecture to its ELF magic.
	 * TODO: Support more architecture aliases.
	 */
	struct MAGIC *ret = (struct MAGIC *)malloc(sizeof(struct MAGIC));
// Avoid to simulate the same architecture as host.
#if defined(__aarch64__)
	if (strcmp(cross_arch, "aarch64") == 0 || strcmp(cross_arch, "arm64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__alpha__)
	if (strcmp(cross_arch, "alpha") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__arm__)
	if (strcmp(cross_arch, "arm") == 0 || strcmp(cross_arch, "arm32") == 0 || strcmp(cross_arch, "armhf") == 0 || strcmp(cross_arch, "armel") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__armeb__)
	if (strcmp(cross_arch, "armeb") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__cris__)
	if (strcmp(cross_arch, "cris") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__hexagon__)
	if (strcmp(cross_arch, "hexagon") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__hppa__)
	if (strcmp(cross_arch, "hppa") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__i386__)
	if (strcmp(cross_arch, "i386") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__loongarch64__)
	if (strcmp(cross_arch, "loongarch64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__m68k__)
	if (strcmp(cross_arch, "m68k") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__microblaze__)
	if (strcmp(cross_arch, "microblaze") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__mips__)
	if (strcmp(cross_arch, "mips") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__mips64__)
	if (strcmp(cross_arch, "mips64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__mips64el__)
	if (strcmp(cross_arch, "mips64el") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__mipsel__)
	if (strcmp(cross_arch, "mipsel") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__mipsn32__)
	if (strcmp(cross_arch, "mipsn32") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__mipsn32el__)
	if (strcmp(cross_arch, "mipsn32el") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__ppc__)
	if (strcmp(cross_arch, "ppc") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__ppc64__)
	if (strcmp(cross_arch, "ppc64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__ppc64le__)
	if (strcmp(cross_arch, "ppc64le") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__riscv32__)
	if (strcmp(cross_arch, "riscv32") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__riscv64__)
	if (strcmp(cross_arch, "riscv64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__s390x__)
	if (strcmp(cross_arch, "s390x") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__sh4__)
	if (strcmp(cross_arch, "sh4") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__sh4eb__)
	if (strcmp(cross_arch, "sh4eb") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__sparc__)
	if (strcmp(cross_arch, "sparc") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__sparc32plus__)
	if (strcmp(cross_arch, "sparc32plus") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__sparc64__)
	if (strcmp(cross_arch, "sparc64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__x86_64__)
	if (strcmp(cross_arch, "x86_64") == 0 || strcmp(cross_arch, "amd64") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__xtensa__)
	if (strcmp(cross_arch, "xtensa") == 0) {
		free(ret);
		return NULL;
	}
#endif
#if defined(__xtensaeb__)
	if (strcmp(cross_arch, "xtensaeb") == 0) {
		free(ret);
		return NULL;
	}
#endif
	if (strcmp(cross_arch, "aarch64") == 0 || strcmp(cross_arch, "arm64") == 0 || strcmp(cross_arch, "armv8") == 0) {
		ret->magic = magicof(aarch64);
		ret->mask = maskof(aarch64);
	} else if (strcmp(cross_arch, "alpha") == 0) {
		ret->magic = magicof(alpha);
		ret->mask = maskof(alpha);
	} else if (strcmp(cross_arch, "arm") == 0 || strcmp(cross_arch, "armhf") == 0 || strcmp(cross_arch, "arm32") == 0 || strcmp(cross_arch, "armel") == 0) {
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
	} else if (strcmp(cross_arch, "x86_64") == 0 || strcmp(cross_arch, "amd64") == 0) {
		ret->magic = magicof(x86_64);
		ret->mask = maskof(x86_64);
	} else if (strcmp(cross_arch, "xtensa") == 0) {
		ret->magic = magicof(xtensa);
		ret->mask = maskof(xtensa);
	} else if (strcmp(cross_arch, "xtensaeb") == 0) {
		ret->magic = magicof(xtensaeb);
		ret->mask = maskof(xtensaeb);
	} else {
		free(ret);
		return NULL;
	}
	log("Cross architecture: {cyan}%s\n", cross_arch);
	log("ELF magic: {cyan}%s\n", ret->magic);
	log("ELF mask: {cyan}%s\n", ret->mask);
	return ret;
}
