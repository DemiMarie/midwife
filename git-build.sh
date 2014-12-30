#!/bin/sh --
set -e
dir=${0%/*}
cd -- "${dir:-.}"
./autogen.sh
mkdir build 2>/dev/null || {
chmod 700 -R build &&
rm -rf build &&
mkdir build
}
(cd build
../configure "$@"
make ${1+"-j$1"}
make check
make distcheck
make clobber)
rmdir build/src
rmdir build
