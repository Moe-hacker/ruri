cd ${TEST_ROOT}
source global.sh

export TEST_NO=3
export DESCRIPTION="Test if capability control works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Default capability"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep CapBnd| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(capsh --decode=$(cat test/cap) | grep cap_sys_admin)" != "" ]]; then
    error "Found cap_sys_admin, default capabitily is not set properly!"
fi
echo -e "${BASE}==> Default capability works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Capability limit of mknod()"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
mknod /dev/n c 1 3
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_failed $?
echo -e "${BASE}==> mknod() is not allowed"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=3
export SUBTEST_DESCRIPTION="Capability limit of mount()"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
mount -t tmpfs none /mnt
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_failed $?
echo -e "${BASE}==> mount() is not allowed"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=4
export SUBTEST_DESCRIPTION="Add capability CAP_SYS_ADMIN"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep CapBnd| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
./ruri -k cap_sys_admin ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(capsh --decode=$(cat test/cap) | grep cap_sys_admin)" == "" ]]; then
    error "Keep cap cap_sys_admin is not set properly!"
fi
echo -e "${BASE}==> Keep cap cap_sys_admin works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=5
export SUBTEST_DESCRIPTION="Drop capability CAP_CHOWN"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep CapBnd| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
./ruri -d cap_chown ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(capsh --decode=$(cat test/cap) | grep cap_chown)" != "" ]]; then
    error "Drop cap cap_chown is not set properly!"
fi
echo -e "${BASE}==> Drop cap cap_chown works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=6
export SUBTEST_DESCRIPTION="Drop all capabilities"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep CapBnd| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
for i in $(seq 0 40); do
    DROP_CAP="$DROP_CAP -d $i"
done
./ruri $DROP_CAP ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(capsh --decode=$(cat test/cap) | cut -d '=' -f 2)" != "" ]]; then
    error "Cannot drop all capabilities!"
fi
echo -e "${BASE}==> Drop all capabilities works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=7
export SUBTEST_DESCRIPTION="Keep all capabilities(privileged)"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep CapBnd| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
./ruri -p ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(capsh --decode=$(cat test/cap) | grep "cap_chown,cap_dac_override,cap_dac_read_search,cap_fowner,cap_fsetid,cap_kill,cap_setgid,cap_setuid,cap_setpcap,cap_linux_immutable,cap_net_bind_service,cap_net_broadcast,cap_net_admin,cap_net_raw,cap_ipc_lock,cap_ipc_owner,cap_sys_module,cap_sys_rawio,cap_sys_chroot,cap_sys_ptrace,cap_sys_pacct,cap_sys_admin,cap_sys_boot,cap_sys_nice,cap_sys_resource,cap_sys_time,cap_sys_tty_config,cap_mknod,cap_lease,cap_audit_write,cap_audit_control,cap_setfcap,cap_mac_override,cap_mac_admin,cap_syslog")" == "" ]]; then
    error "Cannot keep all capabilities!"
fi
echo -e "${BASE}==> Keep all capabilities works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=8
export SUBTEST_DESCRIPTION="Drop all capabilities but keep CAP_SYS_ADMIN"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep CapBnd| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
for i in $(seq 0 40); do
    DROP_CAP="$DROP_CAP -d $i"
done
./ruri $DROP_CAP -k cap_sys_admin ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(capsh --decode=$(cat test/cap) | cut -d '=' -f 2)" != "cap_sys_admin" ]]; then
    error "Cannot drop all capabilities except CAP_SYS_ADMIN!"
fi
echo -e "${BASE}==> Drop all capabilities but keep CAP_SYS_ADMIN works properly"
./ruri -U ./test
pass_subtest

pass_test
