#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

int stack[MAX_SIZE];
int top = NULL;

void push(int item);
int pop();
void stackFull();
void stackEmpty();

void main(void)
{
	FILE* f;
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, search;
	int i, j, k, n;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "cannot open the file\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(f, "%d\n", &n);
	for (i = 0; i < n; i++) {
		out[i] = TRUE; seq[i] = NULL;
	}

	printf("/* MAX_SIZE of a set S : 24 */\n");
	printf("current size of S : %d\n", n);
	printf("S = { ");
	for (k = 0; k < n - 1; k++) printf("%d, ", k);
	printf("%d }\n", n - 1);
	printf("input pairs : ");

	while (!feof(f)) {
		fscanf_s(f, "%d %d\n", &i, &j);
		printf("%dR%d ", i, j);
		x = malloc(sizeof(*x));
		x->data = j; x->link = seq[i]; seq[i] = x;
		x = malloc(sizeof(*x));
		x->data = i; x->link = seq[j]; seq[j] = x;
	}

	puts(""); puts("");

	printf("symetric 관계 linked List\n");

	for (k = 0; k < n; k++) {
		printf("%d : symetric 관계:\n", k);
		search = seq[k];

		do {
			printf("(%p %d %p)\t", search, search->data, search->link);
			if (search->link == NULL) break;
			search = search->link;
		} while (1);

		puts("");
	}

	puts("");

	for (i = 0; i < n; i++) {
		if (out[i] == TRUE) {
			printf("\nNew class: %5d", i);
			out[i] = FALSE;
			x = seq[i]; top = -1;

			for (;;) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j); out[j] = FALSE;
						push(j);
						x = x->link;
					}
					else {
						x = x->link;
					}
				}

				if (top == -1) break;
				x = seq[pop()];
			}
		}
	}

	puts(""); puts("");

	return 0;
}

void push(int item)
{
	if (top >= MAX_SIZE - 1) {
		stackFull();
		return;
	}

	stack[++top] = item;

	return;
}

int pop()
{
	if (top == -1)
		stackEmpty();

	return stack[top--];
}

void stackFull()
{
	fprintf(stderr, "stack is full, cannot add element\n");
}

void stackEmpty()
{
	fprintf(stderr, "stack is empty, cannot delete element\n");
}