cd ${TEST_ROOT}
source global.sh

export TEST_NO=9
export DESCRIPTION="Test if cross-arch container works properly"
show_test_description

export SUBTEST_NO=1
export SUBTEST_DESCRIPTION="Run aarch64 container on x86_64"
show_subtest_description
cd ${TMPDIR}
./ruri -a aarch64 -q /usr/bin/qemu-aarch64-static ./aarch64 dd if=/dev/zero of=/test bs=1M count=1
check_if_succeed $?
if [[ ! -e aarch64/test ]]; then
    error "Cannot run aarch64 container on x86_64!"
fi
echo -e "${BASE}==> Run aarch64 container on x86_64 works properly"
./ruri -U ./aarch64
pass_subtest

export SUBTEST_NO=2
export SUBTEST_DESCRIPTION="Run armhf container on x86_64"
show_subtest_description
cd ${TMPDIR}
./ruri -a armhf -q /usr/bin/qemu-arm-static ./armhf dd if=/dev/zero of=/test bs=1M count=1
check_if_succeed $?
if [[ ! -e armhf/test ]]; then
    error "Cannot run armhf container on x86_64!"
fi
echo -e "${BASE}==> Run armhf container on x86_64 works properly"
./ruri -U ./armhf
pass_subtest

pass_test
