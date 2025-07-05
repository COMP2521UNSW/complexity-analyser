
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

