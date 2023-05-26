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
SRC = ruri.c
BIN = ruri
RURI = $(SRC) -o $(BIN)
all :
	@$(CC) $(OPTIMIZE_CFLAGS) -pie $(RURI) $(LD_FLAGS)
	$(CC_LOG) $(BIN)
	@$(STRIP) $(BIN)
	$(STRIP_LOG) $(BIN)
dev :
	$(CC) -ggdb -Wall -Wextra -D__CONTAINER_DEV__ $(RURI) $(LD_FLAGS)
static :
# The first command is for ubuntu-amd64 and the other is for termux.
# Compilation can be completed by successfully executing any of the two commands.
	@$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) $(LD_FLAGS) -L`pkg-config --variable=libdir libcap` 2>/dev/null||$(CC) $(STATIC_CFLAGS) $(OPTIMIZE_CFLAGS) $(RURI) -lcap 
	$(CC_LOG) $(BIN)
	@$(STRIP) $(BIN)
	$(STRIP_LOG) $(BIN)
install :all
	install -m 777 $(BIN) ${PREFIX}/bin/$(BIN)
clean :
	rm ruri||true
help :
	@printf "\033[1;38;2;254;228;208mUsage:\n"
	@echo "  make all        :compile"
	@echo "  make install    :install ruri to \$$PREFIX"
	@echo "  make static     :static compile"
	@echo "  make clean      :clean"
	@echo "Only for developer:"
	@echo "  make dev        :compile without optimizations, enable gdb debug information and extra logs."
	@echo "*Premature optimization is the root of all evil."
	@echo "Dependent libraries:"
	@echo "  libpthread,libcap"
