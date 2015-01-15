# @configure_input@
AUTOMAKE_OPTIONS=subdir-objects
bin_PROGRAMS=midwife
midwife_SOURCES=src/midwife.cpp src/lexer.cpp src/lexer.hpp
dist_man1_MANS=man/midwife.1
DISTCLEANFILES=testsuite.log atlocal atconfig
MAINTAINERCLEANFILES=aclocal.m4 package.m4 tests/testsuite
EXTRA_DIST=$(top_srcdir)/src/lexer.cpp.in tests/testsuite.at \
	   autogen.sh $(MAINTAINERCLEANFILES)


all-local: midwife3$(EXEEXT)

midwife3$(EXEEXT): midwife$(EXEEXT)
	-$(LN_S) 'midwife$(EXEEXT)' 'midwife3$(EXEEXT)'

.PHONY: midwife3$(EXEEXT) clean-local-testsuite clobber

clobber: maintainer-clean
	@printf 'To rebuild, run ./autogen.sh\n'
	rm -f configure Makefile.in


if HAS_RE2C
# Do not delete src/lexer.cpp if the user could not recreate it
CLEANFILES='@srcdir@/src/lexer.cpp' 'midwife3$(EXEEXT)'

@top_srcdir@/src/lexer.cpp: src/lexer.cpp.in
	'@RE2C@' -o '@srcdir@/src/lexer.cpp' '@srcdir@/src/lexer.cpp.in'
else
CLEANFILES='midwife3$(EXEEXT)'
endif

check: $(top_srcdir)/tests/testsuite
	'$(top_srcdir)/tests/testsuite'

install-exec-hook:
	-cd -- '$(DESTDIR)$(bindir)' && \
	$(LN_S) midwife$(EXEEXT) midwife3$(EXEEXT)

uninstall-hook:
	$(RM) -- '$(DESTDIR)$(bindir)/midwife3'

installcheck-local: $(top_srcdir)/tests/testsuite
	'$(top_srcdir)/tests/testsuite' 'midwife_bindir=$(DESTDIR)$(bindir)'

$(top_srcdir)/tests/testsuite: $(top_srcdir)/tests/testsuite.at
	cd '$(top_srcdir)' && \
	. ./missing autom4te --language=autotest \
		-Wall -Werror \
		--output=tests/testsuite \
		tests/testsuite.at
