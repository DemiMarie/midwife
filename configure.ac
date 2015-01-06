#                                               -*- Autoconf -*-
# Copyright 2014-2015 Demetrios Obenour. Licensed under the MIT
# license; see COPYING for its terms

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
AC_PROG_LN_S

AX_WITH_PROG([RE2C], [re2c])

if "${RE2C-false}" /dev/null >/dev/null 2>&1; then
  has_re2c=:
else
  AC_MSG_WARN([[re2c not found, changes to src/lexer.cpp.in ignored]])
  has_re2c=false
fi
AS_CASE([[${RE2C=./missing}]],
        [[*["'\$$as_nl"]*]], [AC_MSG_ERROR([[unsafe path to re2c: $RE2C]])],
        [:])
AM_CONDITIONAL([HAS_RE2C],["$has_re2c"])

# Checks for libraries.

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
