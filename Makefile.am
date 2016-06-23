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

bin_PROGRAMS = 		\
	eopkg_ng

eopkg_ng_SOURCES = 	\
	src/lib/util.h	\
	src/cli/main.c

eopkg_ng_CFLAGS =	\
	$(AM_CFLAGS)

