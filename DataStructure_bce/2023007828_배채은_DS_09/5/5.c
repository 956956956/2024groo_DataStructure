#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
};
polyPointer startA, startB, startC;
polyPointer avail = NULL;


polyPointer insertHead(polyPointer first, polyPointer new) {
	polyPointer p = first->link;
	first->link = new;
	new->link = p;

	return first;
}

polyPointer insertLast(polyPointer first, polyPointer new) {
	polyPointer p = first;
	while (p->link != first)
		p = p->link;
	p->link = new;
	new->link = first;
	return first;
}

void polyPrint(polyPointer first) {
	polyPointer p = first;
	do {
		if (p->coef)
			printf("(%p:  %+dx^%d : %p)\n", p, p->coef, p->expon, p->link);
		p = p->link;
	} while (p != first && p!=NULL);
	return;
}

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}

void retNode(polyPointer p) {
	p->link = avail;
	avail = p;
}

polyPointer getNode() {
	if (avail == NULL)
		return NULL;
	else {
		polyPointer tmp = avail;
		avail = avail->link;
		return tmp;
	}
}

polyPointer createNode(int coef, int expon) {
	polyPointer tmp = getNode();
	if(tmp==NULL)
		tmp = (polyPointer)malloc(sizeof(struct polyNode));
	tmp->coef = coef;
	tmp->expon = expon;
	tmp->link = NULL;
	return tmp;
}

polyPointer polyAdd(polyPointer a, polyPointer b) {
	polyPointer pa, pb, tmp;
	pa = a->link; pb = b->link;
	while (pa->expon != -1 && pb->expon != -1) {
		switch (compare(pa->expon, pb->expon)) {
		case -1:
			tmp = createNode(pb->coef, pb->expon);
			startC = insertLast(startC, tmp);
			pb = pb->link;
			break;
		case 0:
			tmp = createNode(pb->coef + pa->coef, pb->expon);
			startC = insertLast(startC, tmp);
			pa = pa->link;
			pb = pb->link;
			break;
		case 1:
			tmp = createNode(pa->coef, pa->expon);
			startC = insertLast(startC, tmp);
			pa = pa->link;
			break;
		}
	}
	for (; pa->expon != -1; pa = pa->link)
		startC = insertLast(startC, pa);
	for (; pb->expon != -1; pb = pb->link)
		startC = insertLast(startC, pb);

	return startC;
}

void erase(polyPointer p) {
	polyPointer temp;
	while (p != NULL) {
		temp = p;
		p = p->link;
		free(temp);
	}
}

void returnToAvail(polyPointer p) {
	polyPointer tmp;
	if (p) {
		tmp = p->link;
		p->link = avail;
		avail = tmp;
		p = NULL;
	}
}

int main() {
	FILE* fpa = fopen("a.txt", "r");
	FILE* fpb = fopen("b.txt", "r");
	char order;

	startA = (polyPointer)malloc(sizeof(struct polyNode));
	startB = (polyPointer)malloc(sizeof(struct polyNode));
	startC = (polyPointer)malloc(sizeof(struct polyNode));

	startA->expon = startB->expon = startC->expon = -1;
	startA->link = startA;
	startB->link = startB;
	startC->link = startC;

	fscanf(fpa, "%c", &order);
	while (!feof(fpa)) {
		polyPointer tmp = (polyPointer)malloc(sizeof(struct polyNode));
		fscanf(fpa, "%d %d", &tmp->coef, &tmp->expon);
		tmp->link = NULL;
		if (order == 'a')
			startA = insertHead(startA, tmp);
		else if (order == 'd')
			startA = insertLast(startA, tmp);
	}
	fclose(fpa);

	fscanf(fpb, "%c", &order);
	while (!feof(fpb)) {
		polyPointer tmp = (polyPointer)malloc(sizeof(struct polyNode));
		fscanf(fpb, "%d %d", &tmp->coef, &tmp->expon);
		tmp->link = NULL;
		if (order == 'a')
			startB = insertHead(startB, tmp);
		else if (order == 'd')
			startB = insertLast(startB, tmp);
	}
	fclose(fpb);

	printf("   a :\n");
	polyPrint(startA);
	printf("\n   b :\n");
	polyPrint(startB);

	startC = polyAdd(startA, startB);
	printf("\na+b=c :\n");
	polyPrint(startC);

	returnToAvail(startA);
	returnToAvail(startB);
	returnToAvail(startC);
	printf("\navail : \n");
	polyPrint(avail);

	erase(avail);
}