# @configure_input@
bin_PROGRAMS=midwife
midwife_SOURCES=src/midwife.cpp src/lexer.cpp src/lexer.hpp
DISTCLEANFILES=testsuite.log atlocal atconfig
MAINTAINERCLEANFILES=@srcdir@/src/lexer.cpp aclocal.m4 package.m4
EXTRA_DIST=@srcdir@/src/lexer.cpp.in tests/testsuite.at \
	   tests/testsuite $(MAINTAINERCLEANFILES)
AM_CPPFLAGS='-I@srcdir@/src'

RE2C = @RE2C@

clean-local: clean-local-testsuite

.PHONY: clean-local-lexer clean-local-testsuite clobber

clobber: maintainer-clean
	@printf 'To rebuild, run ./autogen.sh\n'
	rm -f configure Makefile.in

clean-local-testsuite:
	rm -rf testsuite.dir

if HAS_RE2C
# Do not delete src/lexer.cpp if the user could not recreate it
CLEANFILES=@srcdir@/src/lexer.cpp

@srcdir@/src/lexer.cpp: src/lexer.cpp.in
	  $(RE2C) -o '@srcdir@/src/lexer.cpp' '@srcdir@/src/lexer.cpp.in'
endif

check:
	'@srcdir@/tests/testsuite'

installcheck-local:
	'@srcdir@/tests/testsuite' 'midwife_bindir=$(bindir)'
