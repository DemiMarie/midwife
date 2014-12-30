#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

m4_include([m4/midwife_package.m4])
AC_INIT([Midwife], [0.1.0], [demetriobenour@gmail.com],
	[midwife], [https://github.com/drbo/shebang-helper])
AC_CONFIG_SRCDIR([src/midwife.cpp])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects])

# Checks for shebang support
AC_SYS_INTERPRETER
if test "$interpval" = no; then
  AC_MSG_ERROR([Your system does not support the @%:@! line])
fi

AC_CONFIG_HEADERS([config.h])

# We are using C++
AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
AX_WITH_PROG([RE2C], [re2c], [re2c])
test "x$RE2C" != xno ||
	AC_MSG_WARN([[re2c not found, changes to src/lexer.cpp.in ignored]])
AM_CONDITIONAL([HAS_RE2C], [test "x$RE2C" != xno])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([cassert cerrno climits cstdio \
cstdlib cstring errno.h stdio.h stdlib.h string \
string.h unistd.h vector])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([strstr strtoul])

# Initialize testsuite
AC_CONFIG_TESTDIR([.])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT

MIDWIFE_PACKAGE
