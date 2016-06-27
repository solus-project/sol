AC_INIT([eopkg], 0, [ikey@solus-project.com], [eopkg], [https://gitlab.com/solus-project/eopkg])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects])
AC_PROG_CC
AC_PROG_CC_STDC
AC_CONFIG_HEADERS([config.h])
AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

m4_define([libxml_required_version], [2.9.0])
m4_define([curl_required_version], [7.43.0])
m4_define([libarchive_required_version], [3.1.2])
m4_define([check_required_version], [0.9.0])

PKG_CHECK_MODULES([CHECK], [
        check >= check_required_version
])

# Core database requirements
PKG_CHECK_MODULES([EOPKG_DB], [
        libxml-2.0 >= libxml_required_version
])

# Network requirements
PKG_CHECK_MODULES([EOPKG_NETWORK], [
        libcurl >= curl_required_version
])

# Actual file ops (packages/indexes/etc)
PKG_CHECK_MODULES([EOPKG_FILES], [
        libarchive >= libarchive_required_version
])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

AC_MSG_RESULT([
        eopkg $VERSION
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
])
