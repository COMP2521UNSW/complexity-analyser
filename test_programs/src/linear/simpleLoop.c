
#include <stdio.h>
#include <stdlib.h>

void simpleLoop(int n);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	simpleLoop(n);
}

void simpleLoop(int n) {
	for (int i = 0; i < n; i++);
}

