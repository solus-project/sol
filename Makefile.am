EXTRA_DIST = \
	LICENSE.LGPL2.1

AM_CFLAGS = \
	-fstack-protector -Wall -pedantic \
	-Wstrict-prototypes -Wundef -fno-common \
	-Werror-implicit-function-declaration \
	-Wformat -Wformat-security -Werror=format-security \
	-Wno-conversion -Wunused-variable -Wunreachable-code \
	-Wall -W -D_FORTIFY_SOURCE=2 -std=c11

bin_PROGRAMS = \
	eopkg_ng

eopkg_ng_SOURCES = \
	src/cli/main.c


