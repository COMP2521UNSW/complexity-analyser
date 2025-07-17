# Introduction

Complexity analyser estimates the time complexity of C functions.

It uses Callgrind (a Valgrind tool) to measure the number of instructions executed by a C function for different input sizes, and then linear regression to determine the most likely time complexity of the function out of commonly-occurring time complexities ($O(1)$, $O(\log n)$, $O(n)$, $O(n \log n)$, $O(n^2)$, $O(n^3)$, $O(2^n)$ ).

# How to use

1. Write a C program that includes the function to be analysed and takes an input size as its last command-line argument
2. Compile the program with debugging symbols
3. Run the analyser with the command

```
./analyser.py [command] [function-name] [input size]... 
```

   The given command will be run once per input size, with the input size appended to the command. For more accurate results, it is recommended to provide at least eight input sizes.

## Example

1. Write a C program:

```c
#include <stdio.h>
#include <stdlib.h>

static void selectionSort(int arr[], int size);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <array size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	int *arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}

	selectionSort(arr, n);

	free(arr);
}

static void selectionSort(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		int min = i;
		for (int j = min + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
```

2. Compile the program:

```
clang -Wall -Werror -g -o selectionSort selectionSort.c
```

3. Run the analyser:

```
./analyser.py ./selectionSort selectionSort 10 20 30 40 50 60 70 80
```

## Recommendation

For accurate results, the program should generate the same "type" of input each time it is run. For example, to analyse the worst-case time complexity of the function, the program should consistently generate inputs that correspond to the worst-case runtime of the function.

# Dependencies

C compiler, python3, valgrind, numpy, scikit-learn

# Tests

A number of test programs are included. Compile the test programs with `make` and then run the tests with `python3 test_analyser.py`.

# Limitations

* The analyser does not count instructions executed by system calls. This can lead to inaccurate results if the function uses system calls that are not $O(1)$, for example, by calling `realloc`.

# Possible improvements

* Handle errors (e.g., timeouts) more gracefully
* Handle when the function is not called by the program
* Write more detailed description of implementation
* Add more test programs

