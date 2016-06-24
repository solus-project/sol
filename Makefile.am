EXTRA_DIST = 		\
	LICENSE.LGPL2.1 \
	README.md

AM_CPPFLAGS =			\
	-I $(top_srcdir)/src 	\
	-I $(top_srcdir)/src/lib

AM_CFLAGS = 							\
	-fstack-protector -Wall -pedantic			\
	-Wstrict-prototypes -Wundef -fno-common 		\
	-Werror-implicit-function-declaration 			\
	-Wformat -Wformat-security -Werror=format-security 	\
	-Wno-conversion -Wunused-variable -Wunreachable-code 	\
	-Wall -W -D_FORTIFY_SOURCE=2 -std=c11

lib_LTLIBRARIES = 	\
	libeopkg-ng.la

bin_PROGRAMS = 		\
	eopkg-ng

# Core library
libeopkg_ng_la_SOURCES = 	\
	src/lib/eopkg.h		\
	src/lib/eopkg.c		\
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
