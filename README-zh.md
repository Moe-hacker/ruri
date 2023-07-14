<p align="center">「 可以自称贫穷却不必为此折损自尊</p>
<p align="center">是富人与生俱来的特权 」</p>
<p align="center">——酷安@普通的魔法使56</p>
<p align="center">(>_×)</p>         

-----------
### 警告：      
```
* 此项目作者对项目内的任何文件不做任何担保，哪怕是最基本的正确性担保
* 此项目作者不会对任何由于使用此项目而在您的设备上发生的事做担保
* 您自行使用此项目，并自行承担相应责任
* 您不应为此项目而责怪其作者和Github以及其开发者
* 此项目没有超级牛力
```
### 关于：         
&emsp;文章开头那句引用没有对大佬不敬的意思，只是觉得在放在这里挺合适的引用下而已。             
&emsp;也知道自己就是个萌新，大佬轻喷。         
&emsp;Ruri是一个用C语言写的容器，除了网络和用户之外的隔离在unshare容器中会自动开启，权限默认和docker容器相同，可通过-d来降低或-p来提高容器权限，也可以自行定义。      
### 安装：    
```
git clone https://github.com/Moe-hacker/ruri
cd ruri
sudo make install
```
#### 编译依赖：         
libcap动态库用于动态编译，libc和libcap静态库用于静态编译。           
#### 编译选项：     
```text
make all         :默认动态编译
make install     :默认动态编译并安装为ruri命令
make static      :静态编译
make clean       :清理生成文件
make help        :显示帮助
*仅供开发者
make dev         :关闭优化选项，开启gdb支持以及额外日志信息
make asan        :开启ASAN
make check       :运行clang-tidy检查
make strictcheck :运行clang-tidy执行更为严格的检查
make format      :格式化代码
```
### 用法：    
```text
  ruri [其他选项] [<参数> <容器目录> <初始化命令>]
其他选项:
  -v                    :版本信息
  -h                    :显示帮助
  -D                    :运行rurid
  -K                    :杀死rurid
  -t                    :检查rurid是否在运行
  -l                    :列出所有运行中的unshare容器
  -U [容器目录]         :杀死容器并解除挂载
容器运行参数:
  -u                    :开启unshare特性
  -d                    :移除更多特权以提供更好的安全性
  -p                    :运行特权容器
 --keep [cap]           :保留指定权限
 --drop [cap]           :移除指定权限
  -e [env] [value]      :设置环境变量env为value
  -m [dir] [mountpoint] :挂载dir到mountpoint
  -w                    :抑制警告
```
&emsp;注：
- 容器必须以root权限运行。      
- 在termux中需要删除$LD_PRELOAD变量来调用此程序。           
### 关于namespace：      
&emsp;unshare()中的`CLONE_NEWUSER`和`CLONE_NEWNET`功能未被开启。         
### 关于rurid：      
&emsp;rurid是一个用于存储容器信息并初始化容器的服务进程，以确保同一容器始终运行在相同命名空间。它并非必要进程，纯chroot容器将不会与rurid进行通信，unshare容器仅会在服务未运行时发出警告，但仍建议在运行容器前启动rurid。
