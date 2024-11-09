#!/bin/bash
# SPDX-License-Identifier: MIT
#
#
# This file is part of ruri, with ABSOLUTELY NO WARRANTY.
#
# MIT License
#
# Copyright (c) 2024 Moe-hacker
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
UNAME_ARCH=$(uname -m)
case ${UNAME_ARCH} in
armv7* | armv8l) CPU_ARCH="armhf" ;;
armv[1-6]*) CPU_ARCH="armv7" ;;
aarch64 | armv8* | arm64 | arm*) CPU_ARCH="aarch64" ;;
x86_64 | amd64) CPU_ARCH="x86_64" ;;
i*86 | x86) CPU_ARCH="i386" ;;
risc*) CPU_ARCH="riscv64" ;;
s390*) ARCH_TYPE="s390x" ;;
ppc*) ARCH_TYPE="ppc64le" ;;
loong*) ARCH_TYPE="loongarch64" ;;
*) CPU_ARCH=${UNAME_ARCH} ;;
esac
if [ -z "${CPU_ARCH}" ]; then
    if [[ $1 == "-s" ]]; then
        echo "Cannot detect CPU architecture"
        echo "Supported CPU architectures: arm64, armv7, armhf, riscv64, i386, loongarch64, s390x, ppc64le and x86_64"
        exit 1
    fi
    echo "Cannot detect CPU architecture"
    echo "Supported CPU architectures: armv7, aarch64, x86_64, i386, riscv64"
    read -p "please input CPU architecture: " CPU_ARCH
fi
if ! command -v wget &>/dev/null; then
    echo "wget is not installed"
    exit 1
fi
rm ${CPU_ARCH}.tar >/dev/null 2>&1
wget https://github.com/Moe-hacker/ruri/releases/latest/download/${CPU_ARCH}.tar
if [[ $? != 0 ]]; then
    echo "Failed to download ruri"
    echo "Please check your network or download ruri manually"
    echo "If ruri has a new release, please wait for build completion"
    exit 1
fi
tar -xf ${CPU_ARCH}.tar >/dev/null 2>&1
rm -f ${CPU_ARCH}.tar
rm -f LICENSE
chmod +x ruri
echo "ruri has been downloaded successfully"
if [[ $1 == "-s" ]]; then
    exit 0
fi
read -p "Do you want to install ruri to $PREFIX/bin? [y/n]: " INSTALL
if [[ ${INSTALL} == "y" ]]; then
    sudo mv ruri $PREFIX/bin/ || mv ruri $PREFIX/bin/
    if [[ $? != 0 ]]; then
        echo "Failed to install ruri"
        echo "Please check your permission"
        exit 1
    fi
    echo "ruri has been installed to $PREFIX/bin"
fi
