
#TOPDIR=$(shell cd ../../../../../; pwd)
#include $(TOPDIR)/Profile.mak

TARGET=unix-network-coding

#HOST_TOOL=mf_info_gen

CFLAGS= -Wall -g
#ifeq ("${PRODUCT_HARDWARE}", "rt4230w-d156")
#CFLAGS+=-DCONFIG_RT4230W_D156
#else
#CFLAGS+=-DCONFIG_RT4230W_D187
#endif

SRCS=main.c

OBJS=$(patsubst %.c, %.o, $(SRCS))


all: $(TARGET) $(HOST_TOOL) 

$(TARGET): ${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(TARGET) $(OBJS)

$(HOST_TOOL):
	gcc $(CFLAGS) mf_info_gen.c -o $(HOST_TOOL)
	cp -arpdf $(HOST_TOOL) $(TOPDIR)/tools/

clean: 
	rm -rf ${TARGET} $(OBJS) *.bak mf_info_gen art_default_mf_info.bin

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
