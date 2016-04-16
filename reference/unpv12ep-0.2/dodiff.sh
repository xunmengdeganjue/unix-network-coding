#!/bin/sh
set -x
diff -Nau unpv12e{.orig,}/lib/unp.h 
diff -Nau unpv12e{.orig,}/lib/unpthread.h
diff -Naur -x 'unp*.h' -x '*.lh' -x configure unpv12e{.orig,}
