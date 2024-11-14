#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct polyNode *polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;

void create(FILE *fp, polyPointer* poly);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coef, int expon, polyPointer *ptr);
void fattach(int coef, int expon, polyPointer* ptr);
void erase(polyPointer* ptr);
void printPoly(polyPointer first);

void create(FILE* fp, polyPointer* poly)
{ // printf("\nIN CREATE ord: %c, coef: %d, expon: %d\n", ord, coef, expon);
	char ord; int coef = 0, expon = 0;
	fscanf(fp, "%c", &ord);

	polyPointer trail, temp = NULL;
	trail = (polyPointer)malloc(sizeof(*trail));
	if (trail == NULL) return;
	trail->link = NULL;
	*poly = trail;

	if (ord == 'd') {
		while (fscanf(fp, "%d %d", &coef, &expon) != EOF)
			attach(coef, expon, &trail);
		trail->link = NULL;
		temp = (*poly); (*poly) = (*poly)->link;
	}
	else if (ord == 'a') {
		while (fscanf(fp, "%d %d", &coef, &expon) != EOF)
			fattach(coef, expon, &trail);
		temp = trail; (*poly) = trail->link;
	}
	free(temp);
}

polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, rear, temp;
	int sum;
	rear = (polyPointer)malloc(sizeof(*rear));
	if (rear == NULL) return NULL;
	c = rear;

	while ( a && b ) {
		if (a->expon < b->expon) {
			attach(b->coef, b->expon, &rear);
			b = b->link;
		}
		else if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link; b = b->link;
		}
		else {
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;

	temp = c; c = c->link; free(temp);
	
	return c;
}

void attach(int coef, int expon, polyPointer* ptr)
{ // printf("\nIN ATTACH coef: %d expon: %d\n", coef, expon);
	polyPointer temp = NULL;
	temp = (polyPointer)malloc(sizeof(*temp));
	if (temp == NULL) return;
	
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;

	(*ptr)->link = temp;
	*ptr = temp;
}

void fattach(int coef, int expon, polyPointer* ptr)
{ // printf("\nIN RATTACH coef: %d expon: %d\n", coef, expon);
	polyPointer temp = NULL;
	temp = (polyPointer)malloc(sizeof(*temp));
	if (temp == NULL) return;

	(*ptr)->coef = coef;
	(*ptr)->expon = expon;
	temp->link = (*ptr);
	(*ptr) = temp;
}

void erase(polyPointer* ptr) {
	polyPointer temp;
	while (*ptr) {
		temp = (*ptr);
		(*ptr) = (*ptr)->link;
		free(temp);
	}
}

void printPoly(polyPointer first) {
	while (first) {
		if (first->coef > 0) {
			printf("(%p :    + %dx^%d    : %p)\n",
				first, first->coef, first->expon, first->link);
		}
		else {
			printf("(%p :    %dx^%d    : %p)\n", first,
				first->coef, first->expon, first->link);
		}
		first = first->link;
	} 
}

int main() {
	polyPointer a = NULL, b = NULL, c = NULL;
	FILE* fp1, *fp2;

	fp1 = fopen("a.txt", "r");
	create(fp1, &a);
	fclose(fp1);

	fp2 = fopen("b.txt", "r");
	create(fp2, &b);
	fclose(fp2);
	
	printf("a : \n");
	printPoly(a);
	
	printf("\nb : \n");
	printPoly(b);

	c = padd(a, b);

	printf("\na + b = c :\n");
	printPoly(c);

	erase(&a);
	erase(&b);
	erase(&c);
}