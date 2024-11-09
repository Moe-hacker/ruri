cd ${TEST_ROOT}
source global.sh

export TEST_NO=7
export DESCRIPTION="Test if -P option works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="-P with common chroot container"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
#!/bin/sh
sleep 100
EOF
chmod +x test/test.sh
./ruri ./test /bin/sh /test.sh &
check_if_succeed $?
sleep 1
if [[ "$(./ruri -P ./test)" == "" ]]; then
    error "ruri -P has no output"
fi
./ruri -P ./test
echo -e "${BASE}==> -P for common chroot container passed!${CLEAR}\n"
./ruri -U ./test
pass_subtest

cd ${TMPDIR}
./ruri -P ./test | awk '{print $1}' | xargs kill -9

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="-P with stopped container"
show_subtest_description
cd ${TMPDIR}
if [[ "$(./ruri -P ./test)" != "" ]]; then
    error "ruri -P has output, expect not!"
fi
echo -e "${BASE}==> -P for stopped container passed!${CLEAR}\n"
./ruri -U ./test
pass_subtest

pass_test
