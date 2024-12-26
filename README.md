
![](https://github.com/Moe-hacker/ruri/raw/main/logo/logo.png)

-----

<p align="center">「 须臾水面明月出，沧江万顷琉璃寒 」</p>

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14021121.svg)](https://doi.org/10.5281/zenodo.14021121)
-----------------     
# 中文文档
[中文文档](doc/README_zh.md)      
# WIP wiki:
https://wiki.crack.moe/ruri      
# About:         
&emsp;ruri is pronounced as `luli`, or you can call it `[瑠璃/琉璃]` ~~(るり)~~ in Chinese or Japanese as well.       
&emsp;ruri is acronym to Lightweight, User-friendly Linux-container Implementation.         
&emsp;ruri is a powerful container implementation that runs on almost any Linux device, even with incomplete kernel configurations or minimal storage space.           
# The enhanced version:
[rurima](https://github.com/Moe-hacker/rurima) was planned to be the ruri manager, but since it now has a full integration of ruri, you can use it as an enhanced version of ruri.      
Note that rurima is still WIP.      
# Performance:
On AMD Ryzen 5 5500U, Windows 11, Ubuntu 22.04.5 WSL 2      
```
# uname -m
x86_64
# /usr/bin/time -f "Time: %E\nMax memory: %M KB" ./ruri ../t /bin/true
Time: 0:00.01
Max memory: 860 KB
```
## Binary size(amd64):
||ruri|crun|%|
|---|---|---|---|
|(noupx)|454K|3.0M|-84.9%|
|(withupx)|147K|1.3M|-88.7%|
## ~~Alphabet coverage~~
|Alphabet|ruri used|%|
|---|---|---|
|52|41|79%|
# Highlights:
- Powerful Features
  - Basic container features are all supported, chroot, unshare with pivot_root, capability control, basic cgroup support, no_new_privs, auto set environment variables and change user/workdir, built-in seccomp profile, run rootless container, and even more...      
  - Built-in support for binfmt_misc & QEMU, so you can run multi-arch container easily.
  - Powerful mount option, you can mount image/partition as root, and you can choose every mountpoint to be read-only or rw.     
  - Built-in support for config file.
- Ultra-lightweight, Zero runtime Dependencies, Ready Out-of-the-Box
  - Only rootless container need an optional runtime dependency `uidmap`, all feature of chroot/unshare container can be built-in to an all-in-one binary.            
  - Ruri provides statically linked binaries for arm64, armv7, armhf, riscv64, i386, loong64, s390x, ppc64le and x86_64 devices.   
  - The binary of ruri is very small, after upx, it can even be less than 200k, but it can provide over 30 options and even more features.       
- Flexibility, for More Platform
  - From Android devices to IoT gadgets, from amd64 to s390x, ruri can provide basic container support on almost every Linux platforms, the only thing it need is root privilege.      
- Secure by Design 
  - Built-in rootless container support.      
  - Built-in security options, to make container more secure.      
  - Built-in read-only filesystem options for more protection.          
- Simple for Beginner
  - You can just use ruri as an instead of `chroot` command, and ruri will do all things for you.      
  - Ruri empowers you with the freedom to configure everything, but that do not means you need to learn every option to use it.    
<p align="center">
<img src="https://github.com/Moe-hacker/ruri/raw/main/logo/rurifetch.png" alt="" style="width:75%;align: center;">
</p>

# Get ruri:    
You can get ruri binary (statically linked) for arm64, armv7, armhf, riscv64, i386, loong64, s390x, ppc64le and x86_64 devices in [Release](https://github.com/Moe-hacker/ruri/releases/).      
Or you can run the following command to download ruri automatically:      
```sh
wget -q -O - https://getruri.crack.moe | bash -s -- -s
```
or:     
```sh
wget -q -O - https://ruri.nekofeng.com | bash -s -- -s
```
This will automatically download ruri binary to `./ruri`.      
# Usage:    
See [USAGE](doc/USAGE.md) to explore all features of ruri.         
# About command-line:
BSD style usage is partially supported now, for example, you can use `-pW /root`, but `-W/root` is not allowed.      
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
# Container Security:  
See [Enhance Container Security](doc/Security.md).      
# Build Manually:      
Ruri provides statically linked binary, but if you want to build it yourself, see [Build](doc/Build.md).      
# About systemd:
Systemd need CAP_SYS_ADMIN to work, and need user ns support to make itself to be PID 1.      
On my device, with `sudo ./ruri -u -k cap_sys_admin ../ubuntu /sbin/init &` and then `sudo ./ruri ../ubuntu /bin/bash` to enter container, although it shows `State: degraded`, systemd seems works.     
But, as it might do some changes for the host, you take your own risk to use it.      
# Integration:
ruri is ready to integrate into other projects, with the MIT License, it is compatiblte to be redistribute with almost all license, or commercial/closed source.      
An example is ruri's own build action [build-all.sh](build/build-all.sh), it runs containers for 9 different architectures to build itself, that shows its broad application prospects.      
Another example is [rurima](https://github.com/Moe-hacker/rurima), I made ruri built-in into it, so it can be run as a subcommand.      
See [Integration](doc/Integration.md) for a guide to integrate ruri into your projects.    
# Behavior of rurienv:
After initing the container, ruri will create a file /.rurienv by default, this config can unify container config, but it will also cover some of the command-line args, you can use `--no-rurienv` to disable it, or see [rurienv.md](doc/rurienv.md) to see its behavior.     
You might cannot remove this file unless you run `chattr -i .rurienv`, but don't worry, after umounting conainer by `ruri -U`, this config file will be removed automatically.      
If you want to change the container config, just use -U to umount it and re-run the container.      
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
