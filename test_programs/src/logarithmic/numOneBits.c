
#include <stdio.h>
#include <stdlib.h>

int numOneBits(int n);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <array size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	int res = numOneBits(n);
	printf("Number of 1 bits: %d\n", res);
}

int numOneBits(int n) {
	int count = 0;
	while (n > 0) {
		if (n & 1) {
			count++;
		}
		n >>= 1;
	}
	return count;
}

