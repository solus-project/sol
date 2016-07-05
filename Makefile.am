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
	-Wconversion -Wunused-variable -Wunreachable-code 	\
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
	libsol.la

bin_PROGRAMS = 		\
	sol

# Core library
libsol_la_SOURCES = 		\
	src/lib/sol.h			\
	src/lib/sol.c			\
	src/lib/sol-atomics.h	\
	src/lib/util.h			\
	src/lib/xml/entry.c		\
	src/lib/xml/metadata.h	\
	src/lib/xml/metadata.c  \
	src/lib/db/install-db.h \
	src/lib/db/install-db.c

libsol_la_CFLAGS = 		\
	$(SOL_DB_CFLAGS)	\
	$(AM_CFLAGS)

libsol_la_LIBADD =		\
	$(SOL_DB_LIBS)

sol_SOURCES = 	\
	src/cli/main.c

sol_CFLAGS =	\
	$(AM_CFLAGS)

sol_LDADD = 	\
	libsol.la

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
	libsol.la \
	$(CHECK_LIBS)

@VALGRIND_CHECK_RULES@

