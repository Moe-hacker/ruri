CCCOLOR     = \033[34m
STRIPCOLOR  = \033[34;1m
SRCCOLOR    = \033[33m
BINCOLOR    = \033[37;1m
ENDCOLOR    = \033[0m
CC_LOG = @printf '    $(CCCOLOR)CC$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
STRIP_LOG = @printf ' $(STRIPCOLOR)STRIP$(ENDCOLOR) $(BINCOLOR)%b$(ENDCOLOR)\n'
CC = clang
STRIP = strip
LD_FLAGS = -lcap -lpthread
OPTIMIZE_CFLAGS = -O3 -z noexecstack -z now -fstack-protector-all -fPIE
STATIC_CFLAGS = -static -ffunction-sections -fdata-sections -Wl,--gc-sections
DEV_CFLAGS = -ggdb -Wall -Wextra -fno-stack-protector -fno-omit-frame-pointer -D__CONTAINER_DEV__
ASAN_CFLAGS = -no-pie -O0 -fsanitize=undefined -fsanitize-recover=address,all
SRC = ruri.c
BIN_TARGET = ruri
RURI = $(SRC) -o $(BIN_TARGET)
all :
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(OPTIMIZE_CFLAGS) $(RURI) $(LD_FLAGS)
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
dev :
	$(CC) $(DEV_CFLAGS) $(RURI) $(LD_FLAGS)
asan :
	$(CC) $(DEV_CFLAGS) $(ASAN_CFLAGS) $(RURI) $(LD_FLAGS)
static :
# The first command is for ubuntu-amd64 and the other is for termux.
# Compilation can be completed by successfully executing any of the two commands.
	$(CC_LOG) $(BIN_TARGET)
	@$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) $(LD_FLAGS) -L`pkg-config --variable=libdir libcap` 2>/dev/null||$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) -lcap
	$(STRIP_LOG) $(BIN_TARGET)
	@$(STRIP) $(BIN_TARGET)
install :all
	install -m 777 $(BIN_TARGET) ${PREFIX}/bin/$(BIN_TARGET)
clean :
	rm ruri||true
help :
	@printf "\033[1;38;2;254;228;208mUsage:\n"
	@echo "  make all        :compile"
	@echo "  make install    :install ruri to \$$PREFIX"
	@echo "  make static     :static compile"
	@echo "  make clean      :clean"
	@echo "Only for testing:"
	@echo "  make dev        :compile without optimizations, enable gdb debug information and extra logs."
	@echo "  make asan       :enable ASAN"
	@echo "*Premature optimization is the root of all evil."
	@echo "Dependent libraries:"
	@echo "  libpthread,libcap"
