TARGET:=getTime

CFLAGS:=-Wall -g -I../include
#LDFLAGS:=-L../lib 
LDFLAGS:= L../lib
LIBS:= ../lib

DIRS:= $(LIBS) .

SRCS=$(foreach DIR, $(DIRS), $(wildcard $(DIR)/*.c)) #main.c
OBJS=$(patsubst %.c, %.o, $(SRCS))

#OBJS:=${patsubst %.c, %.o, $(SRCS)}
all :lib ${OBJS}
	@echo $(LIBS)
	@echo $(OBJS)
	$(warning  "The LIBS IS :$(LIBS)")
	$(warning  $(OBJS))
	$(CC)  $(LDFLAGS) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf $(OBJS) $(TARGET)

lib:
	$(warning "The LIBS IS: $(LIBS)")
	$(warning "The OBJS IS: $(OBJS)")
	make -C ../lib

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
