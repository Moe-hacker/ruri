<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>          

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
```
### About:      
&emsp;moe-container is now renamed as ruri.    
&emsp;ruri is pronounced as /lʊlɪ/, or you can call it `瑠璃`. Although it sounds like it should be cyan, I chose <font color=#FEE4D0>#FEE4D0</font>  as its accent color.        
&emsp;ruri runs a linux container with namespaces and dropped capabilities. It is designed to provide better security for Linux containers on devices that do not support docker.       
&emsp;It's like `chroot` and `unshare`, but it is more secure.       
&emsp;It is designed to be a simple and lightweight container implementation, but you are still free to define all the configurations of the container.      
### Features:
- Written with 100% C.          
- Light weight, the binary is less than 1M.             
- Controllable capability set.           
- Automatically mount system runtime files and login to the container.        
### Installation:
- Clone the source code.          
- Run `make install` in the source directory.      
#### make options:
```text
  make all        :compile
  make install    :make all and install ruri to $PREFIX
  make static     :static compile
  make clean      :clean
*Only for developer:
  make dev        :compile without optimizations and enable gdb debug information     
```
#### Dependent libraries:
For dynamic compilation:         
- libcap       
- libpthread      
For static compilation:         
- libcap-static
- libc-static         
- pkg-config
### Usage:    
```text
  ruri [Other options] [<Args> <container directory> <init command>]
Other options:
  -v                 :Show version info
  -h                 :Show helps
  -D                 :Run rurid
  -l                 :List all running unshare containers
  -U [container_dir] :Umount&kill a container
Args for running a container:
  -u                 :Enable unshare feature
  -d                 :Drop more capabilities for better security
  -p                 :Run privileged container
 --keep [cap]        :Keep the specified cap
 --drop [cap]        :Drop the specified cap
  -w                 :Disable warnings
```
&emsp;This program should be run with root privileges.        
&emsp;Unset $LD_PRELOAD before running this program to fix issues in termux.         
### About rurid:         
&emsp;Since some functions need to be shared, rurid is not a separate binary program. rurid is a background service process that stores unshare container information and initializes the container so that the same container always runs in the same namespaces. But it is not a necessary process. Pure chroot containers do not rely on rurid, unshare containers will only show a warning if daemon is not running, but it is still recommended to start rurid before running the container.        

--------
<p align="center">「見つけてくれたね ありがとう」</p>
<p align="center">(>_×)</p>
