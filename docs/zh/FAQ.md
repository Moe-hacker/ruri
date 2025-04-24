# 常见问题

## `-P` 选项无法显示进程

由于 ruri 使用 pivot_root() 为无根容器提供更好的安全性，
如果您的设备不支持 PID ns，
我们无法通过读取 /proc/$PID/root 获取进程信息，因为在 pivot_root 之后，它将始终为 `/`

## 网络问题

你可能会遇到 `temporary failure resolving xxxxx` 或 `bad address xxxxx` 的问题
尝试：

```
rm /etc/resolv.conf
echo nameserver 1.1.1.1 > /etc/resolv.conf
```

对于 Android，在容器中运行 `https://github.com/Moe-hacker/daijin/raw/refs/heads/main/src/share/fixup.sh`

## systemd

Systemd 需要 CAP_SYS_ADMIN 才能工作，并且需要 PID 命名空间支持才能使自己成为 PID 1。
在我的设备上，使用 `sudo ./ruri -u -k cap_sys_admin ../ubuntu /sbin/init &` 和然后 `sudo ./ruri ../ubuntu /bin/bash` 进入容器，尽管它显示 `State: degraded`，systemd 似乎可以正常工作
但是，它可能会对主机进行一些更改，并可能导致设备崩溃，请自行承担风险使用它

## 容器环境

出于安全考虑，ruri 容器类似于默认的 docker 容器，它将屏蔽 /sys 和 /proc 中的某些目录，丢弃不需要的能力，并且默认情况下你无法运行像 mknod 或 mount 这样的命令

## 能力

ruri 默认会将能力设置为与 docker 普通容器相同，你可以使用 `-k [cap]` 或 `-d [cap]` 来更改能力设置
例如，使用 `-d cap_sys_admin` 丢弃 CAP_SYS_ADMIN
在未来，可能会有新的能力添加到内核中，如果你使用旧的构建，它们的名称可能无法被识别。你可以使用能力的值（使用 `capsh  --explain=[cap]` 获取值）来丢弃它，例如，使用 `-d 114` 丢弃能力 114（我不知道这个能力是什么，可能可以让我成为超级用户）

## 配置

从 v3.0 开始，ruri 可以使用 [k2v](https://github.com/Moe-hacker/libk2v)，一个简单的配置格式，来存储容器的配置

## rurienv

从 v3.0 开始，ruri 删除了守护进程，它使用一种新的方式来存储正在运行的容器的配置信息
ruri 会创建 `/.rurienv` 文件到容器中，以存储容器的运行时信息
.rurienv 文件由 ruri 自动控制，请不要编辑它

## tty

ruri 中的 `tty` 命令可能会显示 "not a tty"
如果你需要运行一些程序，例如 `gpg`，请在容器中使用 `script -q -O /dev/null`

## 运行时目录

ruri 会在 chroot(2) 进入容器后创建 /dev/, /sys/ 和 /proc/ 目录，以提高安全性。你可以使用 `-S` 选项强制绑定挂载系统运行时目录

## 多架构容器

是的，如果您的设备支持，您可以通过 ruri 运行多架构容器
需要在内核配置中启用 CONFIG_BINFMT_MISC
你需要先复制 qemu-\*-static 到你的容器中
qemu 的路径是 chroot 容器中 qemu 二进制文件的绝对路径，例如，你有 qemu 二进制文件在 `/path/to/container/qemu-amd64-static`，使用 `-a x86_64 -q /qemu-amd64-static` 参数启动容器

## 无根容器

如果容器中出现 `Couldn't create temporary file /tmp/apt.conf.sIKx3J for passing config to apt-key` 错误，请 `chmod 777 /tmp`
你需要在主机上安装 uidmap
你可能需要配置 /etc/subuid 和 /etc/subgid

## Seccomp

ruri 的 seccomp 规则基于 Docker 的默认 seccomp 配置文件。ruri 没有提供更改它的方法，但你可以编辑 src/seccomp.c 并使用你自己的配置重写 setup_seccomp()
