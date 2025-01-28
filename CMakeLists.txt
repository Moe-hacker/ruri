cmake_minimum_required(VERSION 3.10)

# set the project name
project(ruri LANGUAGES C)

# Check for header
include(CheckIncludeFile)

execute_process(
    COMMAND date "+%Y-%m-%d"
    OUTPUT_VARIABLE CMAKE_CURRENT_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND date "+%H:%M:%S"
    OUTPUT_VARIABLE CMAKE_CURRENT_TIME
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions(-DBUILD_DATE="${CMAKE_CURRENT_DATE}")
add_definitions(-DBUILD_TIME="${CMAKE_CURRENT_TIME}")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    message(STATUS "Using ccache: ${CCACHE_FOUND}")
else()
    message(STATUS "Ccache not found. Compiling with cache will be disabled.")
endif(CCACHE_FOUND)

check_include_file("time.h" HAVE_TIME_H)
check_include_file("grp.h" HAVE_GRP_H)
check_include_file("fcntl.h" HAVE_FCNTL_H)
check_include_file("sys/ioctl.h" HAVE_SYS_IOCTL_H)
check_include_file("sys/mount.h" HAVE_SYS_MOUNT_H)
check_include_file("sys/socket.h" HAVE_SYS_SOCKET_H)
check_include_file("linux/fs.h" HAVE_LINUX_FS_H)
check_include_file("linux/version.h" HAVE_LINUX_VERSION_H)
check_include_file("linux/sched.h" HAVE_LINUX_SCHED_H)
check_include_file("sys/capability.h" HAVE_SYS_CAPABILITY_H)
check_include_file("seccomp.h" HAVE_SECCOMP_H)
check_include_file("pthread.h" HAVE_PTHREAD_H)

# Check for headers
if(NOT HAVE_TIME_H)
    message(FATAL_ERROR "Missing required header: time.h")
endif()
if(NOT HAVE_GRP_H)
    message(FATAL_ERROR "Missing required header: grp.h")
endif()
if(NOT HAVE_FCNTL_H)
    message(FATAL_ERROR "Missing required header: fcntl.h")
endif()
if(NOT HAVE_SYS_IOCTL_H)
    message(FATAL_ERROR "Missing required header: sys/ioctl.h")
endif()
if(NOT HAVE_SYS_MOUNT_H)
    message(FATAL_ERROR "Missing required header: sys/mount.h")
endif()
if(NOT HAVE_SYS_SOCKET_H)
    message(FATAL_ERROR "Missing required header: sys/socket.h")
endif()
if(NOT HAVE_LINUX_FS_H)
    message(FATAL_ERROR "Missing required header: linux/fs.h")
endif()
if(NOT HAVE_LINUX_VERSION_H)
    message(FATAL_ERROR "Missing required header: linux/version.h")
endif()
if(NOT HAVE_LINUX_SCHED_H)
    message(FATAL_ERROR "Missing required header: linux/sched.h")
endif()
if(NOT HAVE_SYS_CAPABILITY_H)
    message(FATAL_ERROR "Missing required header: sys/capability.h")
endif()
if(NOT HAVE_SECCOMP_H)
    message(FATAL_ERROR "Missing required header: seccomp.h")
endif()
if(NOT HAVE_PTHREAD_H)
    message(FATAL_ERROR "Missing required header: pthread.h")
endif()

# Search for libs
find_library(CAP_LIBRARY cap)
find_library(SECCOMP_LIBRARY seccomp)
find_library(PTHREAD_LIBRARY pthread)

# Check dependent library
if(NOT CAP_LIBRARY)
    message(FATAL_ERROR "libcap is required")
endif()

if(NOT SECCOMP_LIBRARY)
    message(FATAL_ERROR "libseccomp is required")
endif()

if(NOT PTHREAD_LIBRARY)
    message(FATAL_ERROR "pthread is required")
endif()

# Set default CFLAGS and LDFLAGS
set(CFLAGS_LIST
    "-flto=auto"
    "-pie"
    "-fstack-protector-all"
    "-fdata-sections"
    "-fno-omit-frame-pointer"
    "-fno-stack-protector"
    "-ftrivial-auto-var-init=pattern"
    "-fstack-clash-protection"
    "-Wno-unused-result"
    "-mshstk"
    "-ffunction-sections"
    "-Wl,--gc-sections"
    "-Wl,--strip-all"
    "-Wl,--disable-new-dtags"
    "-Wl,--build-id=sha1"
    "-Wl,-z,norelro"
    "-Wl,-z,execstack"
    "-Wall"
    "-Wextra"
    "-Wconversion"
    "-pedantic"
    "-pipe"
)

foreach(flag IN LISTS CFLAGS_LIST)
    try_compile(result ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/test/check_flag.c COMPILE_DEFINITIONS ${flag})
    if(result)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
        message(STATUS "Compiler supports flag: ${flag}")
    else()
        message(WARNING "Compiler does not support flag: ${flag}")
    endif()
endforeach()

set(LDFLAGS "-Wl,-z,relro -Wl,-z,noexecstack -Wl,-z,now")

option(ENABLE_DEBUG "Enable debug build" OFF)
option(ENABLE_STATIC "Enable static linking" OFF)
option(BUILD_LIB "BUILD with lib" OFF)

# For Debug build
if(ENABLE_DEBUG)
    message(WARNING "Warning: DEBUG mode is enabled")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0 -DDEBUG_BUILD -DRURI_DEBUG -DRURI_DEV")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -DNDEBUG")
endif()

# For static build
if(ENABLE_STATIC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

# Add LDFLAGS
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions(-DRURI_COMMIT_ID="${GIT_COMMIT_ID}")

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/easteregg/*.c)

if (BUILD_LIB)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    add_library(ruri SHARED ${SOURCES})
    install (TARGETS ruri DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/usr/lib/)
else ()
# add the executable
    set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")
    add_executable(ruri ${SOURCES})
    add_custom_command(
        TARGET ruri
        POST_BUILD
        COMMAND strip ruri
        VERBATIM
        )
        install (TARGETS ruri DESTINATION /usr/bin/)
endif()

# on linux clang 14
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if (ENABLE_STATIC)
        target_link_libraries(ruri -lcap -lseccomp)
    else()
        find_library(LCAP cap)
        find_library(LSECCOMP seccomp)
        target_link_libraries(ruri ${LCAP} ${LSECCOMP})
    endif()
endif()
