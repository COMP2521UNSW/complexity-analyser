
CC = clang
CFLAGS = -Wall -Werror -gdwarf-4

all: loop fib bsearch realloc double constant test_file

test_file: test_file.c
	$(CC) $(CFLAGS) -o test_file test_file.c

constant: constant.c
	$(CC) $(CFLAGS) -o constant constant.c

double: double_loop.c
	$(CC) $(CFLAGS) -o double_loop double_loop.c

loop: loop.c
	$(CC) $(CFLAGS) -o loop loop.c

fib: fib.c
	$(CC) $(CFLAGS) -o fib fib.c

bsearch: bsearch.c
	$(CC) $(CFLAGS) -o bsearch bsearch.c

realloc: realloc.c
	$(CC) $(CFLAGS) -o realloc realloc.c

clean:
	rm -f loop fib bsearch realloc double_loop constant test_file

