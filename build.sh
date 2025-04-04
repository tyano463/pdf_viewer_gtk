#!/bin/bash

if [ -d .deps ] ; then
    make distclean
    autoreconf --force
    ./configure
    make
else
    aclocal
    autoconf
    automake --add-missing
    ./configure
    make
fi
