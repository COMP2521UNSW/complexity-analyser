
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int size);
void fixDown(int arr[], int i, int N);
void swap(int arr[], int i, int j);

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

	heapify(arr, n);

	free(arr);
}

void heapify(int *arr, int size) {
	for (int i = size / 2; i >= 0; i--) {
		fixDown(arr, i, size - 1);
	}
}

void fixDown(int arr[], int i, int N) {
	while (2 * i + 1 <= N) {
		int j = 2 * i + 1;
		if (j < N && arr[j] < arr[j + 1]) j++;
		if (arr[i] >= arr[j]) break;
		swap(arr, i, j);
		i = j;
	}
}

void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

