CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra 

all: wunzip

wunzip: wunzip.o
	$(CC) wunzip.o -o wunzip

wunzip.o: wunzip.c
	$(CC) -c $(CFLAGS) wunzip.c -o wunzip.o

clean:
	rm -rf *.o wunzip