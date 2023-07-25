#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
#
#
#  This file is part of ruri, with ABSOLUTELY NO WARRANTY.
#
#  MIT License
#
#  Copyright (c) 2022-2023 Moe-hacker
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#
##############
# 100% shit-code here...
# I can only promise that it works...
CAPSET=$(capsh --print | grep Bounding | cut -d "=" -f 2)
while [[ $(echo ${CAPSET} | grep ",") != "" ]]; do
  CAP=$(echo ${CAPSET} | cut -d "," -f 1)
  ON=false
  for i in cap_dac_read_search cap_linux_immutable cap_net_broadcast cap_net_admin cap_ipc_lock cap_ipc_owner cap_sys_module cap_sys_rawio cap_sys_ptrace cap_sys_pacct cap_sys_admin cap_sys_boot cap_sys_nice cap_sys_resource cap_sys_time cap_sys_tty_config cap_lease cap_audit_control cap_mac_override cap_mac_admin cap_syslog cap_wake_alarm; do
    if [[ $i == ${CAP} ]]; then
      ON=true
      CAPLIST+="${CAP} $(capsh --explain=${CAP} | head -n 1 | awk '{print $2}') ON "
      break
    fi
  done
  if [[ ${ON} != "true" ]]; then
    CAPLIST+="${CAP} $(capsh --explain=${CAP} | head -n 1 | awk '{print $2}') OFF "
  fi
  CAPSET=$(echo ${CAPSET} | cut -d "," -f 2-)
done
CAP=${CAPSET}
ON=false
for i in cap_dac_read_search cap_linux_immutable cap_net_broadcast cap_net_admin cap_ipc_lock cap_ipc_owner cap_sys_module cap_sys_rawio cap_sys_ptrace cap_sys_pacct cap_sys_admin cap_sys_boot cap_sys_nice cap_sys_resource cap_sys_time cap_sys_tty_config cap_lease cap_audit_control cap_mac_override cap_mac_admin cap_syslog cap_wake_alarm; do
  if [[ $i == ${CAP} ]]; then
    ON=true
    CAPLIST+="${CAP} $(capsh --explain=${CAP} | head -n 1 | awk '{print $2}') ON "
    break
  fi
done
if [[ ${ON} != "true" ]]; then
  CAPLIST+="${CAP} $(capsh --explain=${CAP} | head -n 1 | awk '{print $2}') OFF "
fi
i=0
for DISTRO in $(rootfstool list -m tuna | cut -d " " -f 2); do
  echo "\"$DISTRO\""
  if [[ $DISTRO != $(printf "\033[0m") ]]; then
    i=$((i + 1))
    DISTROLIST+="$i $DISTRO "
  fi
done
echo "CAPLIST=\"${CAPLIST}\""
echo "DISTROLIST=\"${DISTROLIST}\""
