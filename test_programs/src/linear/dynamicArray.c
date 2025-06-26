
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 8

void dynamicArray(int arrSize);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <array size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	dynamicArray(n);
}

void dynamicArray(int arrSize) {
	int *arr = malloc(DEFAULT_CAPACITY * sizeof(int));
	int size = 0;
	int capacity = DEFAULT_CAPACITY;

	for (int i = 0; i < arrSize; i++) {
		if (size == capacity) {
			int *newArr = malloc(2 * capacity * sizeof(int));
			for (int j = 0; j < size; j++) {
				newArr[j] = arr[j];
			}
			free(arr);
			arr = newArr;
			capacity *= 2;
		}

		arr[i] = i;
		size++;
	}

	free(arr);
}

