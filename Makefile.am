# @configure_input@
bin_PROGRAMS=midwife midwife3
midwife_SOURCES=src/midwife.cpp src/lexer.cpp src/lexer.hpp
nodist_midwife3_SOURCES=
DISTCLEANFILES=testsuite.log atlocal atconfig
MAINTAINERCLEANFILES=aclocal.m4 package.m4 tests/testsuite
EXTRA_DIST=@top_srcdir@/src/lexer.cpp.in tests/testsuite.at \
	   autogen.sh $(MAINTAINERCLEANFILES)
AM_CPPFLAGS='-I@top_srcdir@/src'

midwife3$(EXEEXT): midwife$(EXEEXT)
	cp -p 'midwife$(EXEEXT)' 'midwife3$(EXEEXT)'

.PHONY: clean-local-lexer clean-local-testsuite clobber

clobber: maintainer-clean
	@printf 'To rebuild, run ./autogen.sh\n'
	rm -f configure Makefile.in


if HAS_RE2C
# Do not delete src/lexer.cpp if the user could not recreate it
CLEANFILES='@srcdir@/src/lexer.cpp'

@top_srcdir@/src/lexer.cpp: src/lexer.cpp.in
	'@RE2C@' -o '@srcdir@/src/lexer.cpp' '@srcdir@/src/lexer.cpp.in'
endif

check: $(top_srcdir)/tests/testsuite
	'@top_srcdir@/tests/testsuite'

installcheck-local: $(top_srcdir)/tests/testsuite
	'@top_srcdir@/tests/testsuite' 'midwife_bindir=$(DESTDIR)$(bindir)'

$(top_srcdir)/tests/testsuite: $(top_srcdir)/tests/testsuite.at
	cd '@top_srcdir@' && \
	. ./missing autom4te --language=autotest \
		-Wall -Werror \
		--output=tests/testsuite \
		tests/testsuite.at
