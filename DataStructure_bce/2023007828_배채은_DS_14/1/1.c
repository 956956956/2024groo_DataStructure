#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

typedef struct {
	int key;
}element;

element heap[MAX_ELEMENT];
int size = 0;

void insertHeap(element*, int);
void printHeap(element*);
element deleteHeap(element*);

int main() {
	FILE* fp;
	int tmpD;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "%s", "file open error\n");
		exit(EXIT_FAILURE);
	}

	printf("***** insertion into a max heap *****\n");
	while (fscanf(fp, "%d", &tmpD) == 1) {
		insertHeap(&heap, tmpD);
		printHeap(&heap);
	}
	
	printf("***** deletion from a max heap *****\n");
	while (size!=0) {
		element item = deleteHeap(&heap);
		printf("delet data = %d\n", item.key);
		printHeap(&heap);
	}

}

element deleteHeap(element* heap) {
	int parent = 1, child = 2;
	element tmp = heap[size--];
	element item = heap[1];

	while (child <= size) {
		if ((child < size) && heap[child].key < heap[child + 1].key)
			//오른쪽 자식이 더 클 수 있음
			child++;
		if (tmp.key >= heap[child].key) break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2; //원래 child의 leftChild로 이동
	}
	heap[parent] = tmp;
	return item;
}

void printHeap(element* heap) {
	for (int i = 1; i <= size; i++) {
		printf("%d ", heap[i].key);
	}
	printf("\n");
}

void insertHeap(element* heap, int data) {
	int i = ++size;

	while (i != 1 && data > heap[i/2].key) {
		heap[i] = heap[i / 2];
		i /= 2;
	}

	heap[i].key = data;
}