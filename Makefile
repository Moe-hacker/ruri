all :
	cc -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -pie container.c -o container
	strip container
static :
	cc -static -ffunction-sections -fdata-sections -Wl,--gc-sections -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE container.c -o container
	strip container
clean :
	rm container
