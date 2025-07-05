
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void quickSort(int a[], int lo, int hi);
static void medianOfThree(int a[], int lo, int hi);
static int partition(int a[], int lo, int hi);
static inline void swap(int a[], int i, int j);

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

	quickSort(arr, 0, n - 1);

	free(arr);
}

static void quickSort(int a[], int lo, int hi) {
	if (lo >= hi) return;
	medianOfThree(a, lo, hi);
	int pivotIndex = partition(a, lo, hi);
	quickSort(a, lo, pivotIndex - 1);
	quickSort(a, pivotIndex + 1, hi);
}

static void medianOfThree(int a[], int lo, int hi) {
	int mid = (lo + hi) / 2;
	if (a[mid] > a[lo]) swap(a, mid, lo);
	if (a[lo] > a[hi]) swap(a, lo,  hi);
	if (a[mid] > a[lo]) swap(a, mid, lo);
}

static int partition(int a[], int lo, int hi) {
	int pivot = a[lo];

	int l = lo + 1;
	int r = hi;
	while (true) {
		while (l < r && a[l] <= pivot) l++;
		while (l < r && a[r] >= pivot) r--;
		if (l == r) break;
		swap(a, l, r);
	}

	if (pivot < a[l]) l--;
	swap(a, lo, l);
	return l;
}

static inline void swap(int a[], int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

