# Initialization
AC_PREREQ([2.69])
AC_INIT([oem-ipmi-handler], [0.1.0], [sample@test.come])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_MKDIR_P

# Check for sdbus++ tool
#PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus],, \
#    AC_MSG_ERROR(["Requires sdbusplus package."]))
#AC_PATH_PROG([SDBUSPLUSPLUS], [sdbus++])
#AS_IF([test "x$SDBUSPLUSPLUS" == "x"], AC_MSG_ERROR([Cannot find sdbus++]))

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_17([noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# Checks for library functions.
LT_INIT

# Create configured output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

