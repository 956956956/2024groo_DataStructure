#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 20

typedef struct listNode {
	char name[MAX_NAME_SIZE];
	char job[MAX_NAME_SIZE];
	char sex[5];
	struct listNode* link;
} listNode;

listNode* first = NULL;
listNode* firstF = NULL;
listNode* firstM = NULL;
listNode* firstC = NULL;

void printList(listNode* f) {
	listNode* p = f;
	printf("The ordered list contains:\n");
	while (p != NULL) {
		printf("(%p, %4s, %4s, %4s, %p)", p, p->name, p->job, p->sex, p->link);
		p = p->link;
	}
	return;
}

listNode* combineList(listNode* one, listNode* two) {
	listNode* p;
	p = one;
	while (p->link != NULL)
		p = p->link;
	p->link = two;
	return one;
}

listNode* insertNode(listNode* f, listNode* new) {
	listNode* p = f;
	if (p == NULL) {
		f = new;
		return f;
	}
	else {
		while (p->link != NULL) {
			p = p->link;
		}
		p->link = new;
	}
	return f;
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

listNode* inverseList(listNode* first) {
	listNode* lead,* middle,* trail;
	lead = first;
	middle = NULL;
	while (lead != NULL) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}




int main() {
	FILE* fp;
	fp = fopen("input.txt", "r");
	char name[MAX_NAME_SIZE], job[MAX_NAME_SIZE], sex[3];
	while (!feof(fp)) {
		listNode* tmp1 = (listNode*)malloc(sizeof(struct listNode));
		listNode* tmp2 = (listNode*)malloc(sizeof(struct listNode));
		fscanf(fp, "%s %s %s", tmp1->name, tmp1->job, tmp1->sex);
		tmp1->link = tmp2->link = NULL;
		strcpy(tmp2->job, tmp1->job);
		strcpy(tmp2->name, tmp1->name);
		strcpy(tmp2->sex, tmp1->sex);

		if(strcmp(tmp1->sex, "남자")==0)
			firstM = insertNode(firstM, tmp1);
		else if(strcmp(tmp1->sex, "여자") == 0)
			firstF = insertNode(firstF, tmp1);

		first = insertNode(first, tmp2);	
	}

	fclose(fp);
	printf("전체 리스트\n");
	printList(first);
	printf("\n남자 리스트\n");
	printList(firstM);
	printf("\n여자 리스트\n");
	printList(firstF);

	firstC = combineList(firstF, firstM);
	printf("\n합친 리스트\n");
	printList(firstC);

	firstC = inverseList(firstC);
	printf("\n\nInversed list\n");
	printList(firstC);


}