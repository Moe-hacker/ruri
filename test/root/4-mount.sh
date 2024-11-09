cd ${TEST_ROOT}
source global.sh

export TEST_NO=4
export DESCRIPTION="Test if mount function works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Mount test.img as rootfs"
show_subtest_description
cd ${TMPDIR}
mkdir ./t >/dev/null 2>&1
./ruri -m test.img / ./t /bin/echo -e "${BASE}==> Running echo command in container"
check_if_succeed $?
if [[ ! -e ./t/bin/sh ]]; then
    error "Seems that container did not mounted properly!"
fi
echo -e "${BASE}==> test.img mounted successfully"
./ruri -U ./t
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Mount ./test2.img as /m"
show_subtest_description
cd ${TMPDIR}
mkdir ./t >/dev/null 2>&1
./ruri -m test.img / -m test2.img /m ./t /bin/echo -e "${BASE}==> Running echo command in container"
check_if_succeed $?
if [[ ! -e ./t/bin/sh ]]; then
    error "Seems that container did not mounted properly!"
fi
if [[ "$(cat ./t/m/test.txt)" != "x" ]]; then
    error "test2.img does not mounted properly!"
fi
echo -e "${BASE}==> ./test2.img mounted as /m successfully"
./ruri -U ./t
pass_subtest

export SUBTEST_NO=3
export SUBTEST_DESCRIPTION="Mount ./test2.img as /m and /n"
show_subtest_description
cd ${TMPDIR}
mkdir ./t >/dev/null 2>&1
./ruri -m test.img / -m test2.img /m -m test2.img /n ./t /bin/echo -e "${BASE}==> Running echo command in container"
check_if_succeed $?
if [[ ! -e ./t/bin/sh ]]; then
    error "Seems that container did not mounted properly!"
fi
if [[ "$(cat ./t/m/test.txt)" != "x" ]]; then
    error "test2.img does not mounted properly!"
fi
if [[ "$(cat ./t/n/test.txt)" != "x" ]]; then
    error "test2.img does not mounted properly!"
fi
echo -e "${BASE}==> ./test2.img mounted as /m and /n successfully"
./ruri -U ./t
pass_subtest

export SUBTEST_NO=4
export SUBTEST_DESCRIPTION="Mount ./test3 as /t"
show_subtest_description
cd ${TMPDIR}
mkdir ./test3 >/dev/null 2>&1
echo x >test3/test.txt
./ruri -m ./test3 /t ./test /bin/echo -e "${BASE}==> Running echo command in container"
if [[ "$(cat ./test/t/test.txt)" != "x" ]]; then
    error "test3 does not mounted properly!"
fi
echo -e "${BASE}==> ./test3 mounted as /t successfully"
./ruri -U ./test
pass_subtest

pass_test
