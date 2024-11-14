#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;

polyPointer avail = NULL;

polyPointer getNode();
void retALL(polyPointer *ptr);
void createPoly(FILE* fp, polyPointer* poly);
void insertPoly(int coef, int expon, polyPointer trail);
void attach(int coef, int expon, polyPointer* ptr);
polyPointer padd(polyPointer a, polyPointer b);
void erase(polyPointer* ptr);
void printPoly(polyPointer first, polyPointer last);
polyPointer findLast(polyPointer trail);

polyPointer getNode() {
	polyPointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else
		node = (polyPointer)malloc(sizeof(*node));
	return node;
}

void retALL(polyPointer* ptr) {
	// ptr은 환형 리스트에서 맨 마지막 노드
	polyPointer temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = avail;	// ptr->link == NULL
		avail = temp;
		*ptr = NULL;
	}
}

void createPoly(FILE* fp, polyPointer* poly) {
	polyPointer trail = NULL;
	(*poly) = getNode();
	(*poly)->expon = -1; (*poly)->link = (*poly);
	trail = (*poly);

	char ord; int coef = 0, expon = 0;
	fscanf(fp, "%c", &ord);

	if (ord == 'd') {	// 뒤로뒤로 추가(항상 맨 마지막에 추가)
		while (fscanf(fp, "%d %d", &coef, &expon) != EOF)
		{
			insertPoly(coef, expon, trail);
			trail = trail->link;
		}
		return;
	}
	else if (ord == 'a') {
		while (fscanf(fp, "%d %d", &coef, &expon) != EOF)
			insertPoly(coef, expon, trail);
	}
}

void insertPoly(int coef, int expon, polyPointer trail) {
	polyPointer temp;
	temp = getNode();
	if (temp == NULL) return;
	
	temp->coef = coef;
	temp->expon = expon;
	
	temp->link = (trail)->link;
	(trail)->link = temp;
}

void attach(int coef, int expon, polyPointer* ptr) {
	polyPointer temp = NULL;
	temp = getNode();
	if (temp == NULL) return;

	temp->coef = coef;
	temp->expon = expon;

	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer startA, c, lastC;
	int sum, done = 0;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();

	c->expon = -1; lastC = c;
	do {
		if (a->expon < b->expon) {
			attach(b->coef, b->expon, &lastC);
			b = b->link;
		}
		else if (a->expon == b->expon) {
			if (startA == a) done = 1;
			else {
				sum = a->coef + b->coef;
				if (sum) attach(sum, a->expon, &lastC);
				a = a->link, b = b->link;
			}
		}
		else {
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}

void erase(polyPointer* ptr) {
	polyPointer temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = temp->link;
		free(temp);
	}
}

polyPointer findLast(polyPointer trail) {
	polyPointer last =  NULL;
	while (trail->link->expon == -1)
		trail = trail->link;
	last = trail;
	return last;
}

void printPoly(polyPointer first, polyPointer last) {
	do {		
		if (first->coef > 0) {
			printf("(%p :    +%dx^%d    : %p)\n",
				first, first->coef, first->expon, first->link);
		}
		else {
			printf("(%p :    %dx^%d    : %p)\n", first,
				first->coef, first->expon, first->link);
		}
		first = first->link;
	} while (first != last); // 조건문 다시 생각!!
}

int main() {
	polyPointer a = NULL, b = NULL, c = NULL;
	FILE* fp1,* fp2;

	fp1 = fopen("a.txt", "r");
	createPoly(fp1, &a);
	fclose(fp1);

	fp2 = fopen("b.txt", "r");
	createPoly(fp2, &b);
	fclose(fp2);

	polyPointer lastA = NULL, lastB = NULL, lastC = NULL;
	lastA = findLast(a);
	lastB = findLast(b);

	printf("a :\n");
	printPoly(a, lastA);

	printf("\nb :\n");
	printPoly(b, lastB);

	c = padd(a, b);

	lastC = findLast(c);
	printf("\na + b = c :\n");
	printPoly(c, lastC);

	retALL(&lastA);
	retALL(&lastB);
	retALL(&lastC);

	printf("\navail: \n");
	printPoly(avail, NULL);

	while (avail)
		erase(&avail);
}