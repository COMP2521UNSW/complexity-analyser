
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool twoSum(int *arr, int size, int sum);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
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

	bool res = twoSum(arr, n, 2 * n);
	printf("Result: %s\n", res ? "yes" : "no");

	free(arr);
}

bool twoSum(int *arr, int size, int sum) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] + arr[j] == sum) {
				return true;
			}
		}
	}
	
	return false;
}

