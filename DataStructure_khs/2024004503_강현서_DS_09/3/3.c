#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}lsitNode;

listPointer first = NULL;

listPointer createNode(int data);
void insertLast(listPointer* last, listPointer node);
void deleteList(listPointer* first, listPointer* last, listPointer x, listPointer pre);
void printList(listPointer first, listPointer last);

listPointer createNode(int data) {
	listPointer temp = NULL;
	temp = (listPointer)malloc(sizeof(*temp));
	
	if (temp == NULL)
	{
		printf("할당 실패!\n");
		return NULL;
	}

	temp->data = data;
	temp->link = NULL;

	return temp;
}

void insertLast(listPointer* last, listPointer node) {
	if ((*last) == NULL) {
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
		(*last) = node;
	}
}

void deleteList(listPointer* first, listPointer *last, listPointer x, listPointer pre) {
	if ((*first) == (*last))
		(*first) = (*last) = NULL;
	else {
		pre->link = x->link;

		if (x == (*first))
			(*first) = (*last)->link;
		else if (x == (*last))
			(*last) = pre;
	}
	free(x);
}

void printList(listPointer first, listPointer last) {
	int cnt = 0;

	printf("The Circularly Linked List contains:\n");
	do {
		printf("(%p, %5d, %p )",
			first, first->data, first->link);
		first = first->link;
		cnt++;
		if (cnt % 3 == 0)
			printf("\n");
	} while (first != last->link);
}

int main() {
	int num = 0;
	listPointer newNode = NULL;
	listPointer tail = NULL;
	FILE* fp;
	fp = fopen("input.txt", "r");

	while (fscanf(fp, "%d ", &num) != EOF)
	{
		newNode = createNode(num);
		insertLast(&tail, newNode);
	}
	fclose(fp);

	if (tail != NULL)
		first = tail->link;

	printList(first, tail);
	printf("\n");

	listPointer current = first;
	listPointer pre = tail;
	do {
		if (current->data % 2 != 0)
		{
			deleteList(&first, &tail, current, pre);
			if (pre != NULL)
				current = pre->link;
		}
		else {
			if (first != tail) {
				pre = current;
				current = current->link;
			}
		}
	} while (current != first);

	printf("\nAfter deleting nodes with odd value\n");
	printf("\n");
	printList(first, tail);
	
	while (first)
		deleteList(&first, &tail, first, tail);
}