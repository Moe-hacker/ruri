cd ${TEST_ROOT}
source global.sh

export TEST_NO=5
export DESCRIPTION="Test if read-only mount function works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Mount test.img as read-only rootfs"
show_subtest_description
cd ${TMPDIR}
mkdir ./t >/dev/null 2>&1
./ruri -M test.img / ./t touch /test.txt
check_if_failed $?
if [[ ! -e ./t/bin/sh ]]; then
    error "Seems that container did not mounted properly!"
fi
if [[ -e ./t/test.txt ]]; then
    error "Seems that container is not read-only!"
fi
echo -e "${BASE}==> test.img mounted as read-only successfully"
./ruri -U ./t
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Mount / as read-only rootfs (-R)"
show_subtest_description
cd ${TMPDIR}
./ruri -R ./test touch /test.txt
check_if_failed $?
if [[ -e ./test/test.txt ]]; then
    error "Seems that container is not read-only!"
fi
echo -e "${BASE}==> / mounted as read-only successfully"
./ruri -U ./test
pass_subtest

pass_test
