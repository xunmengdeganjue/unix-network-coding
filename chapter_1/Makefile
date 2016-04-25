TARGET:=getTime

CFLAGS:=-Wall -g -I../include
LDFLAGS:=

SRCS:=main.c

OBJS:=${patsubst %.c, %.o, $(SRCS)}

${TARGET}:${OBJS}
	$(CC)  $(LDFLAGS) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf $(OBJS) $(TARGET)



