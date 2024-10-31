ruri(Lightweight, User-friendly Linux-container Implementation)是一个非常轻量的chroot/unshare Linux容器实现，使用C语言编写，静态二进制仅不到1M，具有相比chroot/unshare命令增强的安全性，更丰富的配置选项和更加用户友好的使用方式。      
ruri试图为`内核配置不完整`或`内存容量不充足`的设备提供更加安全方便的容器实现，而不是替代containerd/youki等OCI容器实现。       
# 安装：
您可以直接去[Release](https://github.com/Moe-hacker/ruri/releases/)下载ruri的静态二进制版本，或者您可以自行编译。      
# 用法：
See [USAGE](USAGE_zh.md)   
# 使用：
首先你需要一个rootfs，这是基础。
去[lxc-mirror](https://mirrors.bfsu.edu.cn/lxc-images/images/)选一个，下载下来。      
然后，解压到./test目录中（mkdir test && tar -xvf rootfs.tar.xz -C ./test），我们开始。      
## 基本使用：
运行一个受保护的chroot容器：       
```
sudo ruri ./test
```
将其解除挂载：      
```
sudo ruri -U ./test
```
运行特权容器（具有所有capability）：      
```
sudo ruri -p ./test
```
需要注意，ruri为了统一容器行为，在容器被挂载后会统一使用最初的配置来运行容器，你需要先解除容器挂载后再修改权限等配置。      
运行unshare容器：      
```
sudo ruri -u ./test
```
基本使用篇完，只是简单用用的话，就这么简单。      
# 网络问题：
您可能会遇到像`temporary failure resolving xxxxx`或`bad address xxxxx`的错误。      
可以尝试：  
```
rm /etc/resolv.conf
echo nameserver 1.1.1.1 > /etc/resolv.conf
```
或者对于Android，您可尝试在容器中运行 https://github.com/Moe-hacker/daijin/raw/refs/heads/main/src/share/fixup.sh      
# 关于rootless容器：
如果在容器中遇到 `Couldn't create temporary file /tmp/apt.conf.sIKx3J for passing config to apt-key` 这样的错误，请 `chmod 777 /tmp`。  
您需要在宿主机上安装 uidmap。  
您可能需要在宿主机上配置/etc/subuid和/etc/subgid。      
# 关于运行时目录：
为了安全性，ruri会在chroot()后再创建/dev, /proc和/sys目录以及里面的文件，你可以使用-S选项来挂载宿主机上的运行时目录而非由ruri创建。      
# 安全选项：
## 关于Capability：
从Linux 2.2开始，内核将进程root特权分割为可独立控制的部分，称之为capability，capability是线程属性，可从父进程继承。      
通常所说的root权限其实是拥有相关capability，如chroot(2)其实需要的是CAP_SYS_CHROOT而非完整的root特权。      
ruri支持通过`-d`来移除capability，`-k`来保留。  
未来可能会有新的权限被添加到内核中，如果您使用旧版本，可能无法识别它们的名称。您可以使用权限的值（使用 `capsh --explain=[cap]` 来获取值）来删除它，例如，使用 `-d 114` 来删除权限 114（咱也不知道这个权限具体是什么，也许可以让拥有这个权限的用户变成homo（大嘘））。     
如果你并不知道capability配置意味着什么，请保持默认。      
## 其它安全选项：
ruri内置了一份seccomp profile，可通过`-s`选项开启。      
ruri可以通过`-n`选项为容器设置NO_NEW_PRIVS位。      
ruri可通过`-R`选项将根目录挂载为只读。      
# 增加挂载点：
ruri支持将目录/img镜像文件/块设备挂载到容器中。      
挂载点目录会自动创建，无需手动。       
比如在安卓系统下的容器中挂载/sdcard：       
```
sudo ruri -m /sdcard /sdcard ./test
```
而-M选项用于只读挂载，可以增强安全性，缺点是无法写入。       
ruri的挂载在运行chroot()之前，于是，当rootfs在镜像或其他块设备中时：         
```
sudo ruri -m ./rootfs.img / ./test
```
可以将rootfs.img提前挂载，系统分区同理，对于qemu容器或者在骁龙845等设备上安装Linux等场景特别有用。      
# 跨架构容器：
在支持binfmt_misc的设备上，ruri可通过qemu-user-static运行跨架构容器。      
判断是否支持binfmt_misc，可通过执行`sudo grep binfmt_misc /proc/filesystems`或`sudo zgrep BINFMT_MISC /proc/config.gz`命令。
你需要复制静态版本的qemu-user-xxxx到容器中。      
然后：      
```
sudo ruri -a [容器架构] -q /qemu-user-xxxx  ./test
```
# Cgroup限制：
ruri自3.1起支持cgroup的cpuset和memory限制，可以用`-l cpuset=0-3`限制只能使用CPU 0-3，或`-l memory=1024M`限制内存只能使用1024M这样。此特性需要内核支持相应cgroup。      
# 配置文件：
从3.0版本开始，ruri取消了daemon支持，换为配置文件支持。      
配置文件有两种：       
容器目录下的.rurienv，用于统一容器环境。      
普通配置文件，用于运行容器。            
配置文件统一采用[k2v](https://github.com/Moe-hacker/libk2v)格式，是作者自己写的一个库来实现的，类似toml语法，但更加严苛。      
你可以在运行容器的参数中加入`-D`选项来导出配置，使用`-o [配置文件]`选项保存到文件。       
使用`-c  [配置文件]`来使用配置文件运行容器。       
