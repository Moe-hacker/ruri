all :
	clang -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -pie -flto container.c -o container
	strip container
no :
	clang -lcap container.c -o container
static :
	clang -static -ffunction-sections -fdata-sections -Wl,--gc-sections -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -flto container.c -o container
	strip container
staticfail :
	clang -static -ffunction-sections -fdata-sections -Wl,--gc-sections -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -flto container.c -o container ./libcap.a
	strip container
install :all
	install -m 777 container ${PREFIX}/bin/moe-container
clean :
	rm container||true
	rm libcap.a||true
help :
	@printf "\033[1;38;2;254;228;208mUsage:\n"
	@echo "  make all        :compile"
	@echo "  make install    :make all and install container to \$$PREFIX"
	@echo "  make static     :static compile"
	@echo "  make staticfail :static compile,fix errors"
	@echo "  make no         :compile without optimizations"
	@echo "  make clean      :clean"
	@echo "Dependent libraries:"
	@echo "  libc-client-static,libcap-static"
	@printf "If you got errors like \`undefined symbol: cap_drop_bound\` or \`undefined reference to \`cap_set_flag' when using static compile,please copy your \`libcap.a\` into current directory and use \`make staticfail\` instead\n\033[0m"
