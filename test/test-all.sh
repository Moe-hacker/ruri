#!/bin/bash
source global.sh

# This will set $TEST_ROOT
export TEST_ROOT=$(pwd)

DESCRIPTION="This is a test script that runs all test scripts."
echo -e "${BASE}Running $0"
echo -e "${BASE}Description:\n${CYAN} ${DESCRIPTION}"
printf "${CLEAR}"

# This will set $TMPDIR
sudo bash init-test.sh
check_return_value $?
