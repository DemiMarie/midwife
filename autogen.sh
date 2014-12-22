#!/bin/sh
var=${0%/*}
cd -- "${var:-.}"

# Clean cache
rm autom4te.cache -r

# M4 code in configure.ac package.m4 automatically
rm package.m4

autoreconf --install -Wall
autom4te -Wall \
	--language=autotest \
	--output=tests/testsuite \
	tests/testsuite.at
