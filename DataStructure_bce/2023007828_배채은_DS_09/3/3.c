#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;
listPointer first = NULL;


listPointer delOdd(listPointer first) {
	listPointer p = first->link;
	listPointer prev = first;
	do {
		if (p->data % 2 == 1) {
			if (p == first) {
				first = first->link;
				prev->link = first;
				free(p);
				p = first;
			}
			else {
				prev->link = p->link;
				free(p);
				p = prev->link;
			}
		}
		else {
			prev = p;
			p = p->link;
		}
	} while (p != first);
	return first;
}

void printList(listPointer first) {
	listPointer p = first;
	printf("The Circularly Linked List contains:\n");
	while (p->link != first) {
		printf("(%p, %4d, %p)", p, p->data, p->link);
		p = p->link;
	}
	printf("(%p, %4d, %p)\n", p, p->data, p->link);
	return;
}

listPointer insertLast(listPointer new) {
	listPointer p = first;
	if (p == NULL) {
		first = new;
		first->link = first;
	}
	else {
		while (p->link != first)
			p = p->link;
		p->link = new;
		new->link = first;
	}
	return first;
}

void freeList(listPointer first) {
	listPointer p = first->link->link;
	listPointer prev = first->link;
	do{
		free(prev);
		prev = p;
		p = p->link;
	} while (p != first);
	free(p);
}

int main() {
	FILE* fp;
	fp = fopen("input.txt", "r");
	while (!feof(fp)) {
		listPointer tmp = (listPointer)malloc(sizeof(struct listNode));
		fscanf(fp, "%d", &tmp->data);
		tmp->link = NULL;
		first = insertLast(tmp);
	}
	fclose(fp);
	printList(first);

	first = delOdd(first);

	printf("\nAfter deleting nodes with odd value\n\n");
	printList(first);

	freeList(first);

}