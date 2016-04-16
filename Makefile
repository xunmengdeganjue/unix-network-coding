
#TOPDIR=$(shell cd ../../../../../; pwd)
#include $(TOPDIR)/Profile.mak

TARGET=unix-network-coding

#HOST_TOOL=mf_info_gen

CFLAGS= -Wall -g -I./include
#LDFLAGS+=-L. -lm -liwinfo -luci -lcups


CHAPTERLIB=chapter_1
DIRS=$(CHAPTERLIB) lib  
SRCS=$(foreach DIR, $(DIRS), $(wildcard $(DIR)/*.c))
OBJS=$(patsubst %.c, %.o, $(SRCS))
#OBJS+=cgi_main.o


all:lib $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(TARGET) $(OBJS)

#build_bsahashtab: 
#	gcc $(CFLAGS) -o hash/bsa_hashtab hash/bsa_hashtab.c
#	./hash/bsa_hashtab ./hash/cgi_bsa_hash_tab.h

lib: 
	make -C lib


#install:
#	sudo cp net.cgi /usr/lib/cgi-bin/
	#echo "cp -a $(TARGET) $(ROOTDIR)/web"
	#@cp -a $(TARGET) $(ROOTDIR)/web

clean: 
	rm -rf $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
