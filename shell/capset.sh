#!/usr/bin/env bash
DROP_CAPLIST=$(whiptail --title "Capability list" --checklist \
  "Choose which capability should be dropped\nUse space key to select, press Enter to continue" 16 60 8 \
  ${CAPLIST} 3>&1 1>&2 2>&3)
echo ${DROP_CAPLIST}
