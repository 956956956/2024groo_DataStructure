#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

int heap[MAX_ELEMENTS];

void push(int item, int* n);
int pop(int* n);
void printHeap(int n);

int main() {
	FILE* fp = fopen("input.txt", "r");
	int elm = 0;
	int n = 0;

	printf("***** insertion into a max heap *****\n");
	while (fscanf(fp, "%d ", &elm) != EOF)
		push(elm, &n);

	int len = n;
	printf("***** deletion from a max heap *****\n");
	for (int i = 1; i <= len; i++)
		pop(&n);
}

void push(int item, int* n) {
	int i = 0;
	if (HEAP_FULL(*n))
		exit(1);
	i = ++(*n);
	while ((i != 1) && (item > heap[i / 2])) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;

	printHeap(*n);
}

int pop(int* n) {
	int parent, child;
	int item, temp;
	if (HEAP_EMPTY(*n))
		exit(EXIT_FAILURE);
	item = heap[1];
	temp = heap[(*n)--];
	
	parent = 1;
	child = 2;

	while (child <= *n) {
		if ((child < *n) && (heap[child] < heap[child + 1]))
			child++;
		if (temp >= heap[child]) break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	
	printf("delet data = %d\n", item);
	printHeap(*n);
	
	return item;
}

void printHeap(int n) {
	for (int i = 1; i <= n; i++)
		printf(" %2d", heap[i]);
	printf("\n");
}