#include <stdlib.h>
#include <stdio.h>

void loop(int n);

int main(int argc, char *argv[]) {
	int n = argc == 1 ? 0 : atoi(argv[1]);
	loop(n);
}

void loop(int n) {
	for (int i = 0; i < n; i++);
}

