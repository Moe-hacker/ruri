# 日常使用

```sh
ruri [选项]...
ruri [参数]... [容器目录]... [命令 [参数]...]
```

## 选项

```text
-v, --version ...............................: 显示版本信息
-V, --version-code ..........................: 显示版本号
-h, --help ..................................: 显示帮助信息
-H, --show-examples .........................: 显示命令行示例
-P, --ps [container_dir/config] .............: 显示容器进程状态
```

这四个选项将显示容器信息

---

```
-U, --umount [container_dir/config] .........: 卸载容器
```

运行容器时，ruri 需要挂载一些目录
运行容器后，可以使用`-U`选项卸载容器
此选项需要以 root 用户运行
警告：在删除容器之前，请始终运行`sudo ruri -U /path/to/container`

---

```
-C, --correct-config .......................: 修正配置文件
```

尝试修正不完整的配置文件

## 参数

普通 ruri 容器应该以 sudo 运行，但您也可以使用`-r`选项运行无根容器

---

```
-D, --dump-config ...........................: 转储配置
```

ruri 支持使用配置文件，您可以使用`-D`选项转储容器当前配置
例如：

```
ruri -D -k cap_sys_admin -d cap_sys_chroot ./t
```

这将转储容器配置，因此下次您可以只使用配置文件而不是`-k cap_sys_admin -d cap_sys_chroot`参数

---

```
-o, --output [config file] ..................: 设置`-D`选项的输出文件
```

此选项用于`-D`选项，将配置保存到文件中
例如：

```
ruri -D -o test.conf -k cap_sys_admin -d cap_sys_chroot ./t
```

这将保存配置到 test.conf

---

```
-c, --config [config] [args] [COMMAND [ARGS]]: 使用配置文件
```

您可以使用`ruri -c config_file`运行一个容器，使用配置文件
例如：

```
ruri -c test.conf
```

或者：

```
ruri -c test.conf -k cap_sys_admin /bin/su root -
```

这将使用 test.conf 运行容器

---

```
-a, --arch [arch] ...........................: 通过binfmt_misc/QEMU模拟架构
-q, --qemu-path [path] ......................: 指定QEMU的路径
```

这两个参数应该同时设置
ruri 支持使用 binfmt_misc 内核的 qemu-user-static 功能运行跨架构容器
`-q`选项可以使用主机上的 qemu 路径，它将被复制到容器中的/qemu-ruri

例如在 arm64 设备上：

```
ruri -q /usr/bin/qemu-x86_64-static -a x86_64 ./test-x86_64
```

但请记住，不要使用此功能模拟主机架构
注意：此选项需要内核支持 binfmt_misc

---

```
-u, --unshare ...............................: 启用unshare功能
```

ruri 支持 unshare 容器，但 NET 和 USER 命名空间不支持。
注意：当 PID 1 在 PID NS 中死亡时，命名空间将被清除，因此其中的所有进程都将死亡
注意：此选项需要内核支持命名空间，它将尝试启用支持的命名空间，但如果失败，它只会显示警告

---

```
-n, --no-new-privs ..........................: 设置NO_NEW_PRIVS标志
```

此参数将设置 NO_NEW_PRIVS，普通用户将无法使用`sudo`等命令

---

```
-N, --no-rurienv ............................: 不使用.rurienv文件
```

ruri 将在容器中创建/.rurienv 文件以保存容器配置，您可以使用此选项禁用它

---

```
-J, --join-ns [NS_PID].......................: 使用NS_PID加入命名空间
```

如果您使用带有-N 选项的 unshare/rootless 容器，您可以使用此选项加入其命名空间
此选项需要与`-uN`或`-rN`选项一起使用

---

```
-s, --enable-seccomp ........................: 启用内置的Seccomp配置文件
```

ruri 提供了一个内置的 seccomp 配置文件，但如果您真的需要使用 seccomp，您可能需要编辑 src/seccomp.c 并重新编译它
注意：此选项需要内核支持 seccomp

---

```
-p, --privileged ............................: 运行特权容器
```

此参数将授予容器所有能力，但您也可以使用`-d`选项过滤掉您不想保留的能力

---

```
-r, --rootless ..............................: 运行无根容器
```

