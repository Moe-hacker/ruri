#!/usr/bin/env bash
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
echo "CAPLIST=\"${CAPLIST}\""
i=0
for DISTRO in $(rootfstool list -m tuna | cut -d " " -f 2); do
  echo "\"$DISTRO\""
  if [[ $DISTRO != $(printf "\033[0m") ]]; then
    i=$((i + 1))
    DISTROLIST+="$i $DISTRO "
  fi
done
echo "DISTROLIST=\"${DISTROLIST}\""
