<p align="center">「 可以自称贫穷却不必为此折损自尊</p>
<p align="center">是富人与生俱来的特权 」</p>
<p align="center">——酷安@普通的魔法使56</p>
<p align="center">(>_×)</p>         

-----------
### 关于：    
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
- 性能不输传统chroot/unshare容器
### 安装：    
#### 编译依赖：         
libcap动态库用于动态编译，libc和libcap静态库用于静态编译。           
#### 编译选项：     
```text
make all        :默认动态编译
make install    :默认动态编译并安装为moe-container命令
make static     :静态编译
make staticfail :如果系统装有libcap.a但依然报错，将它复制到项目目录执行此编译选项
make no         :动态编译，关闭优化选项
make clean      :清理生成文件
make help       :显示帮助
```
### 用法：    
```text
container [选项] [容器目录] (init命令)
```
&emsp;选项：    
```text
-v           :显示版本信息
-h           :显示帮助信息
-u           :开启unshare功能将容器隔离到新namespace中
-U           :尝试卸载容器
-d           :进一步降低特权
-p           :运行特权容器
--drop [cap] :移除指定特权
--keep [cap] :保留指定特权
-w           :抑制警告
```
&emsp;注：
- 容器必须以root权限运行。      
- 在termux中需要删除$LD_PRELOAD变量来调用此程序。      
### Capability选项：    
&emsp;通过编辑`container.h`可选择哪些capability将会在加入-d或-D选项后移除。      
&emsp;部分会影响容器正常运行的capability默认即使开启-D选项也不会被移除。       
### 关于namespace：      
&emsp;unshare()中的`CLONE_NEWUSER`和`CLONE_NEWNET`功能暂时还不会用，因此没有开启。         
### TODO:         
&emsp;研究usermap实现，将容器root用户映射为普通用户。          
