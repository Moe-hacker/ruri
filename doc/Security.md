# Enhance Container Security:
Here are several ways to enhance the security of ruri container, kindly read this document before using ruri.      
## Regular:
### Run rootless container:
If your device supports user ns, you can install uidmap and use `-r` option with common user, so that you can avoid using root privileges to run the container.      
### Run command in container with common user:
If you can not run rootless container, there's another choice, add a common user in your container and use `-E username` to run command as common user instead root.      
If you don't need any privileges, it's better to enable no_new_privs at the same time.      
### Hidepid:
ruri supports hidepid options for /proc, use `-i 1/2` to enable it.      
### Capabilities:
Ruri will automatically drop unneeded capabilities, but ruri also provides capability control function, you can read capabilities(7) and use `-d` option to filter out unnecessary capabilities in container.      
### Disable .rurienv:
Ruri will create the file /.rurienv in container, to avoid security issues, this file is immutable and read-only.      
But you can also disable creating it using `-N` option.      
### Set memory limit:
Ruri supports memory cgroup, you can use `-l` option to set the limit of memory usage.      
### Enable unshare:
Ruri supports unshare, it's recommended to enable this feature for better security.      
Unshare container will use pivot_root(2) instead chroot(2), so it's more secure.      
### Mount other mountpoints as read-only:
Ruri supports using `-m` option to mount other device/img/dir into container, if you only need read access to the mountpoint, try using `-M` option to make them read-only.      
## Geek:
### Seccomp:
Ruri has a built-in Seccomp profile, you can enable it by using `-s` option.      
If this profile does not fit your needs, you can edit src/seccomp.c and write your own Seccomp rules.      
## Radical:
### No new privs:
Ruri supports enable no_new_privs bit by `-n` option, after enabling this, command like `sudo` will be unavailable for common user.      
### Mount / as read-only:
Ruri supports mounting the rootfs of container as read-only by using `-R` option, this will make all the container read-only.      
### Do not create runtime dirs:
/dev, /proc and /sys will not be mounted if you enable `-j` option.      
### Disable network:
You can use `-x` option to create a new net ns and disable network for container.      
# Other built-in protections:
## Devices in /dev.
For /dev, ruri will only create necessary devices on it,  so that block devices will always be unavailable in container, and as cap_mknod and cap_sys_admin is dropped by default, you can not escape from ruri container by modifying disk partitions.      
## Masked dirs:
Ruri will mask some directories with tmpfs in /proc and /sys, this can protect the host to avoid security issues.      
## Capabilities: 
Ruri will drop unneeded capabilities by default, so that it can avoid escaping from container.      