此选项应该与普通用户一起运行，因此您可以运行无根容器
此选项需要`uidmap`包和用户命名空间支持
注意：此选项需要用户命名空间支持，并且需要内核允许使用普通用户创建用户命名空间

---

```
-k, --keep [cap] ............................: 保留指定能力
-d, --drop [cap] ............................: 丢弃指定能力
```

这两个选项可以控制容器中的能力，cap 可以同时是值或名称
例如，`-k cap_chown`与`-k 0`具有相同的效果

---

```
-e, --env [env] [value] .....................: 设置环境变量到其值
```

一个非常无用的功能，我希望它能工作

---

```
-m, --mount [dir/dev/img/file] [target] .....: 挂载dir/block-device/image/file到target
-M, --ro-mount [dir/dev/img/file] [target] ..: 挂载dir/block-device/image/file为只读
```

ruri 提供了一个强大的挂载功能，这里有一些例子：

```
ruri -m /dev/sda1 / ./test
```

此命令将挂载/dev/sda1 到./test 并运行容器

```
ruri -m ./test.img / ./test
```

此命令将挂载./test.img 到./test 并运行容器

```
ruri -m /sdcard /sdcard ./test
```

此命令将挂载/sdcard 到./test/sdcard 并运行容器
它还可以绑定挂载文件/FIFO/socket

---

```
-S, --host-runtime ..........................: 绑定挂载/dev/, /sys/ 和 /proc/ 从主机
```

ruri 将在 chroot(2)进入容器后创建/dev/, /sys/ 和 /proc/ 以提高安全性。您可以使用`-S`选项强制它绑定挂载系统运行时目录。

---

```
-R, --read-only .............................: 挂载/为只读
```

这将使整个容器根文件系统只读。

---

```
-l, --limit [cpuset=cpu/memory=mem] .........: 设置cpuset/memory限制
```

ruri 目前支持 cpuset 和 memory cgroup。
每个`-l`选项只能设置一个 cpuset/memory 限制
例如：

```
ruri -l memory=1M -l cpuset=1 /test
```

注意：此选项需要内核支持指定 cgroup。

---

```
-w, --no-warnings ...........................: 禁用警告
```

运行 ruri 时可能会出现一些警告，如果您不喜欢，可以使用`-w`选项禁用它们。

---

```
-f, --fork ..................................: 在exec命令之前fork()
```

unshare 和 rootless 容器在运行命令之前总是会 fork()，
您可以使用此选项使普通 chroot 容器具有相同的行为，

---

```
-j, --just-chroot ...........................: 只chroot，不要创建运行时目录
```

如果您启用此选项，ruri 将不会在容器中创建运行时目录(/dev, proc 和 /sys)。

---

```
-W, --work-dir [dir]..........................: 更改容器中的工作目录。
```

默认工作目录是`/`，您可以使用此选项更改它。

---

```
-A, --unmask-dirs ............................: 取消掩码/proc和/sys中的目录。
```

ruri 默认会保护/proc 和/sys 中的某些文件/目录，使用`-A`选项禁用此功能。

---

```
-E, --user ...................................: 设置运行命令的用户。
```

您可以使用此选项在 exec(3)之前切换到普通用户。

---

```
-t, --hostname [hostname] ....................: 设置主机名
```

设置主机名，仅适用于 unshare 容器。

---

```
-x, --no-network .............................: 禁用网络
```

禁用网络，此选项需要 net ns 支持，并将在同一时间启用 unshare。

---

```
-K, --use-kvm ...............................: 启用/dev/kvm支持
```

启用/dev/kvm 支持。

---

```
-I, --char-dev [device] [major] [minor] .....: 添加字符设备到容器
```

添加字符设备到容器，例如`-I kvm 10 232`或`-I dri/card0 226 0`。

---

```
-i, --hidepid 1/2 ...........................: 隐藏/proc中的pid
```

Hidepid 选项用于/proc。

---

```
-b, --background ............................: 将ruri置于后台
-L, --logfile [file] ........................: 设置-b选项的日志文件
```

在后台运行 ruri 并设置输出文件。

---

```
-X, --deny-syscall [syscall] ................: 拒绝系统调用
```

使用 Seccomp 设置系统调用为 SCMP_ACT_KILL。

---

```
-O, --oom-score-adj [score] .................: 设置oom_score_adj。
```

设置 oom_score_adj，注意使用负值是危险的。
