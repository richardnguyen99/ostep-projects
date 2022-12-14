CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra 

all: reverse

reverse: reverse.o
	$(CC) reverse.o -o reverse

reverse.o: reverse.c
	$(CC) -c $(CFLAGS) reverse.c -o reverse.o

clean:
	rm -rf *.o reverse