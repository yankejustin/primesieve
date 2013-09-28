AC_INIT([primesieve], [4.9.9], [kim.walisch@gmail.com])
PACKAGE_YEAR=2013

AC_PREREQ([2.62])

AC_LANG([C++])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])

AC_PROG_CXX
AM_PROG_AR 

LT_INIT

PACKAGE_VERSION_MAJOR=$(echo AC_PACKAGE_VERSION | cut -d'.' -f1)
PACKAGE_VERSION_MINOR=$(echo AC_PACKAGE_VERSION | cut -d'.' -f2)
PACKAGE_VERSION_PATCH=$(echo AC_PACKAGE_VERSION | cut -d'.' -f3)
AC_SUBST(PACKAGE_VERSION_MAJOR)
AC_SUBST(PACKAGE_VERSION_MINOR)
AC_SUBST(PACKAGE_VERSION_PATCH)
AC_SUBST(PACKAGE_YEAR)

AC_ARG_VAR([L1_DCACHE_SIZE], [CPU L1 data cache size in kilobytes])
AS_IF([test "x$L1_DCACHE_SIZE" = x], [[
    # Find the CPU's L1 data cache size in kilobytes
    command -v getconf >/dev/null 2>/dev/null
    if [ $? -eq 0 ]
    then
        L1_DCACHE_BYTES=$(getconf LEVEL1_DCACHE_SIZE 2>/dev/null)
    fi
    if [ "$L1_DCACHE_BYTES" == "" ]
    then
        command -v sysctl >/dev/null 2>/dev/null
        if [ $? -eq 0 ]
        then
            L1_DCACHE_BYTES=$(sysctl hw.l1dcachesize 2>/dev/null | sed -e 's/^.* //')
        fi
    fi
    L1_DCACHE_SIZE=32
    if [ "$L1_DCACHE_BYTES" != "" ]
    then
        L1_DCACHE_SIZE=$(expr $L1_DCACHE_BYTES '/' 1024)
    fi]])
AC_DEFINE_UNQUOTED([L1_DCACHE_SIZE], [$L1_DCACHE_SIZE], [CPU L1 data cache size in kilobytes])

AC_OPENMP

AC_CONFIG_HEADERS([src/soe/autoconf.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT