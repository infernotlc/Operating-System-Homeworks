CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

all: speedtest histChars

speedtest: speedtest.c
	$(CC) $(CFLAGS) -o speedtest speedtest.c

histChars: histChars.c
	$(CC) $(CFLAGS) -o histChars histChars.c

clean:
	rm -f speedtest histChars
