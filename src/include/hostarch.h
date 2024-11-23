/*
 * This header contains no copyrightable information.
 */
#if defined(__aarch64__)
#define RURI_HOST_ARCH "aarch64"
#endif
#if defined(__alpha__)
#define RURI_HOST_ARCH "alpha"
#endif
#if defined(__arm__)
#define RURI_HOST_ARCH "arm"
#endif
#if defined(__armeb__)
#define RURI_HOST_ARCH "armeb"
#endif
#if defined(__cris__)
#define RURI_HOST_ARCH "cris"
#endif
#if defined(__hexagon__)
#define RURI_HOST_ARCH "hexagon"
#endif
#if defined(__hppa__)
#define RURI_HOST_ARCH "hppa"
#endif
#if defined(__i386__)
#define RURI_HOST_ARCH "i386"
#endif
#if defined(__loongarch64__)
#define RURI_HOST_ARCH "loongarch64"
#endif
#if defined(__m68k__)
#define RURI_HOST_ARCH "m68k"
#endif
#if defined(__microblaze__)
#define RURI_HOST_ARCH "microblaze"
#endif
#if defined(__mips__)
#define RURI_HOST_ARCH "mips"
#endif
#if defined(__mips64__)
#define RURI_HOST_ARCH "mips64"
#endif
#if defined(__mips64el__)
#define RURI_HOST_ARCH "mips64el"
#endif
#if defined(__mipsel__)
#define RURI_HOST_ARCH "mipsel"
#endif
#if defined(__mipsn32__)
#define RURI_HOST_ARCH "mipsn32"
#endif
#if defined(__mipsn32el__)
#define RURI_HOST_ARCH "mipsn32el"
#endif
#if defined(__ppc__)
#define RURI_HOST_ARCH "ppc"
#endif
#if defined(__ppc64__)
#define RURI_HOST_ARCH "ppc64"
#endif
#if defined(__ppc64le__)
#define RURI_HOST_ARCH "ppc64le"
#endif
#if defined(__riscv32__)
#define RURI_HOST_ARCH "riscv32"
#endif
#if defined(__riscv64__)
#define RURI_HOST_ARCH "riscv64"
#endif
#if defined(__s390x__)
#define RURI_HOST_ARCH "s390x"
#endif
#if defined(__sh4__)
#define RURI_HOST_ARCH "sh4"
#endif
#if defined(__sh4eb__)
#define RURI_HOST_ARCH "sh4eb"
#endif
#if defined(__sparc__)
#define RURI_HOST_ARCH "sparc"
#endif
#if defined(__sparc32plus__)
#define RURI_HOST_ARCH "sparc32plus"
#endif
#if defined(__sparc64__)
#define RURI_HOST_ARCH "sparc64"
#endif
#if defined(__x86_64__)
#define RURI_HOST_ARCH "x86_64"
#endif
#if defined(__xtensa__)
#define RURI_HOST_ARCH "xtensa"
#endif
#if defined(__xtensaeb__)
#define RURI_HOST_ARCH "xtensaeb"
#endif
#if !defined(RURI_HOST_ARCH)
#define RURI_HOST_ARCH "unknown"
#endif