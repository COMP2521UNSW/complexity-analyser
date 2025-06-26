
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool binarySearch(int arr[], int n, int key);

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
		arr[i] = 2 * i + 1;
	}

	binarySearch(arr, n, 2 * n);

	free(arr);
}

bool binarySearch(int arr[], int n, int key) {
	int lo = 0;
	int hi = n - 1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (key < arr[mid]) {
			hi = mid - 1;
		} else if (key > arr[mid]) {
			lo = mid + 1;
		} else {
			return true;
		}
	}
	return false;
}

