// Experimental test file version; which will be used with upgraded input/output capabilities of the 
// analyser program.
#include <stdlib.h>
#include <stdio.h>

// Exponential-time Fibonacci
long fibonacci(int n) {
    if (n < 2) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// O(log(n)) work: repeatedly half i
void doLogarithmic(int n) {
    long ops = 0;
    for (int i = n; i > 0; i >>= 1) {
        // dummy operation
        ops++;
    }
    printf("Logarithmic (O(log n))      ops: %ld\n", ops);
}

// O(n log n) work: for each i < n, loop j from 1 to n, doubling each time
void doLogLinear(int n) {
    long ops = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j <<= 1) {
            // dummy operation
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
                // dummy operation
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
    int choice = 0;
    int n = -1;

    // Print choices that can be made, and take user choice:
    printf("Select workload to run:\n");
    printf(" 1) Constant       O(1)\n");
    printf(" 2) Logarithmic    O(log n)\n");
    printf(" 3) Loop           O(n)\n");
    printf(" 4) Log-Linear     O(n log n)\n");
    printf(" 5) Double Loop    O(n^2)\n");
    printf(" 6) Cubic          O(n^3)\n");
    printf(" 7) Exponential    O(2^n)\n");
    printf("\nEnter choice (1-7): ");

    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Error: invalid choice input.\n");
        return EXIT_FAILURE;
    }

    // Ask for an input size to be tested on.
    printf("Enter n (non-negative integer): ");
    scanf("%d", &n);
    if (n <= 0) {
        fprintf(stderr, "Error: invalid n value.\n");
        return EXIT_FAILURE;
    }

    printf("\nRunning workload for n = %d...\n\n", n);

    // Run the specified choice
    switch (choice) {
        case 1: doConstant(n);     break;
        case 2: doLogarithmic(n);  break;
        case 3: doLoop(n);         break;
        case 4: doLogLinear(n);    break;
        case 5: doDoubleLoop(n);   break;
        case 6: doCubic(n);        break;
        case 7: doExponential(n);  break;
        default:
            fprintf(stderr, "Error: choice must be 1–7.\n");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
