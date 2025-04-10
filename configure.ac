# SPDX-License-Identifier: MIT
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([ruri],[3.8],[moe-hacker@crack.moe])
PS4='+ [DEBUG] ${BASH_SOURCE}:${LINENO}: '
export PS4
AC_PROG_CC
AM_INIT_AUTOMAKE
AC_C_BIGENDIAN
m4_pattern_allow([AC_CHECK_LDFLAGS])
AM_MAINTAINER_MODE
AC_PROG_MAKE_SET
PKG_PROG_PKG_CONFIG
AC_CHECK_SIZEOF(char)
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(void *)
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_SYS_LARGEFILE
AC_CHECK_SIZEOF(off_t)
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE
AC_FUNC_STAT
AC_FUNC_FORK
AC_FUNC_LSTAT
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_OFF_T
AC_CHECK_SIZEOF(off_t, 4)
AC_PROG_INSTALL
AC_C_PROTOTYPES
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

dnl Give error and exit if we dont have pkgconfig
if test "x$PKG_CONFIG" = "x"; then
  AC_MSG_ERROR([you need to have pkgconfig installed!])
fi
# REQUIRE a standard (ANSI/ISO) C compiler
if test "$ac_cv_prog_cc_stdc" = no; then
	AC_MSG_ERROR([A standard (ANSI/ISO C89) C compiler is required.])
fi

gl_cv_func_printf_directive_n=yes
gl_cv_func_printf_infinite_long_double=yes
gl_cv_func_printf_long_double=yes
gl_cv_func_snprintf_directive_n=yes
gl_cv_glob_lists_symlinks=yes

dnl Internationalization macros.
AM_CONDITIONAL(USE_NLS, test x$USE_NLS = xyes)
# Define AC_CHECK_CFLAGS macro
AC_DEFUN([AC_CHECK_CFLAGS], [
    AC_MSG_CHECKING([whether $1 is supported])
    save_CFLAGS=$CFLAGS
    CFLAGS="$CFLAGS $1"
    AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([], [])],
        [AC_MSG_RESULT([yes])],
        [AC_MSG_RESULT([no]); CFLAGS=$save_CFLAGS]
    )
])

AC_CONFIG_SRCDIR([src/ruri.c])
AC_CONFIG_HEADERS([config.h])

# Check for programs
AC_PROG_MAKE_SET
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
# Initialize supported flags variables
SUPPORTED_CFLAGS=""
SUPPORTED_LDFLAGS=""

# Check strip and upx
AC_CHECK_TOOL([STRIP], [strip], [no])
AC_CHECK_PROG([UPX], [upx], [upx], [no])
AM_CONDITIONAL([ENABLE_STRIP], [test "x$STRIP" != "xno"])
AM_CONDITIONAL([ENABLE_UPX], [test "x$UPX" != "xno"])

if test "x$STRIP" != "xno"; then
    AC_MSG_NOTICE([STRIP detected, enabling binary stripping.])
else
    AC_MSG_NOTICE([STRIP not found, skipping binary stripping.])
fi

if test "x$UPX" != "xno"; then
    AC_MSG_NOTICE([UPX detected, enabling binary compression.])
else
    AC_MSG_NOTICE([UPX not found, skipping binary compression.])
fi

# Check for required headers
AC_CHECK_HEADERS([time.h grp.h fcntl.h sys/ioctl.h sys/mount.h sys/socket.h sys/wait.h linux/fs.h linux/version.h linux/sched.h], [], AC_MSG_ERROR([Missing required headers in standard C library.]))

# Enable optional flags
CFLAGS_LIST="-flto=auto -fPIE -pie -fstack-protector-all -fdata-sections -fno-omit-frame-pointer -fno-stack-protector -ftrivial-auto-var-init=pattern -fstack-clash-protection -Wno-unused-result -mshstk -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--strip-all -Wl,--disable-new-dtags -Wl,--build-id=sha1 -Wl,-z,norelro -Wl,-z,execstack -Wall -Wextra -Wconversion -pedantic -pipe"
LDFLAGS_LIST="-pipe -Wl,-z,relro -Wl,-z,noexecstack -Wl,-z,now"

