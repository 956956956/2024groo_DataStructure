#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24

typedef struct node* nodePointer;
typedef struct node{
	int data;
	nodePointer link;
} node;

int size, top=-1;
int stack[MAX_SIZE];
int out[MAX_SIZE] = { 0, };
nodePointer seq[MAX_SIZE] = { NULL, };
void storeData(int i, int j);
void printEquiRelation();
void printEquiClass();


int main() {
	int i ,j;
	FILE* fp;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &size);
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &i, &j);
		storeData(i, j);
		storeData(j, i);
	}
	printEquiRelation();
	printf("\n");
	printEquiClass();

}

void printEquiClass() {
	int i;
	nodePointer p;
	for (i = 0; i < size; i++) {
		if (!out[i]) {
			printf("New class:	%d", i);
			out[i] = 1;
			stack[++top] = i;
			p = seq[i];
			for (;;) {
				while (p) {
					if (!out[p->data]) {
						printf("	%d", p->data);
						stack[++top] = p->data;
						out[p->data] = 1;
					}
					p = p->link;
				}
				if (top == -1)break;
				p = seq[stack[top--]];
			}
			printf("\n");
		}

	}
}

void storeData(int i, int j) {
	nodePointer new = (nodePointer)malloc(sizeof(struct node));
	new->data = j;
	new->link = seq[i];
	seq[i] = new;
	return;
}

void printEquiRelation() {
	printf("symmetric 관계 linked List\n");
	for (int i = 0; i < size; i++) {
		printf("%d : symmetric 관계:\n", i);
		nodePointer p = seq[i];
		while (p) {
			printf("(%p %d %p) ", p, p->data, p->link);
			p = p->link;
		}
		printf("\n");
	}
}