#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;
nodePointer head = NULL;


nodePointer insertLast(nodePointer, nodePointer);
void printForward(nodePointer);
void printBackward(nodePointer);
nodePointer deleteLessThanFifty(nodePointer);
void freeAll(nodePointer);


int main() {
	FILE* fp;
	head = (nodePointer)malloc(sizeof(struct node));
	head->data = NULL;
	head->llink = head->rlink = head;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	while (!feof(fp)) {
		nodePointer new = (nodePointer)malloc(sizeof(struct node));
		fscanf(fp, "%d", &new->data);
		head = insertLast(head, new);
	}

	printForward(head);

	printBackward(head);

	head = deleteLessThanFifty(head);
	printf("\n\nAfter deleting numbers less than and equal to 50 :\n");
	printForward(head);
	printBackward(head);

	freeAll(head);
}

void printForward(nodePointer head) {
	printf("\nforward\n");
	nodePointer p = head->rlink;
	do {
		printf("(%p %d %p)  ", p, p->data, p->rlink);
		p = p->rlink;
	} while (p != head);
	return;
}

void printBackward(nodePointer head) {
	printf("\nBackward\n");
	nodePointer p = head->llink;
	do {
		printf("(%p %d %p)  ", p, p->data, p->llink);
		p = p->llink;
	} while (p != head);
	return;
}


nodePointer insertLast(nodePointer head, nodePointer new) {
	nodePointer p = head;
	while (p->rlink != head)
		p = p->rlink;
	p->rlink->llink = new;
	new->rlink = p->rlink;
	p->rlink = new;
	new->llink = p;
	return head;
}

nodePointer deleteLessThanFifty(nodePointer head) {
	nodePointer p = head->rlink;
	nodePointer del;
	do {
		if (p->data <= 50) {
			del = p;
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			p = p->rlink;
			free(del);
		}
		else
			p = p->rlink;
	} while (p != head);
	return head;
}

void freeAll(nodePointer head) {
	nodePointer p = head->rlink;
	nodePointer del;
	do {
		del = p;
		p = p->rlink;
		free(del);
	} while (p != head);
	free(p);
}