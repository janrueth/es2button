#!/bin/bash

VERSION=6.7.43.0-1
PACKAGE=epsonscan2-${VERSION}
FILE=$PACKAGE.src.tar.gz

wget https://support.epson.net/linux/src/scanner/epsonscan2/${FILE} -O ${FILE}

# untar src folder from archive into include directory
tar -C include --strip-components=2 -xzf ${FILE} $PACKAGE/src