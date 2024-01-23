# SPDX-License-Identifier: MIT
#
#
# This file is part of ruri, with ABSOLUTELY NO WARRANTY.
#
# MIT License
#
# Copyright (c) 2022-2024 Moe-hacker
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
LDCOLOR     = \033[1;38;2;254;228;208m
STRIPCOLOR  = \033[1;38;2;254;228;208m
BINCOLOR    = \033[34;1m
ENDCOLOR    = \033[0m
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
LD_LOG = @printf '    $(LDCOLOR)LD$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
CLEAN_LOG = @printf ' $(CCCOLOR)CLEAN$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
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
# For production.
OPTIMIZE_CFLAGS = $(LTO) $(PIE) $(CANARY) $(CLASH_PROTECT) $(SHADOW_STACK) $(AUTO_VAR_INIT) $(FORTIFY) $(OPTIMIZE) $(COMMIT_ID) $(STANDARD)
# Static link.
STATIC_CFLAGS = $(OPTIMIZE_CFLAGS) -static
# For Testing.
DEV_CFLAGS = $(DEV_MARCO) $(DEBUGGER) $(NO_OPTIMIZE) $(NO_CANARY) $(WALL) $(COMMIT_ID) $(STANDARD)
# AddressSanitizer.
ASAN_CFLAGS = $(DEV_CFLAGS) -fsanitize=address,leak -fsanitize-recover=address,all
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
CHECKER_FLAGS = --checks=*,-clang-analyzer-security.insecureAPI.strcpy,-altera-unroll-loops,-cert-err33-c,-concurrency-mt-unsafe,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-readability-function-cognitive-complexity,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-bugprone-easily-swappable-parameters,-cert-err34-c,-misc-include-cleaner,-readability-identifier-length
# Link with libcap, libpthread and libseccomp.
LD_FLAGS = -lcap -lpthread -lseccomp $(NX) $(RELRO)
DEV_LD_FLAGS = -lcap -lpthread -lseccomp $(NO_RELRO) $(NO_NX) $(NO_PIE)
# Fix issues in termux (with bionic).
BIONIC_FIX = -ffunction-sections -fdata-sections
BIONIC_CFLAGS = $(OPTIMIZE_CFLAGS) $(BIONIC_FIX) -static
# Bionic has built-in libpthread.
BIONIC_LD_FLAGS = -lcap -lseccomp -Wl,--gc-sections $(NX) $(RELRO)
# Target.
objects = caplist.o chroot.o daemon.o info.o seccomp.o socket.o tool.o unshare.o elf-magic.o main.o
O = out
.ONESHELL:
all :CFLAGS=$(OPTIMIZE_CFLAGS)
all :build_dir mandoc $(objects)
	@cd $(O)
	@$(CC) $(CFLAGS) -o $(BIN_TARGET) $(objects) $(LD_FLAGS)
	$(LD_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
	$(STRIP_LOG) $(BIN_TARGET)
	@cp -f $(BIN_TARGET) ../
mandoc :
	@gzip -kf doc/ruri.1
dev :CFLAGS=$(DEV_CFLAGS)
dev :build_dir $(objects)
	@cd $(O)
	$(LD_LOG) $(BIN_TARGET)
	@$(CC) $(CFLAGS) -o $(BIN_TARGET) $(objects) $(DEV_LD_FLAGS)
	@cp -f $(BIN_TARGET) ../
asan :CFLAGS=$(ASAN_CFLAGS)
asan :build_dir $(objects)
	@cd $(O)
	$(LD_LOG) $(BIN_TARGET)
	@$(CC) $(CFLAGS) -o $(BIN_TARGET) $(objects) $(DEV_LD_FLAGS)
	@cp -f $(BIN_TARGET) ../
static :CFLAGS=$(STATIC_CFLAGS)
static :build_dir mandoc $(objects)
	@cd $(O)
	$(LD_LOG) $(BIN_TARGET)
	@$(CC) $(CFLAGS) -o $(BIN_TARGET) $(objects) $(LD_FLAGS)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
	@cp -f $(BIN_TARGET) ../
static-bionic :CFLAGS=$(BIONIC_CFLAGS)
static-bionic :build_dir mandoc $(objects)
	@cd $(O)
	$(LD_LOG) $(BIN_TARGET)
	@$(CC) $(CFLAGS) -o $(BIN_TARGET) $(objects) $(BIONIC_LD_FLAGS)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
	@cp -f $(BIN_TARGET) ../
build_dir:
	@mkdir -p $(O)
$(objects) :%.o:src/%.c $(build_dir)
	@cd $(O)
	@$(CC) $(CFLAGS) -Wno-unused-command-line-argument -c ../$< -o $@
	$(CC_LOG) $@
install :all
	install -m 777 $(BIN_TARGET) ${PREFIX}/bin/$(BIN_TARGET)
	install -m 777 doc/ruri.1.gz `man -w ls|head -1|sed -e "s/ls.*//"`
check :
	@printf "\033[1;38;2;254;228;208mCheck list:\n"
	@sleep 1.5s
	@$(CHECKER) $(CHECKER_FLAGS) --list-checks $(SRC) -- $(DEV_CFLAGS)
	@printf ' \033[1;38;2;254;228;208mCHECK\033[0m \033[34;1m%b\033[0m\n' $(SRC)
	@$(CHECKER) $(CHECKER_FLAGS) $(SRC) -- $(COMMIT_ID)
	@printf ' \033[1;38;2;254;228;208mDONE.\n'
format :
	$(FORMATER) $(SRC) $(HEADER)
clean :
	$(CLEAN_LOG) $(BIN_TARGET)
	@rm -f $(BIN_TARGET)||true
	$(CLEAN_LOG) $(O)
	@rm -rf $(O)||true
	$(CLEAN_LOG) peda*
	@rm -f peda*
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
