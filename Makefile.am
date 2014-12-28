# @configure_input@
bin_PROGRAMS=midwife
midwife_SOURCES=src/midwife.cpp src/lexer.cpp src/lexer.hpp
DISTCLEANFILES=testsuite.log atlocal atconfig
MAINTAINERCLEANFILES=@srcdir@/src/lexer.cpp aclocal.m4 package.m4
EXTRA_DIST=src/lexer.cpp.in tests/testsuite.at \
	   tests/testsuite $(MAINTAINERCLEANFILES)
AM_CPPFLAGS='-I@srcdir@/src'

RE2C = @re2c@

maintainer-clean-local:
	rm -f -- $(DIST_ARCHIVES)

clean-local: clean-local-lexer clean-local-testsuite

.PHONY: clean-local-lexer clean-local-testsuite clobber

clobber: maintainer-clean
	@printf 'To rebuild, run ./autogen.sh'
	rm -f configure Makefile.in


# Do not delete src/lexer.cpp if the user could not recreate it
clean-local-lexer:
	if re2c -v 2>&1 | grep re2c >/dev/null; then \
	  rm -f src/lexer.cpp; \
	fi

clean-local-testsuite:
	rm -rf testsuite.dir

@srcdir@/src/lexer.cpp: src/lexer.cpp.in
	if $(RE2C) -v 2>&1 | grep re2c >/dev/null; then\
	  $(RE2C) -o '@srcdir@/src/lexer.cpp' \
	  '@srcdir@/src/lexer.cpp.in'; \
	else \
	  printf "WARNING: re2c not found.\\n\
	Changes in lexer.cpp.in ignored\\n" >&2; \
	fi

check:
	'@srcdir@/tests/testsuite'

installcheck-local:
	'@srcdir@/tests/testsuite' 'midwife_bindir=$(bindir)'