# Handle optional flags for debug and static builds
AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug], [Enable debug build]),
    [if test "x$enable_debug" = "xyes"; then CFLAGS="$CFLAGS  -g3 -O0 -DDEBUG_BUILD -DRURI_DEBUG -DRURI_DEV" && AC_MSG_NOTICE([Warning: DEBUG mode is enabled.]) && CFLAGS_LIST="$CFLAGS_LIST -g3 -O0 -DDEBUG_BUILD -DRURI_DEBUG -DRURI_DEV"; else CFLAGS="$CFLAGS -O3 -g0 -DNDEBUG" && CFLAGS_LIST="$CFLAGS_LIST -O3 -g0 -DNDEBUG"; fi])
    AM_CONDITIONAL([ENABLE_DEBUG], [test "x$enable_debug" = "xyes"])
AC_ARG_ENABLE([static],
    AS_HELP_STRING([--enable-static], [Enable static linking]),
    [if test "x$enable_static" = "xyes"; then LDFLAGS="$LDFLAGS -static"; fi])
# Option to disable libseccomp
AC_ARG_ENABLE([libseccomp],
    AS_HELP_STRING([--disable-libseccomp], [Disable libseccomp support]),
    [], [enable_libseccomp=yes])

# Option to disable libcap
AC_ARG_ENABLE([libcap],
    AS_HELP_STRING([--disable-libcap], [Disable libcap support]),
    [], [enable_libcap=yes])

# Option to disable rurienv
AC_ARG_ENABLE([rurienv],
    AS_HELP_STRING([--disable-rurienv], [Disable .rurienv support]),
    [], [enable_rurienv=yes])

# Replace the existing library checks with these conditional versions
# Check for libseccomp
AS_IF([test "x$enable_libseccomp" = "xyes"], [
    AC_CHECK_HEADERS([seccomp.h], [], [AC_MSG_ERROR([seccomp.h header not found])])
    AC_SEARCH_LIBS([seccomp_init], [seccomp], [], 
        [AC_MSG_ERROR([libseccomp is required unless --disable-libseccomp is used])])
], [
    AC_DEFINE([DISABLE_LIBSECCOMP], [1], [Define to 1 if libseccomp support is disabled])
])

# Check for libcap
AS_IF([test "x$enable_libcap" = "xyes"], [
    AC_CHECK_HEADERS([sys/capability.h], [], [AC_MSG_ERROR([sys/capability.h header not found])])
    AC_SEARCH_LIBS([cap_init], [cap], [], 
        [AC_MSG_ERROR([libcap is required unless --disable-libcap is used])])
], [
    AC_DEFINE([DISABLE_LIBCAP], [1], [Define to 1 if libcap support is disabled])
])

# Add rurienv conditional define
AS_IF([test "x$enable_rurienv" != "xyes"], [
    AC_DEFINE([DISABLE_RURIENV], [1], [Define to 1 if rurienv support is disabled])
])

# Check CFLAGS
AC_MSG_CHECKING([whether the following CFLAGS are supported])
# Check compiler flags
AC_MSG_NOTICE([Checking compiler flag support...])
for flag in $CFLAGS_LIST; do
    save_CFLAGS="$CFLAGS"
    AC_MSG_CHECKING([whether $CC supports $flag])
    CFLAGS="$CFLAGS $flag"
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM()],
        [AC_MSG_RESULT([yes])
         SUPPORTED_CFLAGS="$SUPPORTED_CFLAGS $flag"],
        [AC_MSG_RESULT([no])
         CFLAGS="$save_CFLAGS"])
done

# Check linker flags
AC_MSG_NOTICE([Checking linker flag support...])
for flag in $LDFLAGS_LIST; do
    save_LDFLAGS="$LDFLAGS"
    AC_MSG_CHECKING([whether the linker accepts $flag])
    LDFLAGS="$LDFLAGS $flag"
    AC_LINK_IFELSE([AC_LANG_PROGRAM()],
        [AC_MSG_RESULT([yes])
         SUPPORTED_LDFLAGS="$SUPPORTED_LDFLAGS $flag"],
        [AC_MSG_RESULT([no])
         LDFLAGS="$save_LDFLAGS"])
done

# Apply supported flags
CFLAGS="$SUPPORTED_CFLAGS"
LDFLAGS="$SUPPORTED_LDFLAGS"

if test "$CC" = "tcc"; then
    AC_DEFINE([__VERSION__], ["TinyCC"], ["1"])
    AC_DEFINE([__TIMESTAMP__], ["unknown"], ["1"])
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

dnl ==========================================================================
echo "
Configure summary:

    ${PACKAGE_STRING}
    `echo $PACKAGE_STRING | sed "s/./=/g"`

    prefix:                       ${prefix}
    source code location:         ${srcdir}
    compiler:                     ${CC}
    compiler flags:               ${CFLAGS}
    linker flags:                 ${LDFLAGS}
"
