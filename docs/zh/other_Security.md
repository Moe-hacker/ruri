---
aside: false
---

# 其他内置保护

## /dev 中的设备

对于 /dev，ruri 只会创建必要的设备，因此块设备在容器中始终不可用，并且由于 cap_mknod 和 cap_sys_admin 默认被丢弃，因此你无法通过修改磁盘分区来逃离 ruri 容器

### 掩码目录

ruri 将在 /proc 和 /sys 中使用 tmpfs 掩码一些目录，这可以保护主机避免安全问题

## Capabilities

默认情况下，ruri 将丢弃不需要的功能，以便它可以避免从容器中逃逸
