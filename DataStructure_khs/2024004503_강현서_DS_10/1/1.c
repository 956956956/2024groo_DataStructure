#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 24

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

int stack[MAX_SIZE];
int top = -1;

void push(int data);
int pop();
void initRelate(int i, int j, nodePointer seq[]);
void equivalence(int n, bool out[], nodePointer seq[]);
void printList(int n, nodePointer seq[]);

void push(int data) {
	if (top >= MAX_SIZE - 1)	// 스택 가득 차 있음
		return;
	stack[++top] = data;
}
int pop() {
	if (top < 0)	// 스택 비었음
		return -1;
	return stack[top--];
}

void initRelate(int i, int j, nodePointer seq[]) {
	nodePointer x, y;
	x = (nodePointer)malloc(sizeof(*x));
	if (!x) return;
	x->data = j; x->link = seq[i]; seq[i] = x;

	y = (nodePointer)malloc(sizeof(*x));
	if (!y) return;
	y->data = i; y->link = seq[j]; seq[j] = y;
}

void equivalence(int n, bool out[], nodePointer seq[])
{
	nodePointer x;
	int j;
	for (int i = 0; i < n; i++) {
		if (out[i]) {
			printf("\nNew class: %5d", i);
			out[i] = false;
			x = seq[i]; top = -1;

			for (;;) {		// i의 동치류 집합의 나머지 요소 찾기
				while (x) {	// x가 NULL이 아닌 동안
					j = x->data;
					if (out[j]) {
						printf("%5d", j); out[j] = false;
						push(j);
					}
					x = x->link;
				}
				if (top == -1) break;
				x = seq[pop()];
			}
		}
	}
}

void printList(int n, nodePointer seq[]) {
	nodePointer temp = NULL;
	for (int i = 0; i < n; i++) {
		printf("\n%d : symmetric 관계:\n", i);
		
		temp = seq[i];
		while (temp) {
			printf("(%p %d %p)  ",
				temp, temp->data, temp->link);
			temp = temp->link;
		}
	}
}

int main() {
	bool out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	int i = 0, j = 0, n = 0;

	FILE* fp;
	fp = fopen("input.txt", "r");

	// 전체집합 크기 입력받기
	fscanf(fp, "%d", &n);

	printf("/* MAX_SIZE of a set S : %d */\n", MAX_SIZE);
	printf("current size of S : %d\n", n);
	printf("S = { ");
	for (i = 0; i < n - 1; i++) printf("%d, ", i);
	printf("%d }\n", i);

	// out, seq 초기화
	for (i = 0; i < n; i++) {
		out[i] = true;
		seq[i] = NULL;
	}

	// 관계쌍 입력받기, 출력
	printf("input pairs : ");
	while (fscanf(fp, "%d %d", &i, &j) != EOF) {
		initRelate(i, j, seq);
		printf("%dR%d ", i, j);
	}
	printf("\n");
	
	// 관계 linked list 출력
	printf("\nsymmetric 관계 linked List");
	printList(n, seq);

	// 동치류 찾아 집합만든 후 출력
	printf("\n");
	equivalence(n, out, seq);
	printf("\n");
}