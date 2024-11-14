#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 200
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n);
element pop(int* n);

int main()
{
	FILE* f;
	element item;
	char str[MAX_STRING_SIZE];
	char* token;
	char* next_str;
	char* delimiter = " ";
	int i;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL) {
		fprintf(stderr, "file does not open\n");
		exit(EXIT_FAILURE);
	}

	fgets(str, MAX_STRING_SIZE, f);
	fclose(f);
	printf("***** insertion into a min heap *****\n");
	token = strtok_s(str, delimiter, &next_str);
	while (token) {
		item.key = atoi(token);
		push(item, &n);
		for (i = 1; i <= n; i++)
			printf("%3d", heap[i].key);
		puts("");
		token = strtok_s(NULL, delimiter, &next_str);
	}

	printf("***** deletion from a min heap *****\n");
	while (n != 0) {
		printf("delete data = %d\n", pop(&n));
		for (i = 1; i <= n; i++)
			printf("%3d", heap[i].key);
		puts("");
	}

	return 0;
}

void push(element item, int* n)
{
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int* n)
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key > heap[child + 1].key))
			child++;
		if (temp.key <= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}