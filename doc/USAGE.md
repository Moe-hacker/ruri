# Usage:
```
ruri [OPTIONS]...
ruri [ARGS]... [CONTAINER_DIRECTORY]... [COMMAND [ARGS]...]
```
## Options:
```
-v, --version ...............................: Show version info
-V, --version-code ..........................: Show version code
-h, --help ..................................: Show helps
-H, --show-examples .........................: Show commandline examples
-P, --ps [container_dir/config] .............: Show process status of the container
```
These four options will show the info.
********************************************
```
-U, --umount [container_dir/config] .........: Umount a container
```
When running a container, ruri needs to mount some directories on it.         
And after running the container, you can use `-U` option to umount a container.          
This option needs to be run with root(sudo).      
WARNING: Always do `sudo ruri -U /path/to/container` before you removing the container.      
***********************************
```
-C, --correct-config .................: Correct config.
```
Try to correct an incomplete config file.        
## Arguments:
Common ruri container should be run with sudo, but you can also use `-r` option to run rootless container if you want.      
*****************************************
```
-D, --dump-config ...........................: Dump the config
```
ruri supports using config file, you can use `-D` option to dump current config of container.      
For example:      
```
ruri -D -k cap_sys_admin -d cap_sys_chroot ./t
```
This will dump the container config with `-k cap_sys_admin -d cap_sys_chroot`, so next time  you can just use the config instead of `-k cap_sys_admin -d cap_sys_chroot` argument.      
********************************************
```
-o, --output [config file] ..................: Set output file of `-D` option
```
This option is used for `-D` option, to save the config to a file.      
For example:
```
ruri -D -o test.conf -k cap_sys_admin -d cap_sys_chroot ./t
```
This will save config to test.conf.      
*****************************************
```
-c, --config [config] [args] [COMMAND [ARGS]]: Use config file
```
You can use `ruri -c config_file` to run a container with config file.      
For example:      
```
ruri -c test.conf
```
or:      
```
ruri -c test.conf -k cap_sys_admin /bin/su root -
```      
This will run container using test.conf.
***********************************************
```      
-a, --arch [arch] ...........................: Simulate architecture via binfmt_misc/QEMU
-q, --qemu-path [path] ......................: Specify the path of QEMU
```
These two arguments should be set at the same time.      
ruri supports to use qemu-user-static with the binfmt_misc feature of kernel to run cross-arch containers.      
`-q` option can use qemu path in host, it will be copied to /qemu-ruri in container.      
For example:      
```
ruri -q /usr/bin/qemu-x86_64-static -a x86_64 ./test-x86_64
```
But remember that do not use this feature to simulate host architecture.      
Note: This option need kernel support for binfmt_misc.      
*******************************************************************
```
-u, --unshare ...............................: Enable unshare feature
```
ruri supports unshare container, but NET and USER namespace is not supported.        
Note: when PID 1 died in PID NS, the ns will be cleared, so all process in it will die.      
Note: This option need kernel support for namespaces, it will try to enable supported ns, but if failed, it will only show warnings.     
*****************************************
```
-n, --no-new-privs ..........................: Set NO_NEW_PRIVS flag
```
This argument will set NO_NEW_PRIVS, commands like `sudo` will be unavailable for common user.      
****************************************
```
-N, --no-rurienv ............................: Do not use .rurienv file
```
ruri will create /.rurienv in container to save container config by default, you can use this option to disable it.      
*********************************************
```
-s, --enable-seccomp ........................: Enable built-in Seccomp profile
```
ruri provides a built-in seccomp profile, but if you really need to use seccomp, you might need to edit src/seccomp.c with your own rules and recompile it.      
Note: This option need kernel support seccomp.
****************************************
```
-p, --privileged ............................: Run privileged container
```
This argument will give all capabilities to container, but you can also use `-d` option to filter out capabilities you don't want to keep.      
*******************************************
```
-r, --rootless ..............................: Run rootless container
```
This option should be run with common user, so you can run rootless container with user ns.      
This option require `uidmap` package and user namespace support.      
Note: This option need user ns support, and need kernel to allow create user ns with common user.      
*********************************************
```
-k, --keep [cap] ............................: Keep the specified capability
-d, --drop [cap] ............................: Drop the specified capability
```
This two option can control the capability in container, cap can both be value or name.
For example, `-k cap_chown` have the same effect with `-k 0`.      
**************************************************
```
-e, --env [env] [value] .....................: Set environment variables to its value
```
A very useless function, I hope it works.      
*********************************************
```
-m, --mount [dir/dev/img/file] [target] .....: Mount dir/block-device/image/file to target
-M, --ro-mount [dir/dev/img/file] [target] ..: Mount dir/block-device/image/file as read-only
```
ruri provides a powerful mount function, here are some examples:
```
ruri -m /dev/sda1 / ./test
```
This command will mount /dev/sda1 to ./test and run container.      
```
ruri -m ./test.img / ./test
```
This command will mount ./test.img to ./test and run container.       
```
ruri -m /sdcard /sdcard ./test
```
This command will mount /sdcard to ./test/sdcard and run container.       
It can also bind-mount file/FIFO/socket.      
******************************************
```
-S, --host-runtime ..........................: Bind-mount /dev/, /sys/ and /proc/ from host
```
ruri will create /dev/, /sys/ and /proc/ after chroot(2) into container for better security. You can use `-S` option to force it to bind-mount system runtime dirs.    
*************************************
```
-R, --read-only .............................: Mount / as read-only
```
This will make the whole container rootfs read-only.
***********************************************
```
-l, --limit [cpuset=cpu/memory=mem] .........: Set cpuset/memory limit
```
ruri currently supports cpuset and memory cgroup.            
Each `-l` option can only set one of the cpuset/memory limits      
for example:       
```
ruri -l memory=1M -l cpuset=1 /test
```
Note: This option need kernel support for specified cgroup.      
**************************************************
```
-w, --no-warnings ...........................: Disable warnings
```
There might be some warnings when running ruri, if you don't like, use `-w` option to disable them.       
****************************************************
```
-f, --fork ..................................: fork() before exec the command
```
unshare and rootless container will always fork() before running commands in container,      
you can use this option to make common chroot container have the same behaiver,  
******************************************************       
```
-j, --just-chroot ...........................: Just chroot, do not create the runtime dirs
```
If you enable this option, ruri will not create runtime dirs(/dev, proc and /sys) in container.       
****************************************************
```
-W, --work-dir [dir]..........................: Change work directory in container.
```
default work directory is `/`, you can use this option to change it to other dirs.       
*********************************
```
-A, --unmask-dirs ............................: Unmask dirs in /proc and /sys
```
ruri will protect some files/dirs in /proc and /sys by default, use -A to disable this.      
********************
```
-E, --user ...................................: Set the user to run command in the container.
```
You can use this option to switch to a common user before exec(3).       
*************
```
-t, --hostname [hostname] ....................: Set hostname
```
Set hostname, only for unshare container.      
************
```
-x, --no-network .............................: Disable network
```
Disable network, this option need net ns support and will enable unshare at the same time.      
***********
```
-K, --use-kvm ...............................: Enable /dev/kvm support
```
Enable /dev/kvm for container.      
********
```
-I, --char-dev [device] [major] [minor] .....: Add a character device to container
```
Add a character device to container, for example `-I kvm 10 232` or `-I dri/card0 226 0`.      
**********
```
-i, --hidepid 1/2 ...........................: Hidepid for /proc
```
Hidepid option for /proc      
*********
```
-b, --background ............................: Fork to background
-L, --logfile [file] ........................: Set log file of -b option
```
Run ruri in background and set output file.      