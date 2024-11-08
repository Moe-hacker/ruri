#!/bin/bash
source global.sh

TEST_NO=0
DESCRIPTION="This script is used to create files and directories for testing."
echo -e "${BASE}Running test ${CYAN}#${TEST_NO}${BASE} $0"
echo -e "${BASE}Description:\n${CYAN} ${DESCRIPTION}"
printf "${CLEAR}"
sleep 1

export TMPDIR=tmpdir-$RANDOM

echo -e "${BASE}Building ruri"
printf "${CLEAR}"
cd ..
mkdir ${TMPDIR}
check_return_value $?
export TMPDIR=$(realpath ${TMPDIR})
./configure -d
check_return_value $?
make
check_return_value $?

echo -e "${BASE}Copy ruri to ${TMPDIR}"
printf "${CLEAR}"
mv ruri ${TMPDIR}
check_return_value $?
cd ${TMPDIR}

echo -e "${BASE}Get rootfs"
printf "${CLEAR}"
git clone https://github.com/moe-hacker/rootfstool
rootfstool/rootfstool d -d alpine -v edge
check_return_value $?
rm -rf rootfstool
check_return_value $?

echo -e "${BASE}Create test.img"
printf "${CLEAR}"
if [[ -e /tmp/test ]]; then
  rm /tmp/test
fi
if [[ -d /tmp/test ]]; then
  ./ruri -U /tmp/test
  rm -rf /tmp/test
fi
dd if=/dev/zero of=test.img bs=1M count=256
check_return_value $?
mkfs.ext4 test.img
check_return_value $?
mkdir /tmp/test
check_return_value $?
LOOPFILE=$(losetup -f)
losetup ${LOOPFILE} ./test.img
mount ${LOOPFILE} /tmp/test
check_return_value $?
tar -xf rootfs.tar.xz -C /tmp/test
check_return_value $?
umount -lvf /tmp/test
check_return_value $?

echo -e "${BASE}Create test2.img"
printf "${CLEAR}"
dd if=/dev/zero of=test2.img bs=1M count=256
check_return_value $?
mkfs.ext4 test2.img
check_return_value $?
LOOPFILE=$(losetup -f)
losetup ${LOOPFILE} ./test2.img
mount ${LOOPFILE} /tmp/test
check_return_value $?
touch /tmp/test/test.txt
check_return_value $?
echo "xxxxxxxxxxxx" >/tmp/test/test.txt
check_return_value $?
umount -lvf /tmp/test
check_return_value $?
