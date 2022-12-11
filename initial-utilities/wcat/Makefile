CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra 

all: wcat

wcat: wcat.o
	$(CC) wcat.o -o wcat

wcat.o: wcat.c
	$(CC) -c $(CFLAGS) wcat.c -o wcat.o

clean:
	rm -rf *.o wcat