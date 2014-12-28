#!/bin/sh --
dir=${0%/*}
cd -- "${dir:-.}" &&
./autogen.sh &&
chmod 700 -R build &&
rm -r build &&
mkdir build &&
cd build &&
../configure "$@" &&
make ${1+"-j$1"} &&
make check &&
make distcheck
