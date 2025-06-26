
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isLeapYear(int year);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <year>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int year = atoi(argv[1]);
	bool result = isLeapYear(year);
	printf("%d %s a leap year\n", year, result ? "is" : "is not");
}

bool isLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	} else if (year % 100 == 0) {
		return false;
	} else if (year % 4 == 0) {
		return true;
	} else {
		return false;
	}
}

