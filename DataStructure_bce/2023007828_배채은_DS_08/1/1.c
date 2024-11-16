#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
	int data;
	struct listNode* link;
} listNode;
listNode* first = NULL; // or struct listNode *first = NULL;

listNode* delOdd(listNode* first) {
	listNode* p = first;
	listNode* prev = NULL;
	while (p != NULL) {
		if (p->data % 2 != 0) {
			if (p == first) {
				first = first->link;
				free(p);
				p = first;
				prev = NULL;
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
	}
	return first;
}

void printList(listNode* first) {
	listNode* p = first;
	printf("The ordered list contains:\n");
	while (p != NULL) {
		printf("(%p, %4d, %p)", p, p->data, p->link);
		p = p->link;
	}
	return;
}

listNode* insertNode(listNode* new) {
	listNode* p = first;
	listNode* prev = NULL;
	if (p == NULL) {
		first = new;
		return first;
	}
	else {
		while (p != NULL && p->data <= new->data) {
			prev = p;
			p = p->link;
		}
		if (prev == NULL) {
			new->link = p;
			first = new;
		}
		else {
			prev->link = new;
			new->link = p;
		}
	}
	return first;
}

void freeList(listNode* first) {
	listNode* p = first->link;
	listNode* prev = first;
	while (1) {
		free(prev);
		if (p == NULL)
			break;
		else {
			prev = p;
			p = p->link;
		}
	}
}

int main() {
	FILE* fp;
	fp = fopen("input.txt", "r");
	while (!feof(fp)) {
		listNode* tmp = (listNode*)malloc(sizeof(struct listNode));
		fscanf(fp, "%d", &tmp->data);
		tmp->link = NULL;
		first = insertNode(tmp);
	}
	fclose(fp);
	printList(first);

	first = delOdd(first);

	printf("\nAfter deleting nodes with odd value\n\n");
	printList(first);

	freeList(first);
}