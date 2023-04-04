CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

all: binarytoascii

binarytoascii: binarytoascii.o
	$(CC) $(CFLAGS) -o $@ $^

binarytoascii.o: binarytoascii.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f binarytoascii binarytoascii.o
