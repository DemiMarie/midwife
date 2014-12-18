#!/bin/sh
var=${0%/*}
cd -- "${var:-.}"
autoreconf
autom4te --language=autotest --output=tests/testsuite tests/testsuite.at
