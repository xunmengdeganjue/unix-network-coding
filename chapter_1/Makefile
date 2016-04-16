TARGET:=getTime

CFLAGS:=-Wall -g -I../include
#LDFLAGS:=-L../lib 
LDFLAGS:=
DIRS:=../lib ./

SRCS=$(foreach DIR, $(DIRS), $(wildcard $(DIR)/*.c)) #main.c
OBJS=$(patsubst %.c, %.o, $(SRCS))

#OBJS:=${patsubst %.c, %.o, $(SRCS)}

${TARGET}:lib ${OBJS}
	$(CC)  $(LDFLAGS) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf $(OBJS) $(TARGET)

lib:
	make -C ../lib

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
