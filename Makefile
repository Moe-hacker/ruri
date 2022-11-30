#默认开启安全增强与代码优化选项
all :
	cc -lcap -O3 -z noexecstack -z now -fstack-protector-all -fPIE -pie container.c -o container
clean :
	rm container
