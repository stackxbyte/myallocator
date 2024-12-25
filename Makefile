CC = gcc
CFLAGS = -ggdb -no-pie

main: 
	$(CC) $(CFLAGS) -o allocator allocator.c

clean: 
	rm allocator
