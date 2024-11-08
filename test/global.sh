export BASE="\033[1;38;2;254;228;208m"
export RED="\033[31m"
export GREEN="\033[32m"
export YELLOW="\033[33m"
export BLUE="\033[34m"
export PURPLE="\033[35m"
export CYAN="\033[36m"
export CLEAR="\033[0m"
error() {
  cd $TEST_ROOT
  bash clean.sh
  printf "${RED}$@\n${CLEAR}"
  exit 1
}
function check_return_value() {
  if [[ $1 == "0" ]]; then
    return 0
  elif [[ $1 == "114" ]]; then
    error "ruri panic signal found!"
  else
    error "failed"
  fi
}
