cd ${TEST_ROOT}
source global.sh

export TEST_NO=2
export DESCRIPTION="Test if /proc, /sys and /dev works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="/dev/zero"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
dd if=/dev/zero of=/nullfile bs=1M count=1
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_succeed $?
if [[ ! -e test/nullfile ]]; then
    error "File /nullfile does not exist!"
fi
if [[ $(stat -c %s test/nullfile) -ne 1048576 ]]; then
    error "File /nullfile size is not 1M!"
fi
echo -e "${BASE}==> /dev/zero works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="/dev/urandom"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
dd if=/dev/urandom of=/randomfile bs=1M count=1
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_succeed $?
if [[ ! -e test/randomfile ]]; then
    error "File /randomfile does not exist!"
fi
if [[ $(stat -c %s test/randomfile) -ne 1048576 ]]; then
    error "File /randomfile size is not 1M!"
fi
echo -e "${BASE}==> /dev/urandom works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=3
export SUBTEST_DESCRIPTION="/dev/null"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
if [ "$(echo "Hello World" >/dev/null)" != "" ];then
    exit 1
fi
exit 0
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_succeed $?
echo -e "${BASE}==> /dev/null works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=4
export SUBTEST_DESCRIPTION="/dev/stdout"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
if [ "$(echo "Hello World" >/dev/stdout)" != "Hello World" ];then
    exit 1
fi
exit 0
EOF
chmod 777 test/test.sh
./ruri ./test /bin/sh /test.sh
check_if_succeed $?
echo -e "${BASE}==> /dev/stdout works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=5
export SUBTEST_DESCRIPTION="/proc/self/status"
show_subtest_description
cd ${TMPDIR}
./ruri ./test /bin/cat /proc/self/status
check_if_succeed $?
echo -e "${BASE}==> /proc/self/status works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=6
export SUBTEST_DESCRIPTION="/proc/$$/status"
show_subtest_description
cd ${TMPDIR}
./ruri ./test /bin/cat /proc/$$/status
check_if_succeed $?
echo -e "${BASE}==> /proc/$$/status works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=7
export SUBTEST_DESCRIPTION="masked dirs, in privileged container"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
echo 1048576 > /proc/sys/fs/pipe-max-size
EOF
chmod 777 test/test.sh
./ruri -p ./test /bin/sh /test.sh
check_if_failed $?
echo -e "${BASE}==> /proc/sys/fs/pipe-max-size is masked"
./ruri -U ./test
pass_subtest

pass_test
