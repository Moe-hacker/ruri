# About rurienv

.rurienv 是一个在容器中的配置文件，为了安全起见，它默认是不可变的，并且由于容器默认没有 cap_linux_immutable，因此除非你使用 `-k cap_linux_immutable -k cap_sys_admin` 或 `-p` 运行容器，否则你无法在容器中编辑或删除它

它将记录以下配置：

- 要丢弃的能力
- 设置 NO_NEW_PRIVS 位
- 启用内置的 seccomp 配置文件
- 拥有 unshare 命名空间的 PID
- 容器 ID
- 工作目录
- 不显示警告
- 运行容器的用户
- 额外的挂载点
- 额外的只读挂载点
- 环境变量

## Security

.rurienv 被设置为不可变并绑定挂载为只读。这意味着除非你在容器中同时拥有 CAP_SYS_ADMIN(umount 它) 和 CAP_LINUX_IMMUTABLE(取消不可变位)，否则你无法在容器中编辑或删除它
对于无根容器，我们无法将其设置为不可变，因此我们不信任它
它只会更改 ns_pid, work_dir 和 user

## Its behavior

1. 在初始化容器时，覆盖 drop_caplist, no_new_privs, enable_seccomp, no_warnings 作为配置。除非你不使用 .rurienv 文件，否则无法禁用这些配置。如果你想更改其中任何一个配置，你应该使用 -U 卸载容器并使用新的 args/configs 重新启动它
2. 如果它们在 cmdline 参数中未设置，则覆盖 user 和 work_dir 设置
3. 存储 container_id 以将容器进程设置到同一个 cgroup 中
4. 存储 ns_pid 以确保 unshare 容器在同一个命名空间中。如果 ruri 检测到 ns_pid，它将自动启用 unshare 并加入命名空间
5. 存储 extra_mountpoint 和 extra_ro_mountpoint 以卸载容器
