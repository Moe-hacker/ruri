<p align="center">「 可以自称贫穷却不必为此折损自尊</p>
<p align="center">是富人与生俱来的特权 」</p>
<p align="center">——酷安@普通的魔法使56</p>
<p align="center">(>_×)</p>         

-----------
### 关于：    
&emsp;moe-container现更名为ruri(瑠璃)！      
&emsp;文章开头那句引用没有对大佬不敬的意思，只是觉得在放在这里挺合适的引用下而已。             
&emsp;也知道自己就是个萌新，大佬轻喷。         
&emsp;这里是将来的termux-container中chroot和chroot-unshare容器底层实现，咱自己写的东西咱还是比较喜欢用MIT协议喵～        
&emsp;也可以作为一个容器应用在普通linux系统下运行。               
### Features:    
- 纯C语言实现
- 二进制仅几百kb      
- 容器权限可控
- ns隔离功能
- 容器内自动挂载系统目录
### 安装：    
#### 编译依赖：         
libcap动态库用于动态编译，libc和libcap静态库用于静态编译,pkg-config用于获取库路径。           
#### 编译选项：     
```text
make all        :默认动态编译
make install    :默认动态编译并安装为ruri命令
make static     :静态编译
*仅供开发者
make dev        :关闭优化选项，开启gdb支持
make clean      :清理生成文件
make help       :显示帮助
```
### 用法：    
```text
  ruri [其他选项] [<参数> <容器目录> <初始化命令>]
其他选项:
  -v            :版本信息
  -h            :显示帮助
  -D            :运行rurid
  -l            :列出所有运行中的unshare容器
  -U [容器目录] :杀死容器并解除挂载
容器运行参数:
  -u            :开启unshare特性
  -d            :移除更多特权以提供更好的安全性
  -p            :运行特权容器
 --keep [cap]   :保留指定权限
 --drop [cap]   :移除指定权限
  -w            :抑制警告
```
&emsp;注：
- 容器必须以root权限运行。      
- 在termux中需要删除$LD_PRELOAD变量来调用此程序。           
### 关于namespace：      
&emsp;unshare()中的`CLONE_NEWUSER`和`CLONE_NEWNET`功能未被开启。         
### 关于rurid：      
&emsp;由于部分函数需要共享，rurid并非独立二进制文件。rurid是一个用于存储容器信息并初始化容器的服务进程，以确保同一容器始终运行在相同命名空间。它并非必要进程，纯chroot容器将不会与rurid进行通信，unshare容器仅会在服务未运行时发出警告，但仍建议在运行容器前启动rurid。
