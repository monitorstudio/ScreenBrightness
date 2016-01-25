CC=clang
CFLAGS=-Wall -Wextra -Weverything -pedantic -Ofast
STRIP=strip

all: main brightness
	$(CC) $(CFLAGS) -o brightness main.o brightness.o
	$(STRIP) brightness

main: brightness.h main.c
	$(CC) $(CFLAGS) -c main.c

brightness: brightness.h brightness.c
	$(CC) $(CFLAGS) -c brightness.c

.PHONY clean:
	rm *.o brightness
