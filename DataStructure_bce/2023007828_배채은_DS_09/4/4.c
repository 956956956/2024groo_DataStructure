#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
};
polyPointer a = NULL, b = NULL, c = NULL;

polyPointer insertHead(polyPointer first, polyPointer new) {
	polyPointer p = first;
	first = new;
	new->link = p;
	return first;
}

polyPointer insertLast(polyPointer first, polyPointer new) {
	polyPointer p = first;
	if (p == NULL) {
		first = new;
	}
	else {
		while (p->link != NULL)
			p = p->link;
		p->link = new;
	}
	return first;
}

void polyPrint(polyPointer first) {
	polyPointer p = first;
	while (p!=NULL) {
		printf("(%p:  %+dx^%d : %p)\n", p, p->coef, p->expon, p->link);
		p = p->link;
	}
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

polyPointer createNode(int coef, int expon) {
	polyPointer tmp = (polyPointer)malloc(sizeof(struct polyNode));
	tmp->coef = coef;
	tmp->expon = expon;
	tmp->link = NULL;
	return tmp;
}

polyPointer polyAdd(polyPointer a, polyPointer b) {
	polyPointer pa, pb, tmp;
	pa = a; pb = b;
	while (pa!=NULL && pb!=NULL) {
		switch (compare(pa->expon, pb->expon)) {
		case -1:
			tmp = createNode(pb->coef, pb->expon);
			c = insertLast(c, tmp);
			pb = pb->link;
			break;
		case 0:
			tmp = createNode(pb->coef + pa->coef, pb->expon);
			c = insertLast(c, tmp);
			pa = pa->link;
			pb = pb->link;
			break;
		case 1:
			tmp = createNode(pa->coef, pa->expon);
			c = insertLast(c, tmp);
			pa = pa->link;
			break;
		}
	}
	for (; pa != NULL; pa = pa->link) {
		tmp = createNode(pa->coef, pa->expon);
		c = insertLast(c, tmp);
	}
	for (; pb != NULL; pb = pb->link) {
		tmp = createNode(pb->coef, pb->expon);
		c = insertLast(c, tmp);
	}
	return c;
}

void erase(polyPointer p){
	polyPointer temp;
	while (p!=NULL) {
		temp = p;
		p = p->link;
		free(temp);
 	}
}

int main() {
	FILE* fpa = fopen("a.txt", "r");
	FILE* fpb = fopen("b.txt", "r");
	char order;
	fscanf(fpa, "%c", &order);
	while (!feof(fpa)) {
		polyPointer tmp = (polyPointer)malloc(sizeof(struct polyNode));
		fscanf(fpa, "%d %d", &tmp->coef, &tmp->expon);
		tmp->link = NULL;
		if (order == 'a')
			a = insertHead(a, tmp);
		else if (order == 'd')
			a = insertLast(a, tmp);
	}
	fclose(fpa);

	fscanf(fpb, "%c", &order);
	while (!feof(fpb)) {
		polyPointer tmp = (polyPointer)malloc(sizeof(struct polyNode));
		fscanf(fpb, "%d %d", &tmp->coef, &tmp->expon);
		tmp->link = NULL;
		if (order == 'a')
			b = insertHead(b, tmp);
		else if (order == 'd')
			b = insertLast(b, tmp);
	}
	fclose(fpb);

	printf("   a :\n");
	polyPrint(a);
	printf("\n   b :\n");
	polyPrint(b);

	c = polyAdd(a, b);
	printf("\n   a+b=c :\n");
	polyPrint(c);

	erase(a);
	erase(b);
	erase(c);
}