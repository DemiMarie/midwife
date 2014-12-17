#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([Midwife], [0.1.0], [demetriobenour@gmail.com])
AC_CONFIG_SRCDIR([src/midwife.cpp])
AM_INIT_AUTOMAKE([subdir-objects])

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([strstr strtoul])
AC_FUNC_MALLOC

# Checks for shebang support
AC_SYS_INTERPRETER
if test "$interpval" = no; then
  AC_MSG_ERROR([Your system does not support the @%:@! line])
fi

# Note that between the / and ' on the fourth line of the sed
# script is a tab, not a space
printf=`which printf| sed 's/[\\\\\"\$]/\\\\&/g
s/\\\$/&&/g
'"s/'/'\\\\\\\\''/g
1 !s/^/ '/
\$ !s/'\$/\\\\\\\\n'\\\\\\\\/g'"`
AC_SUBST([printf])


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([tests/test])

AC_OUTPUT
