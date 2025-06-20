
#include <stdio.h>
#include <stdlib.h>

long long fib(int n);

int main(int argc, char *argv[]) {
	int n = argc == 1 ? 0 : atoi(argv[1]);
	fib(n);
}

long long fib(int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else {
		return fib(n - 1) + fib(n  - 2);
	}
}

