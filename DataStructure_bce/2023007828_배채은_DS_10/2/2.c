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

nodePointer insertLast(nodePointer h, nodePointer new);
nodePointer deleteLessThanFifty(nodePointer h);
void printForward(nodePointer h);
void printBackward(nodePointer h);


int main() {
	FILE* fp = fopen("input.txt", "r");
	head = (nodePointer)malloc(sizeof(struct node));
	head->data = -1;
	head->llink = head; head->rlink = head;
	while (!feof(fp)) {
		nodePointer new = (nodePointer)malloc(sizeof(struct node));
		fscanf(fp, "%d", &new->data);
		head = insertLast(head, new);
	}

	printf("After creating a doubly linked circular list with a head node : \n");
	printForward(head);
	printBackward(head);

	head = deleteLessThanFifty(head);

	printf("After deleting numbers less than and equal to 50 :\n");
	printForward(head);
	printBackward(head);
}

nodePointer insertLast(nodePointer h, nodePointer new) {
	new->llink = h->llink;
	new->rlink = h;
	h->llink->rlink = new;
	h->llink = new;
	return h;
}

nodePointer deleteLessThanFifty(nodePointer h) {
	nodePointer del, p = h->rlink;
	do {
		if (p->data <= 50) {
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			del = p;
			p = p->rlink;
			free(del);
		}
		else
			p = p->rlink;
	} while (p != h);
	return h;
}

void printForward(nodePointer h) {
	nodePointer p = h->rlink;
	printf("forward\n");
	do {
		printf("(%p  %d  %p)", p, p->data, p->rlink);
		p = p->rlink;
	} while (p != h);
	printf("\n\n");
}

void printBackward(nodePointer h) {
	nodePointer p = h->llink;
	printf("Backward\n");
	do {
		printf("(%p  %d  %p)", p, p->data, p->rlink);
		p = p->llink;
	} while (p != h);
	printf("\n\n");
}