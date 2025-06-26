
#include <stdio.h>
#include <stdlib.h>

static void mergeSort(int items[], int lo, int hi);
static void merge(int items[], int lo, int mid, int hi);

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

	mergeSort(arr, 0, n - 1);

	free(arr);
}

static void mergeSort(int arr[], int lo, int hi) {
	if (lo >= hi) return;
	int mid = (lo + hi) / 2;
	mergeSort(arr, lo, mid);
	mergeSort(arr, mid + 1, hi);
	merge(arr, lo, mid, hi);
}

static void merge(int arr[], int lo, int mid, int hi) {
	int *tmp = malloc((hi - lo + 1) * sizeof(int));

	int i = lo;
	int j = mid + 1;
	int k = 0;

	// Scan both segments, copying to `tmp'.
	while (i <= mid && j <= hi) {
		if (arr[i] <= arr[j]) {
			tmp[k++] = arr[i++];
		} else {
			tmp[k++] = arr[j++];
		}
	}

	// Copy items from unfinished segment.
	while (i <= mid) tmp[k++] = arr[i++];
	while (j <= hi) tmp[k++] = arr[j++];

	// Copy `tmp' back to main array.
	for (i = lo, k = 0; i <= hi; i++, k++) {
		arr[i] = tmp[k];
	}

	free(tmp);
}

