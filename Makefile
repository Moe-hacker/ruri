all :
	cc -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -pie container.c -o container
clean :
	rm container
