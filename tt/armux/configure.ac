m4_include([m4/az_python.m4])

AC_INIT([armux], [0.1], [armdev-developers@googlegroups.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_CHECK_LIB(pthreads, pthread_create, [],
[AC_CHECK_LIB(pthread, pthread_create)])
AC_CHECK_LIB(pthreads, pthread_join, [],
[AC_CHECK_LIB(pthread, pthread_join)])
AC_CHECK_LIB(readline, readline)
CFLAGS=-m32
AZ_PYTHON_WITH
AZ_PYTHON_CSPEC
AZ_PYTHON_LSPEC
AC_ARG_ENABLE(debug,
              [  --enable-debug          Enable debugging information],
	       USE_DEBUG="$enableval", USE_DEBUG="no")
if test $USE_DEBUG = yes ; then
        DEBUG=1
	CFLAGS="$CFLAGS -DDEBUG"
fi
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
instructions/Makefile
addressings/Makefile
lua/Makefile
connect/Makefile
])
AC_OUTPUT
