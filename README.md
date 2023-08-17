
![](https://github.com/Moe-hacker/ruri/raw/main/logo/logo.png)

![](https://img.shields.io/github/stars/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=starship&logoColor=fee4d0)
![](https://img.shields.io/github/forks/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=git&logoColor=fee4d0)
![](https://img.shields.io/github/license/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=cloudera&logoColor=fee4d0)
![](https://img.shields.io/github/repo-size/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)
![](https://img.shields.io/github/last-commit/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)
![](https://img.shields.io/badge/language-c-green?style=for-the-badge&color=fee4d0&logo=C&logoColor=fee4d0)

<p align="center">「 须臾水面明月出，沧江万顷瑠璃寒 」</p>

-----------------     
### WARNING:      
```
* Your warranty is now void.
* I am not responsible for anything that may happen to your device by using this program.
* You do it at your own risk and take the responsibility upon yourself.
* And you are not to blame the author or Github and its developers.
* This program has no Super Cow Powers.
```
### About ruri:         
&emsp;ruri is pronounced as  `luli`, or you can call it `瑠璃` in Chinese or Japanese as well.       
&emsp;ruri is the romaji acronym of Lightweight, User-friendly Linux-container Implementation. It's designed to provide better security for Linux containers on devices that do not support docker.       
&emsp;It's like `chroot` and `unshare`, but it is more secure.       
&emsp;It is designed to be a simple and lightweight container implementation, but you are still free to define all the configurations of the container.          
&emsp;The default capability set is the same as the docker container, which can be elevated with the `-p` option, reduced by `-d`, or you can use `--keep` and `--drop` to set by yourself.      
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
sudo ruri -u /tmp/alpine
```
Or:      
```
sudo ruri -D
sudo ruri -u /tmp/alpine
```
Very simple as you can see.    
#### For command line examples, please see `ruri -hh`
#### make options:
```text
  make all            :compile
  make install        :install ruri to $PREFIX
  make static         :static compile,with musl or glibc
   make static-bionic :static compile,with bionic
  make clean          :clean
Only for testing:
  make dev            :compile without optimizations, enable gdb debug information and extra logs.
  make asan           :enable ASAN
  make check          :run clang-tidy
  make format         :format code
```
#### Dependent libraries:
For dynamic compilation:         
- libcap       
- libpthread 
     
For static compilation:         
- libcap-static
- libc-static         
### Usage:    
```text
Usage:
  ruri OPTIONS
  ruri [ARGS] CONTAINER_DIRECTORY [INIT_COMMAND]
OPTIONS:
  -v                    :Show version info
  -h                    :Show helps
  -hh                   :Show helps and commandline examples
  -D                    :Run rurid
  -K                    :Kill rurid
  -t                    :Check if rurid is running
  -l                    :List all running unshare containers
  -U [container_dir]    :Umount&kill a container
ARGS for running a container:
  -u                    :Enable unshare feature
  -n                    :Set NO_NEW_PRIVS Flag
  -d                    :Drop more capabilities for better security
  -p                    :Run privileged container
 --keep [cap]           :Keep the specified cap
 --drop [cap]           :Drop the specified cap
  -e [env] [value]      :Set env to its value *Not work if init command is like `su -`
  -m [dir] [mountpoint] :Mount dir to mountpoint
  -w                    :Disable warnings
```
&emsp;This program should be run with root privileges.        
&emsp;Please unset $LD_PRELOAD before running this program.              
### Full User Guide:
See `ruri(1)` in manpage after installation.   

```
●●●●  ●   ● ●●●●   ●●●        ●   ●  ●●●         ●●●
●   ● ●   ● ●   ●   ●         ●   ● ●   ●       ●   ●
●●●●  ●   ● ●●●●    ●   ●●●●● ●   ●   ●●        ●   ●
●  ●  ●   ● ●  ●    ●          ● ●   ●     ●●●  ●   ●
●   ●  ●●●  ●   ●  ●●●          ●   ●●●●●  ●●●   ●●●
```
--------
<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>          
<p align="center">(>_×)</p>
