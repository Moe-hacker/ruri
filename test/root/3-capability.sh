cd ${TEST_ROOT}
source global.sh

export TEST_NO=3
export DESCRIPTION="Test capability works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Default capability"
show_subtest_description
cd ${TMPDIR}
cat <<EOF > test/test.sh
cat /proc/self/status | grep CapEff| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
./ruri ./test /test.sh
check_if_succeed $?
if [[ "`capsh --decode=$(cat test/cap)|grep cap_sys_admin`"  != "" ]];then
    error "Found cap_sys_admin, default capabitily is not set properly!"
fi
echo -e "${BASE}==> Default capability works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Capability limit of mknod()"
show_subtest_description
cd ${TMPDIR}
cat <<EOF > test/test.sh
mknod /dev/n c 1 3
EOF
chmod 777 test/test.sh
./ruri ./test /test.sh
check_if_failed $?
echo -e "${BASE}==> mknod() is not allowed"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=3
export SUBTEST_DESCRIPTION="Capability limit of mount()"
show_subtest_description
cd ${TMPDIR}
cat <<EOF > test/test.sh
mount -t tmpfs none /mnt
EOF
chmod 777 test/test.sh
./ruri ./test /test.sh
check_if_failed $?
echo -e "${BASE}==> mount() is not allowed"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=4
export SUBTEST_DESCRIPTION="Add capability CAP_SYS_ADMIN"
show_subtest_description
cd ${TMPDIR}
cat <<EOF > test/test.sh
cat /proc/self/status | grep CapEff| awk '{print \$2}' > /cap
EOF
chmod 777 test/test.sh
./ruri -k cap_sys_admin ./test /test.sh
check_if_succeed $?
if [[ "`capsh --decode=$(cat test/cap)|grep cap_sys_admin`"  == "" ]];then
    error "Keep cap cap_sys_admin is not set properly!"
fi
echo -e "${BASE}==> Keep cap cap_sys_admin works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=5
export SUBTEST_DESCRIPTION="Drop capability CAP_CHOWN"
show_subtest_description
cd ${TMPDIR}
cat <<EOF > test/test.sh
cat /proc/self/status | grep CapEff| cut -d' ' -f2 > /cap
EOF
chmod 777 test/test.sh
./ruri -d cap_chown ./test /test.sh
check_if_succeed $?
if [[ "`capsh --decode=$(cat test/cap)|grep cap_chown`"  != "" ]];then
    error "Drop cap cap_chown is not set properly!"
fi
echo -e "${BASE}==> Drop cap cap_chown works properly"
./ruri -U ./test
pass_subtest

pass_test