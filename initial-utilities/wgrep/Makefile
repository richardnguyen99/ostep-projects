CC 		:= gcc
CFLAGS 	:= -O3 -Wall -Werror -Wextra 

all: wgrep

wgrep: wgrep.o
	$(CC) wgrep.o -o wgrep

wgrep.o: wgrep.c
	$(CC) -c $(CFLAGS) wgrep.c -o wgrep.o

clean:
	rm -rf *.o wgrep