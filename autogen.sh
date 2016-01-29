#!/bin/sh

${ACLOCAL-aclocal}
${LIBTOOLIZE-libtoolize} -c
${AUTOHEADER-autoheader}
${AUTOMAKE-automake} --foreign -a -c
${AUTOCONF-autoconf}

rm -rf autom4te.cache
