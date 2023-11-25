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
# Premature optimization is the root of evil.
#
CCCOLOR     = \033[1;38;2;254;228;208m
STRIPCOLOR  = \033[1;38;2;254;228;208m
BINCOLOR    = \033[34;1m
ENDCOLOR    = \033[0m
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
# Compiler.
CC = clang
# Strip.
STRIP = strip
# Link-Time Optimization.
LTO = -flto
# Position-Independent Executables.
PIE = -fPIE
# No-eXecute.
NX = -z noexecstack
# Relocation Read-Only.
RELRO = -z now
# Stack Canary.
CANARY = -fstack-protector-all
# Stack Clash Protection.
CLASH_PROTECT = -fstack-clash-protection
# Shadow Stack.
SHADOW_STACK = -mshstk
# Fortified Source.
FORTIFY = -D_FORTIFY_SOURCE=3 -Wno-unused-result
# Other "one-key" optimization.
OPTIMIZE = -O2
# For production.
OPTIMIZE_CFLAGS = $(LTO) $(PIE) $(NX) $(RELRO) $(CANARY) $(CLASH_PROTECT) $(SHADOW_STACK) $(AUTO_VAR_INIT) $(FORTIFY) $(OPTIMIZE)
# Static link.
STATIC_CFLAGS = -static
# Dev marco for extra logs.
DEV_MARCO = -D__RURI_DEV__
# GNU Symbolic Debugger.
DEBUGGER = -ggdb
# Disable other optimizations.
NO_OPTIMIZE = -O0 -fno-omit-frame-pointer
# Disable Relocation Read-Only.
NO_RELRO = -z norelro
# Disable No-eXecute.
NO_NX = -z execstack
# Position Independent Executables.
NO_PIE = -no-pie
# Disable Stack Canary.
NO_CANARY = -fno-stack-protector
# Warning Options.
WALL = -Wall -Wextra -pedantic -Wconversion -Wno-newline-eof
# For Testing.
DEV_CFLAGS = $(DEV_MARCO) $(DEBUGGER) $(NO_OPTIMIZE) $(NO_RELRO) $(NO_NX) $(NO_PIE) $(NO_CANARY) $(WALL)
# AddressSanitizer.
ASAN = -fsanitize=address,leak -fsanitize-recover=address,all
# We just compile all files at the same time.
SRC = src/*.c
HEADER = src/include/*.h
BIN_TARGET = ruri
STANDARD = -std=gnu99 -Wno-gnu-zero-variadic-macro-arguments
# For ruri -v.
COMMIT_ID = -DRURI_COMMIT_ID=\"`git log --oneline|head -1|cut -d " " -f 1`\"
# For `make fromat`.
FORMATER = clang-format -i
# For `make check`.
CHECKER = clang-tidy --use-color
# Unused checks are disabled.
CHECKER_FLAGS = --checks=*,-clang-analyzer-security.insecureAPI.strcpy,-altera-unroll-loops,-cert-err33-c,-concurrency-mt-unsafe,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-readability-function-cognitive-complexity,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-bugprone-easily-swappable-parameters
# Link with libcap, libpthread and libseccomp.
LD_FLAGS = -lcap -lpthread -lseccomp
# Fix issues in termux (with bionic).
BIONIC_FIX = -ffunction-sections -fdata-sections -Wl,--gc-sections
# Bionic has built-in libpthread.
LD_FLAGS_BIONIC = -lcap -lseccomp
# Target.
RURI = $(COMMIT_ID) $(STANDARD) $(SRC) -o $(BIN_TARGET)
.PHONY: dev
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
	@$(CC) $(DEV_CFLAGS) $(ASAN) $(RURI) $(LD_FLAGS)
static :mandoc
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) $(LD_FLAGS)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
static-bionic :mandoc
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(BIONIC_FIX) $(RURI) $(LD_FLAGS_BIONIC)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
install :all
	install -m 777 $(BIN_TARGET) ${PREFIX}/bin/$(BIN_TARGET)
	install -m 777 doc/ruri.1.gz `man -w ls|head -1|sed -e "s/ls.*//"`
check :
	@printf "\033[1;38;2;254;228;208mCheck list:\n"
	@sleep 1.5s
	@$(CHECKER) $(CHECKER_FLAGS) --list-checks $(SRC) -- $(DEV_CFLAGS) $(RURI)
	@printf ' \033[1;38;2;254;228;208mCHECK\033[0m \033[34;1m%b\033[0m\n' $(SRC)
	@$(CHECKER) $(CHECKER_FLAGS) $(SRC) -- $(COMMIT_ID) $(RURI)
	@printf ' \033[1;38;2;254;228;208mDONE.\n'
format :
	$(FORMATER) $(SRC) $(HEADER)
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
