
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
# About v3.0:
V3.0 contains some breaking changes, please read the changelog, and help page in `ruri -h` if you are upgrading from v2.x.        
# WARNING:      
```
* Your warranty is void.
* I am not responsible for anything that may happen to your device by using this program.
* You do it at your own risk and take the responsibility upon yourself.
* This program has no Super Cow Powers.
```
# SECURITY WARNING:
ruri should always be executed with root privileges(sudo), and do not set SUID or any capability on it!      
# Bug reporting:
> “Bugs will happen, if they don’t happen in hardware, they will happen in software and if they don’t happen in your software and they will happen in somebody else’s software.”      
> --Torvalds

If you think something does not work as expected, please [Open a new isssue](https://github.com/Moe-hacker/ruri/issues)      
# About:         
&emsp;ruri is pronounced as  `luli`, or you can call it `瑠璃` in Chinese or Japanese as well.       
&emsp;ruri is the romaji acronym of Lightweight, User-friendly Linux-container Implementation. It's designed to provide better security for Linux containers on devices that do not support docker.       
- Simple:      
The basic usage is very very simple, you can use it just like the command `chroot`.
- Secure:      
It uses libcap and libseccomp for security, and most devices in /dev will never be reached in containers by default.
- Run Everywhere:      
Build ruri with `make static`, it will be compiled as a small binary file(~1M), but it can be run anywhere without dependent libraries.      

# Install:      
```
git clone https://github.com/Moe-hacker/ruri
cd ruri
sudo make install
```
# Build options:
See `make help`.      

# Usage:    
See `ruri -h`
# Quick start(with rootfstool):
## Download and unpack a rootfs:
```
git clone https://github.com/Moe-hacker/rootfstool
cd rootfstool
./rootfstool download -d alpine -v edge
mkdir /tmp/alpine
sudo tar -xvf rootfs.tar.xz -C /tmp/alpine
```
## Then:
```
sudo ruri /tmp/alpine
```
For unshare container:      
```
sudo ruri -u /tmp/alpine
```
Very simple as you can see.    
For command line examples, please see `ruri -H`.      
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
# About cross-arch container:
It needs CONFIG_BINFMT_MISC enabled in your kernel config.      
You need to copy qemu-*-static to your container first.      
The path of qemu is the absolute path of qemu binary in the chroot container, for example, you have a qemu binary at `/path/to/container/qemu-amd64-static`, use `-a x86_64 -q /qemu-amd64-static` arguments to start the container.
# About rootless container:
It requires user namespace enabled in your kernel config.      
It's a very useless function. Ruri creates a new user namespace and run chroot(2) in it, but without any real privileges, it can not even mount /proc /dev and /sys.       
Adding CAP_SYS_ADMIN can not fix any problems, so just do not use this function.      
# About Seccomp:
The seccomp rule of ruri is based on Docker's default seccomp profile. ruri does not provide the way to change it, but you can edit src/seccomp.c and replace setup_seccomp() with your own config.      
# License:
License of code:      
- Licensed under the MIT License      
- Copyright (c) 2022-2024 Moe-hacker      

License of clang-format config file:      
- GPL-2.0      
--------
<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>          
<p align="center">(>_×)</p>
