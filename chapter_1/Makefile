TARGET:=getTime

CFLAGS:=-Wall -g
LDFLAGS:=-I../include

SRCS:=main.c

OBJ:=${patsubst %.c, %.o, $(SRCS)}

${TARGET}:${OBJ}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(TARGET) $(OBJS)




