cd ${TEST_ROOT}
source global.sh

export TEST_NO=8
export DESCRIPTION="Test if secure options works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="No new privs"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep NoNewPrivs| awk '{print \$2}' > /priv
EOF
chmod 777 test/test.sh
./ruri -n ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(cat test/priv)" != "1" ]]; then
    error "Cannot set no_new_privs!"
fi
echo -e "${BASE}==> No new privs works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Seccomp"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status | grep Seccomp| awk '{print \$2}' > /seccomp
EOF
chmod 777 test/test.sh
./ruri -n ./test /bin/sh /test.sh
check_if_succeed $?
if [[ "$(cat test/seccomp)" == "0" ]]; then
    error "Cannot set Seccomp!"
fi
echo -e "${BASE}==> Seccomp works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=3
export SUBTEST_DESCRIPTION="Just chroot"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/self/status
EOF
chmod 777 test/test.sh
./ruri -j ./test /bin/sh /test.sh
check_if_failed $?
echo -e "${BASE}==> Just chroot works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=4
export SUBTEST_DESCRIPTION="No rurienv"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /.rurienv
EOF
chmod 777 test/test.sh
./ruri -N ./test /bin/sh /test.sh
check_if_failed $?
echo -e "${BASE}==> No rurienv works properly"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=5
export SUBTEST_DESCRIPTION="Mount host runtime"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
cat /proc/mounts | grep /proc/block
EOF
chmod 777 test/test.sh
./ruri -S ./test /bin/sh /test.sh
check_if_failed $?
echo -e "${BASE}==> Mount host runtime works properly"
./ruri -U ./test
pass_subtest

pass_test
