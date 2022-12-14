CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra 

all: reverse

check_leak: reverse
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./reverse tests/6.in  

reverse: reverse.o
	$(CC) reverse.o -o reverse

reverse.o: reverse.c
	$(CC) -c $(CFLAGS) reverse.c -o reverse.o

clean:
	rm -rf *.o reverse