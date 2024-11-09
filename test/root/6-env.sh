cd ${TEST_ROOT}
source global.sh

export TEST_NO=6
export DESCRIPTION="Test if -e option works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Environment variable test"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
#!/bin/sh
if [ "\$x" == "xxxx" ];then
    exit 0
else
    exit 1
fi
EOF
chmod +x test/test.sh
./ruri -e x xxxx ./test /bin/sh /test.sh
check_if_succeed $?
echo -e "${BASE}==> Environment variable test \$x=xxxx passed!${CLEAR}\n"
./ruri -U ./test
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Environment variable test"
show_subtest_description
cd ${TMPDIR}
cat <<EOF >test/test.sh
#!/bin/sh
if [ "\$x" != "xxxx" ];then
    exit 1
fi
if [ "\$y" != "xxxx" ];then
    exit 1
fi
exit 0
EOF
chmod +x test/test.sh
./ruri -e x xxxx -e y xxxx ./test /bin/sh /test.sh
check_if_succeed $?
echo -e "${BASE}==> Environment variable test \$x=xxxx \$y=xxxx passed!${CLEAR}\n"
./ruri -U ./test
pass_subtest

pass_test
