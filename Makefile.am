EXTRA_DIST = 			\
	LICENSE.LGPL2.1 	\
	README.md		\
	tests/data/metadata.xml	\
	tests/data/files.xml

AM_CPPFLAGS =			\
	-I $(top_srcdir)/src 	\
	-I $(top_srcdir)/src/lib

AM_CFLAGS = 							\
	-fstack-protector -Wall -pedantic			\
	-Wstrict-prototypes -Wundef -fno-common 		\
	-Werror-implicit-function-declaration 			\
	-Wformat -Wformat-security -Werror=format-security 	\
	-Wno-conversion -Wunused-variable -Wunreachable-code 	\
	-Wall -W -D_FORTIFY_SOURCE=2 -std=c11			\
	-DTOP_DIR=\"$(abs_top_srcdir)\"

if COVERAGE
coverage:
	mkdir -p coverage
	lcov --compat-libtool --directory . --capture --output-file coverage/report
	lcov --remove coverage/report 'tests/*' '/usr/*' --output-file coverage/report
	genhtml -o coverage/ coverage/report

AM_CFLAGS += --coverage
endif

lib_LTLIBRARIES = 	\
	libeopkg-ng.la

bin_PROGRAMS = 		\
	eopkg-ng

# Core library
libeopkg_ng_la_SOURCES = 	\
	src/lib/eopkg.h		\
	src/lib/eopkg.c		\
	src/lib/eopkg-atomics.h	\
	src/lib/util.h		\
	src/lib/xml/entry.c	\
	src/lib/xml/metadata.h	\
	src/lib/xml/metadata.c

libeopkg_ng_la_CFLAGS = 	\
	$(EOPKG_DB_CFLAGS)	\
	$(AM_CFLAGS)

libeopkg_ng_la_LIBADD =		\
	$(EOPKG_DB_LIBS)

eopkg_ng_SOURCES = 	\
	src/cli/main.c

eopkg_ng_CFLAGS =	\
	$(AM_CFLAGS)

eopkg_ng_LDADD = 	\
	libeopkg-ng.la

# Tests
TESTS = \
	check_metadata

check_PROGRAMS = $(TESTS)

check_metadata_SOURCES = \
	tests/check-metadata.c

check_metadata_CFLAGS = \
	$(CHECK_CFLAGS) \
	$(AM_CFLAGS)

check_metadata_LDADD = \
	libeopkg-ng.la \
	$(CHECK_LIBS)

@VALGRIND_CHECK_RULES@

