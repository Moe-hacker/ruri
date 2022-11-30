### 关于：    
&emsp;这里是将来的termux-container中chroot和chroot-unshare容器底层实现，咱自己写的东西咱还是比较喜欢用MIT协议喵～        
&emsp;也可以作为一个容器应用在普通linux系统下运行。               
### 安装：    
&emsp;make后将生成的container文件放入你系统的$PATH里就可以了。           
### 用法：    
```text
container [选项] [容器目录]
```
&emsp;选项：    
```text
-h :显示帮助信息
-u :开启unshare功能将容器隔离到新namespace中
-U :尝试卸载容器
-d :通过移除docker默认移除的capability降低容器权限
-D :进一步移除容器capability降低权限
```
&emsp;注：
- 容器必须以root权限运行。      
- 在termux中需要删除$LD_PRELOAD变量来调用此程序。      
### Capability选项：    
&emsp;通过编辑`container.h`可选择哪些capability将会在加入-d或-D选项后移除。      
&emsp;部分看起来会影响容器正常运行的capability默认即使开启-D选项也不会被移除。       
### TODO :    
&emsp;研究usermap实现，将容器root用户映射为普通用户。          
