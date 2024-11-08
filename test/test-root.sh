#!/bin/bash
source global.sh

# This will set $TEST_ROOT
export TEST_ROOT=$(pwd)

DESCRIPTION="This is a test script that runs all test scripts."
echo -e "${BASE}Running $0"
echo -e "${BASE}Description:\n${CYAN} ${DESCRIPTION}"
printf "${CLEAR}"
sleep 1

# This will set $TMPDIR
cd ${TEST_ROOT}
source init-root-test.sh
check_return_value $?

# Do all tests
cd ${TEST_ROOT}
i=1
while true; do
  if [[ $(ls root/$i-*.sh 2>/dev/null) == "" ]]; then
    break
  fi
  source root/$i-*.sh
  cd ${TEST_ROOT}
  i=$((i + 1))
done

cd ${TEST_ROOT}
source clean.sh
