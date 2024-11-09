export BASE="\033[1;38;2;254;228;208m"
export RED="\033[31m"
export GREEN="\033[32m"
export YELLOW="\033[33m"
export BLUE="\033[34m"
export PURPLE="\033[35m"
export CYAN="\033[36m"
export CLEAR="\033[0m"

function error() {
    cd ${TEST_ROOT}
    source clean.sh
    echo -e "${RED}\nFailed on: ${GREEN} #${TEST_NO}"
    echo -e "${RED}Description: ${CYAN} ${DESCRIPTION}"
    echo -e "${RED}Subtest: ${CYAN} ${SUBTEST_NO}"
    echo -e "${RED}Subtest Description: ${CYAN} ${SUBTEST_DESCRIPTION}"
    echo -e "${CLEAR}\n"
    printf "${RED}$@\n${CLEAR}"
    exit 1
}

function check_if_succeed() {
    if [[ $1 == "0" ]]; then
        return 0
    elif [[ $1 == "114" ]]; then
        error "ruri panic signal found!"
    else
        error "failed!"
    fi
}

function check_if_failed() {
    if [[ $1 == "0" ]]; then
        error "succeed, but expected failed!"
    else
        return 0
    fi
}

function show_test_description() {
    echo -e "${BASE}\nRunning test ${GREEN}#${TEST_NO}"
    echo -e "${BASE}Description:\n${CYAN} ${DESCRIPTION}"
    printf "${CLEAR}\n"
    sleep 2
}

function show_subtest_description() {
    echo -e "${BASE}\nRunning subtest ${GREEN}#${SUBTEST_NO} ${BASE}of test ${GREEN}#${TEST_NO}"
    echo -e "${BASE}Subtest Description:\n${CYAN} ${SUBTEST_DESCRIPTION}"
    printf "${CLEAR}\n"
    sleep 2
}

function pass_test() {
    echo -e "${BASE}\nPassed test${GREEN} #${TEST_NO}"
    printf "${CLEAR}\n"
}

function pass_subtest() {
    echo -e "${BASE}\nPassed subtest${GREEN} #${SUBTEST_NO} ${BASE}of test ${GREEN}#${TEST_NO}"
    printf "${CLEAR}\n"
}
