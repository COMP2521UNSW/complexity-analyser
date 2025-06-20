#include <stdlib.h>
#include <stdio.h>

// Exponential-time Fibonacci (≈O(φ^n))
long fibonacci(int n) {
    if (n < 2) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// O(log(n)) work: repeatedly half i
void doLogarithmic(int n) {
    long ops = 0;
    for (int i = n; i > 0; i >>= 1) {
        ops++;
    }
    printf("Logarithmic (O(log n))      ops: %ld\n", ops);
}

// O(n log n) work: for each i < n, loop j from 1→n doubling each time
void doLogLinear(int n) {
    long ops = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j <<= 1) {
            ops++;
        }
    }
    printf("Log-linear (O(n log n)) ops: %ld\n", ops);
}

// O(n^3) work: three nested loops
void doCubic(int n) {
    long ops = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ops++;
            }
        }
    }
    printf("Cubic (O(n^3))   ops: %ld\n", ops);
}

// Exponential work: compute fib(n)
void doExponential(int n) {
    if (n > 40) {
        printf("Skipping Fibonacci(%d): too slow for naive recursion\n", n);
        return;
    }
    long result = fibonacci(n);
    printf("Exponential (≈O(φ^n)) fib(%d) = %ld\n", n, result);
}

// Quadratic work: run a double loop
void doDoubleLoop(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++);
	}
}

// Linear work: run a single loop
void doLoop(int n) {
    for (int j = 0; j < n; j++);
}

// Constant work: do a couple constant actions, and return
void doConstant(int n) {
	int x = 0;
	int y = 1;
	int z = x + y;
	z++;
	return;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n < 0) {
        fprintf(stderr, "Please pass a non-negative integer for n.\n");
        return EXIT_FAILURE;
    }

    printf("Running workloads for n = %d\n\n", n);
    
    // At the moment, each unused function is best to be commented out.
    // This is because if this does not occur, it will run all functions, regardless of input size.
    // When testing size 1000 (for testing something like logarithmic) this would run exponential 
    // on size 1000, taking an extremely long time to complete.
     
    doConstant(n);
    doLogarithmic(n);
    doLoop(n);
    doLogLinear(n);
    doDoubleLoop(n);
    // doCubic(n);
    // doExponential(n);

    return EXIT_SUCCESS;
}
