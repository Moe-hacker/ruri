cd ${TEST_ROOT}
source global.sh

export TEST_NO=1
export DESCRIPTION="This is ruri basic test."
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Chroot container with no args"
show_subtest_description
cd ${TMPDIR}
./ruri ./test /bin/true
check_return_value $?
if ! mountpoint -q ./test/sys;then
    error "Seems that container did not mounted properly!"
fi
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Umount container"
show_subtest_description
cd ${TMPDIR}
./ruri -U ./test
check_return_value $?
if mountpoint -q ./test/sys;then
    error "Seems that container did not unmounted properly!"
fi
pass_subtest

pass_test