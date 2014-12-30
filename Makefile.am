# @configure_input@
autotools_output=aclocal.m4 package.m4 tests/testsuite
bin_PROGRAMS=midwife
midwife_SOURCES=src/midwife.cpp src/lexer.cpp src/lexer.hpp
DISTCLEANFILES=testsuite.log atlocal atconfig
MAINTAINERCLEANFILES=$(autotools_output) @srcdir@/src/lexer.cpp
EXTRA_DIST=@srcdir@/src/lexer.cpp.in tests/testsuite.at \
	   autogen.sh $(autotools_output)
AM_CPPFLAGS='-I@top_srcdir@/src'

clean-local:

.PHONY: clean-local-lexer clean-local-testsuite clobber

clobber: maintainer-clean
	@printf 'To rebuild, run ./autogen.sh\n'
	rm -f configure Makefile.in

if HAS_RE2C
# Do not delete src/lexer.cpp if the user could not recreate it
CLEANFILES=@srcdir@/src/lexer.cpp

@srcdir@/src/lexer.cpp: src/lexer.cpp.in
	. '@top_srcdir@/missing' '@RE2C@' -o '@srcdir@/src/lexer.cpp' \
	'@srcdir@/src/lexer.cpp.in'
endif

check:
	'@top_srcdir@/tests/testsuite'

installcheck-local:
	'@top_srcdir@/tests/testsuite' 'midwife_bindir=$(bindir)'

@top_srcdir@/tests/testsuite: @top_srcdir@/tests/testsuite.at
	cd '@top_srcdir@' && \
	. ./missing autom4te --language=autotest \
		-Wall -Werror \
		--output=tests/testsuite \
		tests/testsuite.at
