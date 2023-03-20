<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>    
<p align="center">(>_×)</p>         

![](https://img.shields.io/github/stars/Moe-hacker/moe-container?style=for-the-badge&color=fee4d0&logo=instatus&logoColor=fee4d0)
![](https://img.shields.io/github/forks/Moe-hacker/moe-container?style=for-the-badge&color=fee4d0&logo=git&logoColor=fee4d0)
![](https://img.shields.io/github/license/Moe-hacker/moe-container?style=for-the-badge&color=fee4d0&logo=apache&logoColor=fee4d0)
![](https://img.shields.io/github/repo-size/Moe-hacker/moe-container?style=for-the-badge&color=fee4d0&logo=files&logoColor=fee4d0)
![](https://img.shields.io/github/last-commit/Moe-hacker/moe-container?style=for-the-badge&color=fee4d0&logo=codeigniter&logoColor=fee4d0)
![](https://img.shields.io/badge/language-c-green?style=for-the-badge&color=fee4d0&logo=sharp&logoColor=fee4d0)

-----------------     
You can read this doc in :

**[<kbd> <br> 简体中文 <br> </kbd>](https://github.com/Moe-hacker/moe-container/blob/main/README-zh.md)**&emsp;**[<kbd> <br> English <br> </kbd>](https://github.com/Moe-hacker/moe-container/blob/main/README.md)**

### WARNING:      
```
* Your warranty is now void.
* I am not responsible for anything that may happen to your device by using this program.
* You do it at your own risk and take the responsibility upon yourself.
```
### About:      
&emsp;moe-container runs a linux container with namespaces and dropped capabilities in your system.       
&emsp;It's like `chroot` and `unshare`,but with a controllable reduced capability set.       
### Features:
- Written with 100% C programming language.          
- Light weight, the binary is less than 1M.      
- Can be run with unshare mode.        
- Controllable capability set.           
- Automatically mount system runtime files and login to the container.        
### Installation:
- Clone the source code.          
- Run `make install` in the source directory.      
#### make options:
```text
  make all        :compile
  make install    :make all and install container to $PREFIX
  make static     :static compile
  make staticfail :static compile,fix errors
  make no         :compile without optimizations
  make clean      :clean
```
&emsp;If you got errors like `undefined symbol: cap_drop_bound` or `undefined reference to 'cap_set_flag'` when using static compile , please copy your `libcap.a` into current directory and use `make staticfail` instead.        
#### Dependent libraries:
For dynamic compilation:         
- libcap       

For static compilation:         
- libcap-static
- libc-static         
### Usage:    
```text
container [options] [container directory] (init command)
```
#### Options:
```text
  -v :Show version info
  -h :Show helps
  -u :Enable unshare feature
  -U :Try to umount container,please reboot instead for better security
  -d :Drop more capabilities for better security
  -p :Run privileged container
  -w :Disable warnings
```
&emsp;This program should be run with root privileges.        
&emsp;Unset $LD_PRELOAD before running this program to fix issues in termux.         
### About capabilities:     
&emsp;Edit `container.h` to customise which capabilities will be dropped or kept after using `-d` or `-D` option.      

--------
<p align="center">「見つけてくれたね ありがとう」</p>
<p align="center">(>_×)</p>
