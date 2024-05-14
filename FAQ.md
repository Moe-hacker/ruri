# About config:
Since v3.0, ruri can use [k2v](https://github.com/Moe-hacker/libk2v), a new simple config format, to store the config of a container.          
# About rurienv:
Since v3.0, ruri removed the daemon, it use a new way to store the info of a running container.         
ruri will creat `/.rurienv` file into the container, to store runtime info of container.          
The rurienv file is automatically controled by ruri, please do not edit it.      
# About tty:      
The command `tty` in ruri might say that "not a tty".      
If you need to run some program like `gpg`, please use `script -q -O /dev/null` in container.      
# About runtime dirs:
ruri will create /dev/, /sys/ and /proc/ after chroot(2) into container for better security. You can use `-S` option to force it to bind-mount system runtime dirs.      
# About multi-arch container:
Yes, you can run multi-arch containers via ruri if your device support.      
It needs CONFIG_BINFMT_MISC enabled in your kernel config.      
You need to copy qemu-*-static to your container first.      
The path of qemu is the absolute path of qemu binary in the chroot container, for example, you have a qemu binary at `/path/to/container/qemu-amd64-static`, use `-a x86_64 -q /qemu-amd64-static` arguments to start the container.
# About rootless container:
WIP      
# About Seccomp:
The seccomp rule of ruri is based on Docker's default seccomp profile. ruri does not provide the way to change it, but you can edit src/seccomp.c and replace setup_seccomp() with your own config.      