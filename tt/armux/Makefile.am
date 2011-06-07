bin_PROGRAMS = armux
armux_SOURCES = addressing.c coprocessor.c instruction.c main.c memory.c processor.c utils.c shell.c connects.c
SUBDIRS = instructions addressings lua connect
LDADD = instructions/libarminst.a addressings/libarmaddr.a lua/libarmlua.a @top_srcdir@/libs/lua/liblua5.1.a

CFLAGS = -I@top_srcdir@/include/ -lm -I@top_srcdir@/libs/include/ -ldl
EXTRA_DIST = AUTHORS ChangeLog NEWS README include libs

if PYTHON_USE
armux_CFLAGS = @CFLAGS@ @PYTHON_CSPEC@ -DPYTHON
armux_LDFLAGS = @PYTHON_LSPEC@
else
armux_CFLAGS = @CFLAGS@ -DLUA
endif

