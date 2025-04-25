#!/bin/sh
# SPDX-License-Identifier: MIT

################################################################################
#
# Author: Moe-hacker
#
################################################################################

set -e

# only use the tools that are really needed, not the full build tools and features
# autoreconf -fi

# generate aclocal.m4 file and configure script
aclocal
autoconf
