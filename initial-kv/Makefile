CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra

all: kv

kv: main.o kvs.o
	$(CC) main.o kvs.o -o kv

main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o

kvs.o: kvs.c
	$(CC) -c $(CFLAGS) kvs.c -o kvs.o

clean:
	rm -rf *.o kv
