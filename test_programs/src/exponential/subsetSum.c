
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool subsetSum(int *arr, int size, int sum);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <array size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	int *arr = malloc(n * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}

	bool res = subsetSum(arr, n, n * n);
	printf("Result: %s\n", res ? "yes" : "no");

	free(arr);
}

bool subsetSum(int *arr, int size, int sum) {
	if (sum == 0 || size == 0) {
		return sum == 0;
	}

	return (
		subsetSum(&arr[1], size - 1, sum) ||
		subsetSum(&arr[1], size - 1, sum - arr[0])
	);
}

