#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

nodePointer seq[MAX_SIZE] = { NULL, };
int N;

void insertNode(int i, int j);
void equivalence();

int main() {
	FILE* fp = fopen("input.txt", "r");
	nodePointer p;
	int i, j;
	fscanf(fp, "%d", &N);

	//input
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &i, &j);
		insertNode(i, j);
		insertNode(j, i);
	}


	printf("symmetric 관계 linked List\n");
	for (i = 0; i < N; i++) {
		p = seq[i];
		printf("%d : symmetric 관계:\n", i);
		 while (p != NULL) {
			printf("(%p %d %p)  ", p, p->data, p->link);
			p = p->link;
		 } 
		 printf("\n");
	}

	equivalence();
}

void insertNode(int i, int j) {
	nodePointer x = (nodePointer)malloc(sizeof(struct node));
	x->data = j;
	x->link = seq[i];
	seq[i] = x;
}

/*
0 4 7 11 2
1 3 5
6 10 8 9

0 11 4 7 2
1 3 5
6 8 10 9
*/
//처음 짠 코드는 스택에서 꺼낼 때 프린트
//정답 코드는 스택에 넣을 때 프린트

void equivalence() {
	nodePointer p;
	int i, top = -1, n;
	int out[MAX_SIZE], stack[MAX_SIZE];
	//initialize
	for (i = 0; i < N; i++) {
		out[i] = TRUE;
	}
	for (i = 0; i < N; i++) {
		if (out[i] == TRUE) {
			printf("\nNew class:");
			printf("%5d", i);
			out[i] = FALSE;
			p = seq[i];
			for (;;) {
				while (p) {
					if (out[p->data]) {
						printf("%5d", p->data);
						stack[++top] = p->data;
						out[p->data] = FALSE;
					}
					else
						p = p->link;
				}
				if (top == -1)
					break;
				p = seq[stack[top--]];
			}

		}
	}
}

