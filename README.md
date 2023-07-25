
![](https://github.com/Moe-hacker/ruri/raw/main/logo/logo.png)

![](https://img.shields.io/github/stars/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=instatus&logoColor=fee4d0)
![](https://img.shields.io/github/forks/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=git&logoColor=fee4d0)
![](https://img.shields.io/github/license/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=apache&logoColor=fee4d0)
![](https://img.shields.io/github/repo-size/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)
![](https://img.shields.io/github/last-commit/Moe-hacker/ruri?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)
![](https://img.shields.io/badge/language-c-green?style=for-the-badge&color=fee4d0&logo=sharp&logoColor=fee4d0)

-----------------     
You can read this doc in :

**[<kbd> <br> 简体中文 <br> </kbd>](https://github.com/Moe-hacker/ruri/blob/main/README-zh.md)**&emsp;**[<kbd> <br> English <br> </kbd>](https://github.com/Moe-hacker/ruri/blob/main/README.md)**

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
### Quick start:      
```
git clone https://github.com/Moe-hacker/ruri
cd ruri
sudo make install
```
#### make options:
```text
  make all         :compile
  make install     :install ruri to $PREFIX
  make static      :static compile
  make clean       :clean
Only for testing:
  make dev         :compile without optimizations, enable gdb debug information and extra logs.
  make asan        :enable ASAN
  make check       :run clang-tidy
  make strictcheck :run clang-tidy for more checks
  make format      :format code
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
ruri [Other options] [<Args> <container directory> <init command>]
Other options:
  -v                    :Show version info
  -h                    :Show helps
  -D                    :Run rurid
  -K                    :Kill rurid
  -t                    :Check if rurid is running
  -l                    :List all running unshare containers
  -U [container_dir]    :Umount&kill a container
Args for running a container:
  -u                    :Enable unshare feature
  -d                    :Drop more capabilities for better security
  -p                    :Run privileged container
 --keep [cap]           :Keep the specified cap
 --drop [cap]           :Drop the specified cap
  -e [env] [value]      :Set env to its value
  -m [dir] [mountpoint] :Mount dir to mountpoint
  -w                    :Disable warnings
```
&emsp;This program should be run with root privileges.        
&emsp;Please unset $LD_PRELOAD before running this program.              
### About rurid:         
&emsp;Rurid is the daemon of ruri. It can store the info of unshare containers and ensure that the same containers run in the same namespaces. It's not a necessary process and pure chroot containers will not communicate with the daemon.     

--------
<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>          
<p align="center">(>_×)</p>
