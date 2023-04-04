CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99

all: mymalloc_test

mymalloc_test: mymalloc.o mymalloc_test.o
	$(CC) $(CFLAGS) -o mymalloc_test mymalloc.o mymalloc_test.o

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

mymalloc_test.o: mymalloc_test.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc_test.c

clean:
	rm -f mymalloc_test mymalloc.o mymalloc_test.o
