<p align="center">「 咲誇る花 美しく、</p>    
<p align="center">散り行く運命 知りながら、</p>    
<p align="center">僅かな時の彩を 」</p>    
<p align="center">(>_×)</p>         

-----------------     

[[简体中文]](https://github.com/Moe-hacker/moe-container/blob/main/README-zh.md)
### About:      
&emsp;moe-container runs a linux container with namespaces and dropped capabilities in your system.       
&emsp;It's like `chroot` and `unshare`,but with a controllable reduced capability set.       
### Features:
- Written with 100% C programming language.          
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
If you got errors like `undefined symbol: cap_drop_bound` or `undefined reference to 'cap_set_flag'` when using static compile , please copy your `libcap.a` into current directory and use `make staticfail` instead.        
#### Dependent libraries:
For dynamic compilation:         
- libcap       

For static compilation:         
- libcap-static
- libc-static         
### Usage:    
&emsp;container [options] [container directory]
#### Options:
```text
  -v :Show version info
  -h :Show helps
  -u :Enable unshare feature
  -U :Try to umount container,please reboot instead for better security
  -d :Drop capabilities to reduce permissions of container
  -D :Drop more capabilities for better security
```
This program should be run with root privileges.        
Unset $LD_PRELOAD before running this program to fix issues in termux.         
### About capabilities:     
Edit `container.h` to customise which capabilities will be dropped or kept after using `-d` or `-D` option.      

--------
<p align="center">「見つけてくれたね ありがとう」</p>
<p align="center">(>_×)</p>
