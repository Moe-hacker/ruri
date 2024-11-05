
![](https://github.com/Moe-hacker/ruri/raw/main/logo/logo.png)

-----

<p align="center">「 须臾水面明月出，沧江万顷瑠璃寒 」</p>

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14021121.svg)](https://doi.org/10.5281/zenodo.14021121)
-----------------     
# Download:    
You can get ruri binary (statically linked) for arm64, armv7, armhf, riscv64, i386, loong64, s390x, ppc64le and x86_64 devices in [Release](https://github.com/Moe-hacker/ruri/releases/).      
Or you can run the following command to download ruri automatically:      
```sh
wget https://github.com/Moe-hacker/ruri/raw/refs/heads/main/getruri.sh
bash getruri.sh -s
```
This will automatically download ruri binary to `./ruri`.      
# 中文文档
[中文文档](doc/README_zh.md)      
# WARNING:      
> [!WARNING]
> ruri should always be executed with root privileges(sudo), and do not set SUID or any capability on it!      
```
* Your warranty is void.
* I am not responsible for anything that may happen to your device by using this program.
* You do it at your own risk and take the responsibility upon yourself.
* This program has no Super Cow Powers.
```
# Bug reporting:
> “Bugs will happen, if they don’t happen in hardware, they will happen in software and if they don’t happen in your software and they will happen in somebody else’s software.”      
> --Torvalds

If you think something does not work as expected, please [Open a new isssue](https://github.com/Moe-hacker/ruri/issues)      
# About:         
&emsp;ruri is pronounced as  `luli`, or you can call it `瑠璃` in Chinese or Japanese as well.       
&emsp;ruri is acronym to Lightweight, User-friendly Linux-container Implementation. It's designed to provide better security for Linux containers on devices that do not support docker.       
- Simple:      
The basic usage is very very simple, you can use it just like the command `chroot`.
- Secure:      
Ruri focus on security, with many built-in protections.
- Run Everywhere:      
ruri officially supports multipe platforms: arm64, armv7, armhf, riscv64, i386, loong64, s390x, ppc64le and x86_64.         
The ruri binary is very small, only about 1M, and you can also use `upx` to make it less than 500k, so it can be run anywhere even if the storage is tight.                
# Container Security:  
See [Enhance Container Security](doc/Security.md).      
# Build:      
```
git clone https://github.com/Moe-hacker/ruri
cd ruri
./configure -s
make
sudo cp ruri /usr/bin/ruri
```
# Build options:
```
Usage: ./configure [OPTION]...
    -h, --help          show help
    -s, --static        compile static binary
    -d, --dev           compile dev version
```
## Build Debian package: 
Debian do not like static binary, so in debian package, ruri is dynamically linked.      
You can run:       
```sh
apt update
apt build-dep . -y
dpkg-buildpackage -b -us -uc -d
```
This will bulid the debian package.      
# Integration:
ruri is ready to integrate into other projects, with the MIT License, it is compatiblte to be redistribute with almost all license, or commercial/closed source.      
See [Integration](doc/Integration.md) for a guide to integrate ruri into your projects.    
# Usage:    
See [USAGE](doc/USAGE.md)      
# FAQ:   
[FAQ](doc/FAQ.md)      
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
# Example Usage:      
```
# Run chroot container:
  sudo ruri /tmp/alpine
# Very simple as you can see.
# About the capabilities:
# Run privileged chroot container:
  sudo ruri -p /tmp/alpine
# If you want to run privileged chroot container,
# but you don't want to give the container cap_sys_chroot privileges:
  sudo ruri -p -d cap_sys_chroot /tmp/alpine
# If you want to run chroot container with common privileges,
# but you want cap_sys_admin to be kept:
  sudo ruri -k cap_sys_admin /tmp/alpine
# About unshare:
# Unshare container's capability options are same with chroot.
# Run unshare container:
  sudo ruri -u /tmp/alpine
# Umount the container:
  sudo ruri -U /tmp/alpine
```
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
