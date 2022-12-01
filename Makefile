all :
	cc -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -pie container.c -o container
	strip container
no :
	cc -lcap container.c -o container
static :
	cc -static -ffunction-sections -fdata-sections -Wl,--gc-sections -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE container.c -o container
	strip container
staticfail :
	cc -static -ffunction-sections -fdata-sections -Wl,--gc-sections -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE container.c -o container ./libcap.a
	strip container
clean :
	rm container||true
	rm libcap.a||true
help :
	@printf "\033[1;38;2;166;227;161mUsage:\n"
	@echo "  make all        :compile"
	@echo "  make static     :static compile"
	@echo "  make staticfail :static compile,fix errors"
	@echo "  make no         :compile without optimizations"
	@echo "  make clean      :clean"
	@echo "Dependent libraries:"
	@echo "  libc-client-static,libcap-static"
	@printf "If you got errors like \`undefined symbol: cap_drop_bound\` or \`undefined reference to \`cap_set_flag' when using static compile,please copy your \`libcap.a\` into current directory and use \`make staticfail\` instead\n\033[0m"
