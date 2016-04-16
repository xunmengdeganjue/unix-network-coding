#!/bin/sh
set -e
set -x

# Remove old source
rm -rf unpv12e

# Unpack Richard Stevens' original sources
zcat unpv12e.tar.gz | tar -xvf -

# Replace hard links with symbolic ones for files we patch
mv unpv12e/lib/unp.h .
ls unpv12e/*/unp.h > unps.tmp
rm unpv12e/*/unp.h
mv unp.h unpv12e/lib
for unp in `cat unps.tmp`; do
	ln -s ../lib/unp.h $unp
done
rm unps.tmp

# Apply patches
for p in *.patch ; do
	echo Applying $p
	patch -p0 < $p
done

# Build it
cd unpv12e
rm configure
autoconf
./configure
cd lib
make
cd ../libfree
make
cd ../server
make

echo build.sh done
