#!/bin/bash

PWD_PATH=`pwd`
INSTALL_PATH="$PWD_PATH"/install

mkdir -p "$INSTALL_PATH"

aclocal
autoconf
automake --add-missing
libtoolize --automake --copy --debug --force
autoheader
automake
#autoheader
automake --add-missing
#libtoolize --automake --copy --debug --force

dos2uinx +x configure
chmod +x configure

./configure --prefix=$INSTALL_PATH
make
make install

cp -rf "$INSTALL_PATH"/include/CUnit "$PWD_PATH"/../include
cp -f "$INSTALL_PATH"/lib/libcunit* /usr/lib64/
