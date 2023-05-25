include rule.make
CC = clang
OPTIONS = -lcap -lpthread
RURI = ruri.c -o ruri
BIN = ruri

all :
	$(CC) $(OPTIONS) -O3 -z noexecstack -z now -fstack-protector-all -fPIE -pie $(RURI) 
	strip ruri
dev :
	$(CC) $(OPTIONS) -ggdb -Wall -Wextra -D__CONTAINER_DEV__ $(RURI)
static :
# The first command is for ubuntu-amd64 and the other is for termux.
# Compilation can be completed by successfully executing any of the two commands.
	$(CC) $(OPTIONS) -static -ffunction-sections -fdata-sections -Wl,--gc-sections -O3 -z noexecstack -z now -fstack-protector-all -fPIE ruri.c -o ruri `pkg-config --variable=libdir libcap`/libcap.a 2>/dev/null||clang -static -ffunction-sections -fdata-sections -Wl,--gc-sections -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE $(RURI) 
	strip ruri
install :all
	install -m 777 ruri ${PREFIX}/bin/ruri
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
