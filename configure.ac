AC_INIT([sol], 0, [ikey@solus-project.com], [sol], [https://gitlab.com/solus-project/sol])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects])
AC_PROG_CC
AC_PROG_CC_STDC
AC_CONFIG_HEADERS([config.h])
AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
AX_VALGRIND_CHECK
LT_INIT

m4_define([libxml_required_version], [2.9.0])
m4_define([curl_required_version], [7.43.0])
m4_define([libarchive_required_version], [3.1.2])
m4_define([check_required_version], [0.9.0])

PKG_CHECK_MODULES([CHECK], [
        check >= check_required_version
])

# Core database requirements
PKG_CHECK_MODULES([SOL_DB], [
        libxml-2.0 >= libxml_required_version
])

# Network requirements
PKG_CHECK_MODULES([SOL_NETWORK], [
        libcurl >= curl_required_version
])

# Actual file ops (packages/indexes/etc)
PKG_CHECK_MODULES([SOL_FILES], [
        libarchive >= libarchive_required_version
])

have_coverage=no
AC_ARG_ENABLE(coverage, AS_HELP_STRING([--enable-coverage], [enable test coverage]))
if test "x$enable_coverage" = "xyes" ; then
        AC_CHECK_PROG(lcov_found, [lcov], [yes], [no])
        if test "x$lcov_found" = xno ; then
                AC_MSG_ERROR([*** lcov support requested but the program was not found])
        else
                lcov_version_major="`lcov --version | cut -d ' ' -f 4 | cut -d '.' -f 1`"
                lcov_version_minor="`lcov --version | cut -d ' ' -f 4 | cut -d '.' -f 2`"
                if test "$lcov_version_major" -eq 1 -a "$lcov_version_minor" -lt 10; then
                        AC_MSG_ERROR([*** lcov version is too old. 1.10 required])
                else
			have_coverage=yes
			AC_DEFINE([COVERAGE], [1], [Coverage enabled])
                fi
        fi
fi
AM_CONDITIONAL([COVERAGE], [test "$have_coverage" = "yes"])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

AC_MSG_RESULT([
        sol $VERSION
        ========

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}

        coverage:               ${have_coverage}
])
