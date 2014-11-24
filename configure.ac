#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([Shebang Helper], [0.1.0], [demetriobenour@gmail.com])
AC_CONFIG_SRCDIR([src/shebang-helper.c])
AM_INIT_AUTOMAKE([subdir-objects])

# Automake
AC_CONFIG_FILES([Makefile])

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_OUTPUT
