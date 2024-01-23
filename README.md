
![](https://github.com/Moe-hacker/ruri/raw/main/logo/logo.png)

![](https://img.shields.io/github/stars/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=Google%20Bard&logoColor=fee4d0)
![](https://img.shields.io/github/forks/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=git&logoColor=fee4d0)
![](https://img.shields.io/github/license/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=readme&logoColor=fee4d0)
![](https://img.shields.io/github/repo-size/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)
![](https://img.shields.io/github/last-commit/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)
![](https://img.shields.io/badge/language-c-green?style=for-the-badge&color=fee4d0&logo=Codio&logoColor=fee4d0)
-----
![](https://img.shields.io/badge/tested%20on-my%20machine-fee4d0?style=for-the-badge&color=fee4d0&logo=cachet&logoColor=fee4d0)
![](https://img.shields.io/badge/it%20works-why-fee4d0?style=for-the-badge&color=fee4d0&logo=frontendmentor&logoColor=fee4d0)
![](https://img.shields.io/badge/contain-cats-fee4d0?style=for-the-badge&color=fee4d0&logo=Aiqfome&logoColor=fee4d0)
![](https://img.shields.io/badge/gugu-everyday-fee4d0?style=for-the-badge&color=fee4d0&logo=fluentd&logoColor=fee4d0)
![](https://img.shields.io/badge/powered%20by-water-fee4d0?style=for-the-badge&color=fee4d0&logo=Deluge&logoColor=fee4d0)
![](https://img.shields.io/badge/ages-18%2B-fee4d0?style=for-the-badge&color=fee4d0&logo=erlang&logoColor=fee4d0)

<p align="center">「 须臾水面明月出，沧江万顷瑠璃寒 」</p>

-----------------     
### WARNING:      
```
* Your warranty is void.
* I am not responsible for anything that may happen to your device by using this program.
* You do it at your own risk and take the responsibility upon yourself.
* This program has no Super Cow Powers.
```
### Bug reporting:
> “Bugs will happen, if they don’t happen in hardware, they will happen in software and if they don’t happen in your software and they will happen in somebody else’s software.”      
> --Torvalds

If you think something does not work as expected, please [Open a new isssue](https://github.com/Moe-hacker/ruri/issues)      
### About ruri:         
&emsp;ruri is pronounced as  `luli`, or you can call it `瑠璃` in Chinese or Japanese as well.       
&emsp;ruri is the romaji acronym of Lightweight, User-friendly Linux-container Implementation. It's designed to provide better security for Linux containers on devices that do not support docker.       
- Simple:      
The basic usage is very very simple, you can use it just like the command `chroot`.
- Secure:      
It uses libcap and libseccomp for security, and most devices in /dev will never be reached in containers by default.
- Static:      
Build ruri with `make static`, it will be compiled as a small binary file(~1M), but it can be run anywhere without dependent libraries.      

### Install:      
```
git clone https://github.com/Moe-hacker/ruri
cd ruri
sudo make install
```
### Quick start(with rootfstool):
#### First, download and unpack a rootfs:
```
git clone https://github.com/Moe-hacker/rootfstool
cd rootfstool
./rootfstool download -d alpine -v edge
mkdir /tmp/alpine
sudo tar -xvf rootfs.tar.xz -C /tmp/alpine
```
#### Then:
```
sudo ruri /tmp/alpine
```
For unshare container:      
```
sudo ruri -D
sudo ruri -u /tmp/alpine
```
Very simple as you can see.    
#### For command line examples, please see `ruri -H`
#### make options:
```text
  make all            compile
  make install        install ruri to $PREFIX
  make static         static compile,with musl or glibc
  make static-bionic  static compile,with bionic
  make clean          clean
Only for developers:
  make dev            compile without optimizations, enable gdb debug information and extra logs.
  make asan           enable ASAN
  make check          run clang-tidy
  make format         format code
```
#### Dependent libraries:
For dynamic compilation:         
- libcap       
- libpthread
- libseccomp
     
For static compilation:         
- libcap-static
- libc-static
- libseccomp-static       
### Usage:    
```text
Usage:
  ruri OPTIONS
  ruri [ARGS] CONTAINER_DIRECTORY [COMMAND [ARG]...]

OPTIONS:
  -v                     Show version info
  -V                     Show version code
  -h                     Show helps
  -H                     Show helps and commandline examples
  -D                     Run daemon
  -K                     Kill daemon
  -t                     Check if daemon is running
  -T                     Check if daemon is running (No output)
  -l                     List all running unshare containers
  -U [container_dir]     Umount&kill a container

ARGS:
  -a [arch]              Simulate architecture via binfmt_misc & QEMU, need `-q`
  -q [path]              Specify the path of QEMU
  -u                     Enable unshare feature
  -n                     Set NO_NEW_PRIVS Flag
  -s                     Enable built-in Seccomp profile
  -d                     Drop more capabilities for lower privilege
  -p                     Run privileged container
  -r                     Run rootless container
 --keep [cap]            Keep the specified cap
 --drop [cap]            Drop the specified cap
  -e [env] [value]       Set env to its value *Not work if init command is like `su -`
  -m [dir/dev/img] [dir] Mount dir/block-device/image to mountpoint
  -S                     Bind-mount /dev/, /sys/ and /proc/ from host
  -w                     Disable warnings
```
&emsp;This program should be run with root privileges.        
&emsp;Please unset $LD_PRELOAD before running this program.              
### About runtime dirs:
ruri will create /dev/, /sys/ and /proc/ after chroot(2) into container for better security. You can use `-S` option to force it to bind-mount system runtime dirs.      
### About cross-arch container:
It needs CONFIG_BINFMT_MISC enabled in your kernel config.      
You need to copy qemu-*-static to your container first.      
The path of qemu is the absolute path of qemu binary in the chroot container, for example, you have a qemu binary at `/path/to/container/qemu-amd64-static`, use `-a x86_64 -q /qemu-amd64-static` arguments to start the container.
### About rootless container:
It requires user namespace enabled in your kernel config.      
It's a very useless function. Ruri creates a new user namespace and run chroot(2) in it, but without any real privileges, it can not even mount /proc /dev and /sys.       
Adding CAP_SYS_ADMIN can not fix any problems, so just do not use this function.      
### About Seccomp:
The seccomp rule of ruri is based on Docker's default seccomp profile. ruri does not provide the way to change it, but you can edit src/seccomp.c and replace setup_seccomp() with your own config.      
### About daemon:
The daemon will create a socket file in $TMPDIR/ruri.sock (to be /tmp/ruri.sock on common GNU/Linux) for interprocess communication. This file will be automatically removed after running `ruri -K`.         
### Full User Guide:
See `ruri(1)` in manpage after installation.   
### License:
License of code:      
- Licensed under the MIT License      
- Copyright (c) 2022-2024 Moe-hacker      

License of clang-format config file:      
- GPL-2.0      

```
●●●●  ●   ● ●●●●   ●●●
●   ● ●   ● ●   ●   ● 
●●●●  ●   ● ●●●●    ● 
●  ●  ●   ● ●  ●    ● 
●   ●  ●●●  ●   ●  ●●●
```
--------
<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>          
<p align="center">(>_×)</p>
