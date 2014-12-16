bin_PROGRAMS= midwife
midwife_SOURCES=src/midwife.cpp src/lexer.cpp src/lexer.hpp
EXTRA_DIST=src/lexer.cpp src/lexer.cpp.in
MAINTAINERCLEANFILES=src/lexer.cpp
AM_CPPFLAGS ='-I@srcdir@/src'

clean-local: clean-local-lexer
.PHONY: clean-local-lexer

# Do not delete src/lexer.cpp if the user could not recreate it
clean-local-lexer:
	if re2c -v 2>&1 | grep re2c >/dev/null; then \
	  rm -f src/lexer.cpp; \
	fi

src/lexer.cpp: src/lexer.cpp.in
	if re2c -v 2>&1 | grep re2c >/dev/null; then \
	  re2c -o src/lexer.cpp "@srcdir@/src/lexer.cpp.in"; \
	else \
	  printf "WARNING: re2c not found.\\n\
	Changes in lexer.cpp.in ignored\\n" >&2; \
	fi
