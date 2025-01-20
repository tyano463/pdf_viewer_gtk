AC_PREREQ([2.69])
AC_INIT([MyApp], [1.0], [your-email@example.com])
AM_INIT_AUTOMAKE([foreign])

AC_CANONICAL_HOST

AC_PROG_CC

# GTK+3.0の検出
PKG_CHECK_MODULES([GTK], [gtk+-3.0])

if [[ "x${target}" != "x" ]] ; then
    CFLAGS="$CFLAGS --sysroot=$STAGING_DIR"
    CXXFLAGS="$CXXFLAGS --sysroot=$STAGING_DIR"
    LDFLAGS="$LDFLAGS --sysroot=$STAGING_DIR"
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
