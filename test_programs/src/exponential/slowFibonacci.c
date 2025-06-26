
#include <stdio.h>
#include <stdlib.h>

unsigned long long slowFibonacci(int n);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	unsigned long long res = slowFibonacci(n);
	printf("fib(%d) = %llu\n", n, res);
}

unsigned long long slowFibonacci(int n) {
	if (n < 2) return n;
    return slowFibonacci(n - 1) + slowFibonacci(n - 2);
}

