CC=gcc
OBJS=student.o main.o
CFLAGS = -c -Wall
a:$(OBJS)
	$(CC) $(OBJS) -o $@
$(OBJS):%o:%c
	$(CC) $(CFLAGS) $^ -o $@
.PHONY:clean
clean:
	rm *.o
