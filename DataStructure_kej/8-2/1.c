// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	char name[10];
	int num;
	int score;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

void push(element item);
element pop();
void postorder(int index);

int main() {
	FILE* fp = fopen("in.txt", "r");
	element item;
	int i, student;

	if (!fp) {
		printf("The file cannot open.");
		exit(1);
	}

	// ���� �Է�
	fscanf(fp, "%d", &student);
	for (i = 0; i < student; i++) {
		fscanf(fp, "%s %d %d", item.name, &(item.num), &(item.score));
		push(item);
	}

	// level order�� ���
	printf("Min heap(level order):\n");
	for (i = 1; i <= student; i++)
		printf("[%s, %d��] ", heap[i].name, heap[i].score);
	printf("\n\n");

	// ���� �޴� �л��� delete �� ���
	for (i = 1; i < 5; i++) {
		item = pop();
		printf("Delte #%d [%s, %d��, %d��]\n", i, item.name, item.num, item.score);
	}
	
	// delete �� �� ���� min heap�� postorder traversal�� ���
	printf("\nAfter deleting(postorder):\n");
	postorder(1);
	return 0;
}

// heap�� push�ϴ� �Լ�
void push(element item) {
	int i;
	if (HEAP_FULL(n)) {
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}
	i = ++n;
	while ((i != 1) && (item.score < heap[i / 2].score)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

// heap���� delete�ϴ� �Լ�
element pop() {
	int parent, child;
	element item, temp;

	if (HEAP_EMPTY(n)) {
		fprintf(stderr, "The heap is empty. \n");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[n--];
	parent = 1;
	child = 2;
	while (child <= n) {
		if ((child < n) && (heap[child].score > heap[child + 1].score))
			child++;
		if (temp.score <= heap[child].score)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;

}

// heap ��ҵ��� postorder traversal�� ����ϴ� �Լ�
void postorder(int index) {
	if (index <= n) {
		postorder(2*index);
		postorder(2*index+1);
		printf("[%s, %d��] ", heap[index].name, heap[index].score);
	}
	return;
}