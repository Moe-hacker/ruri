---
aside: false
---

# 什么是 ruri

ruri 的读音是 `luli`，或者你也可以叫它 `[瑠璃/琉璃]` ~~(るり)~~ 在中国或日本

ruri 是 Lightweight, User-friendly Linux-container Implementation 的缩写

ruri 是一个强大的容器实现，可以在几乎任何 Linux 设备上运行，即使在内核配置不完整或存储空间有限的情况下

## 为什么选择 ruri

- 强大的功能

  - 支持所有基本的容器功能，chroot, unshare with pivot_root, capability control, basic cgroup support, no_new_privs, auto set environment variables and change user/workdir, built-in seccomp profile, 等等
  - 内置支持 binfmt_misc & QEMU，所以你可以轻松地运行多架构容器
  - 内置支持 rootless 模式（需要用户命名空间支持）
  - 强大的挂载选项，你可以将镜像/分区挂载为根目录，并可以选择每个挂载点为只读或读写
  - 内置支持配置文件。

- 超轻量级，零运行时依赖，开箱即用

  - 只有 rootless 容器需要一个可选的运行时依赖 `uidmap`，所有 chroot/unshare 容器的功能都可以内置到一个一体化的二进制文件中
  - Ruri 为 arm64, armv7, armhf, riscv64, i386, loong64, s390x, ppc64le 和 x86_64 设备提供静态链接的二进制文件
  - ruri 的二进制文件非常小，经过 upx 压缩后，可以小到 200k 以下，但可以提供超过 30 个选项和更多的功能

- 灵活性，适用于更多平台

  - 从 Android 设备到物联网设备，从 amd64 到 s390x，ruri 可以在几乎所有 Linux 平台上提供基本的容器支持，唯一需要的是 root 权限

- 设计安全

  - 内置 rootless 容器支持
  - 内置安全选项，使容器更安全
  - 内置只读文件系统选项，提供更多保护

- 简单易用
  - 你可以直接使用 ruri 代替 `chroot` 命令，ruri 会为你完成所有事情
  - Ruri 赋予你自由配置一切的能力，但那并不意味着你需要学习每个选项才能使用它
