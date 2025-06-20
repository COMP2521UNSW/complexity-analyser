
#include <stdbool.h>
#include <stdio.h>
#define bsearch _bsearch
#include <stdlib.h>
#undef bsearch

bool bsearch(int arr[], int n, int key);

int main(int argc, char *argv[]) {
	int n = argc == 1 ? 0 : atoi(argv[1]);

	int *arr = malloc(n * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) {
		arr[i] = 2 * i + 1;
	}

	bsearch(arr, n, 2 * n);
}

bool bsearch(int arr[], int n, int key) {
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

