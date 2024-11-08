#!/bin/bash
source global.sh

for i in $(mount | grep ${TMPDIR} | awk '{print $3}'); do
  umount -lvf $i >/dev/null 2>&1
done
cd ${TMPDIR}
./ruri -U ./test
echo -e "${BASE}Remove ${TMPDIR}"
#rm -rf ${TMPDIR}
