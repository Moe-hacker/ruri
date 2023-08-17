# SPDX-License-Identifier: MIT
#
#
# This file is part of ruri, with ABSOLUTELY NO WARRANTY.
#
# MIT License
#
# Copyright (c) 2022-2023 Moe-hacker
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
is_enabled() {
  if [[ ${CONF_FILE} == *.gz ]]; then
    zcat ${CONF_FILE} | grep $1\=y >/dev/null
  else
    cat ${CONF_FILE} | grep $1\=y >/dev/null
  fi
}
if [[ $(id -u) != "0" ]]; then
  echo -e "\033[31mError: This script should be run with root privileges !" >&2
  exit 1
fi
for i in /proc/config.gz /boot/config-$(uname -r) /usr/src/linux-$(uname -r)/.config /usr/src/linux/.config; do
  if [[ -e $i ]]; then
    CONF_FILE=$i
    break
  fi
done
if [[ ${CONF_FILE} == "" ]]; then
  echo -e "\033[31mError: Can not find kernel config file !" >&2
  exit 1
fi
if (($(uname -r | cut -d "." -f 1) < 4)); then
  echo -e "\033[33mWarning: ruri has not been tested on Linux3.x or lower." >&2
fi
for i in CONFIG_HAVE_ARCH_SECCOMP CONFIG_HAVE_ARCH_SECCOMP_FILTER CONFIG_SECCOMP CONFIG_SECCOMP_FILTER CONFIG_UTS_NS CONFIG_USER_NS CONFIG_TIME_NS CONFIG_IPC_NS CONFIG_PID_NS; do
  if is_enabled $i; then
    echo -e "\033[1;38;2;254;228;208m$i \033[36G\033[35m:\033[32menabled"
  else
    echo -e "\033[1;38;2;254;228;208m$i \033[36G\033[35m:\033[31mmissing"
  fi
done
