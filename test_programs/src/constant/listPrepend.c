
#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

struct node *createList(int size);
struct node *newNode(int value);
struct node *listPrepend(struct node *list, int value);
void freeList(struct node *list);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "error: %s <list size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[1]);
	struct node *list = createList(size);

	list = listPrepend(list, 42);

	freeList(list);
}

struct node *createList(int size) {
	struct node *head = NULL;
	struct node *curr = NULL;

	for (int i = 0; i < size; i++) {
		struct node *n = newNode(i);
		if (head == NULL) {
			head = n;
		} else {
			curr->next = n;
		}
		curr = n;
	}

	return head;
}

struct node *newNode(int value) {
	struct node *n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	n->value = value;
	n->next = NULL;
	return n;
}

struct node *listPrepend(struct node *list, int value) {
	struct node *n = newNode(value);
	n->next = list;
	return n;
}

void freeList(struct node *list) {
	struct node *curr = list;
	while (curr != NULL) {
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

