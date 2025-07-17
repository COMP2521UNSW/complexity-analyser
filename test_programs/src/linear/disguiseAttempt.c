
#include <stdio.h>
#include <stdlib.h>

void disguiseAttempt(int n);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <n>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	disguiseAttempt(n);
}

void disguiseAttempt(int n) {
	for (int i = 0; i < 1000000; i++);
	for (int i = 0; i < n; i++);
}

