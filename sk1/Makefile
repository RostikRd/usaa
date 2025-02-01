CC = gcc
CFLAGS = -Wall -Werror

all: compressor

compressor: compressor.o main.o
	$(CC) $(CFLAGS) -o compressor compressor.o main.o

compressor.o: compressor.c compressor.h
	$(CC) $(CFLAGS) -c compressor.c

main.o: main.c compressor.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o compressor
