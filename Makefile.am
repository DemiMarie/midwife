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
	  re2c -o src/lexer.cpp '@srcdir@/src/lexer.cpp.in'; \
	else \
	  printf "WARNING: re2c not found.\\n\
	Changes in lexer.cpp.in ignored\\n" >&2; \
	fi

check:
	dir=$${RANDOM}tmp$$$$; \
	mkdir "./$$dir" && chmod 700 "./$$dir" && \
	echo >$$dir/test && chmod 700 "./$$dir/test" && \
	printf '#! ../midwife -n2\n%s\n' \
	';; -*-@printf@  "%s" "aasdf\n\x0ad\012aa\n" -*-' >$$dir/test && \
	"$$dir/test" >$$dir/test_output && \
	printf 'aasdf\n\x0ad\012aa\n' | cmp - "$$dir/test_output"; \
	status=$$?; rm -rf -- "$$dir"; exit $$status
