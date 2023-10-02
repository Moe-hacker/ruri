# SPDX-License-Identifier: MIT
#
#
# This file is part of ruri, with ABSOLUTELY NO WARRANTY.
#
# MIT License
#
# Copyright (c) 2022-2023 Moe-hacker
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#
CCCOLOR     = \033[1;38;2;254;228;208m
STRIPCOLOR  = \033[1;38;2;254;228;208m
BINCOLOR    = \033[34;1m
ENDCOLOR    = \033[0m
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
FORMATER = clang-format -i
CC = clang
STRIP = strip
CHECKER = clang-tidy --use-color
CHECK_ARG = --checks=*,-clang-analyzer-security.insecureAPI.strcpy,-altera-unroll-loops,-cert-err33-c,-concurrency-mt-unsafe,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-readability-function-cognitive-complexity,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-misc-no-recursion,-bugprone-easily-swappable-parameters,-readability-identifier-length,-cert-err34-c,-bugprone-assignment-in-if-condition,-altera*
LD_FLAGS = -lcap -lpthread -lseccomp
OPTIMIZE_CFLAGS = -O3 -z noexecstack -z now -ftrivial-auto-var-init=pattern -Wl,-z,relro,-z,now -fstack-clash-protection -fstack-protector-all -fPIE -DRURI_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"
STATIC_CFLAGS = -static -ffunction-sections -fdata-sections -Wl,--gc-sections
DEV_CFLAGS = -ggdb -Wall -Wextra -fno-stack-protector -fno-omit-frame-pointer -D__RURI_DEV__ -DRURI_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"
ASAN_CFLAGS = -no-pie -O0 -fsanitize=address,leak -fsanitize-recover=address,all
SRC = src/main.c src/pstree.c src/seccomp.c src/shared.c src/caplist.c src/socket.c src/daemon.c src/chroot.c src/unshare.c src/tool.c src/cgroup.c
HEADER = src/ruri.h
BIN_TARGET = ruri
RURI = $(SRC) -o $(BIN_TARGET)
all :mandoc
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(OPTIMIZE_CFLAGS) $(RURI) $(LD_FLAGS)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
mandoc :
	@gzip -kf doc/ruri.1
dev :
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(DEV_CFLAGS) $(RURI) $(LD_FLAGS)
asan :
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(DEV_CFLAGS) $(ASAN_CFLAGS) $(RURI) $(LD_FLAGS)
static :mandoc
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) $(LD_FLAGS)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
static-bionic :mandoc
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) -lcap -lseccomp
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
install :all
	install -m 777 $(BIN_TARGET) ${PREFIX}/bin/$(BIN_TARGET)
	install -m 777 doc/ruri.1.gz `man -w ls|head -1|sed -e "s/ls.*//"`
check :
	@printf "\033[1;38;2;254;228;208mCheck list:\n"
	@sleep 1.5s
	@$(CHECKER) $(CHECK_ARG) --list-checks $(SRC) -- $(DEV_CFLAGS) $(RURI) $(LD_FLAGS)  -DRURI_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"
	@printf ' \033[1;38;2;254;228;208mCHECK\033[0m \033[34;1m%b\033[0m\n' $(SRC)
	@$(CHECKER) $(CHECK_ARG) $(SRC) -- $(LD_FLAGS)  -DRURI_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"
	@printf ' \033[1;38;2;254;228;208mDONE.\n'
format :
	$(FORMATER) $(SRC)
	$(FORMATER) $(HEADER)
clean :
	rm ruri||true
help :
	@printf "\033[1;38;2;254;228;208mUsage:\n"
	@echo "  make all            compile"
	@echo "  make install        install ruri to \$$PREFIX"
	@echo "  make static         static compile,with musl or glibc"
	@echo "  make static-bionic  static compile,with bionic"
	@echo "  make clean          clean"
	@echo "Only for developers:"
	@echo "  make dev            compile without optimizations, enable gdb debug information and extra logs."
	@echo "  make asan           enable ASAN"
	@echo "  make check          run clang-tidy"
	@echo "  make format         format code"
	@echo "*Premature optimization is the root of all evil."
	@echo "Dependent libraries:"
	@echo "  libpthread,libcap,libseccomp"
