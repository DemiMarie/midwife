#!/bin/sh -e
var=${0%/*}
cd -- "${var:-.}"

# Clean cache
rm autom4te.cache -rf

# M4 code in configure.ac generates package.m4 automatically
rm -f package.m4 aclocal.m4

autoreconf --install -Wall -Werror
exec autom4te -Wall -Werror \
	--language=autotest \
	--output=tests/testsuite \
	tests/testsuite.at
