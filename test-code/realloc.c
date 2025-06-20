// Unfortunately, callgrind does not count the instructions executed in
// kernel mode, which affects some library functions which we use,
// notably calloc and realloc. We may be able to solve this by creating
// proxies for these functions and redirecting their calls to them
// during autotesting.
//
// void *_calloc(size_t nmemb, size_t size) {
//     void *ptr = calloc(nmemb, size);
//     if (!ptr) return NULL;
//     memset(ptr, 0, nmemb * size);
//     return ptr;
// } 

#include <stdio.h>
#include <stdlib.h>

void run(int n);

int main(int argc, char *argv[]) {
	int n = argc == 1 ? 0 : atoi(argv[1]);
	run(n);
}

void run(int n) {
	int *arr = NULL;
	for (int i = 0; i < n; i++) {
		arr = realloc(arr, (i + 1) * sizeof(int));
		arr[i] = i;
		malloc(sizeof(int));
	}
}

