#!/bin/bash
source global.sh

for i in $(mount | grep ${TMPDIR} | awk '{print $3}'); do
  umount -lvf $i
done
echo -e "${BASE}Remove ${TMPDIR}"
rm -rf ${TMPDIR}
