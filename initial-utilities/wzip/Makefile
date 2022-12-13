CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra 

all: wzip

wzip: wzip.o
	$(CC) wzip.o -o wzip

wzip.o: wzip.c
	$(CC) -c $(CFLAGS) wzip.c -o wzip.o

clean:
	rm -rf *.o wzip