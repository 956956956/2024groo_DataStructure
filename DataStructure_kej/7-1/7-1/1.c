// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
} polyNode;
polyPointer a = NULL, b = NULL, c = NULL;

polyPointer append(polyPointer h, int coef, int expon);
void pmultiply(int num1, int num2);
void insertSorted(int coef, int expon);
void printData(polyPointer h);

int main() {
	FILE* fp1 = fopen("poly1.txt", "r"), * fp2 = fopen("poly2.txt", "r");
	polyPointer curr;
	int i, num1, num2, coef, expon;

	if (!fp1 || !fp2) {
		puts("Cannot open the file.");
		exit(1);
	}

	// ���׽� a
	fscanf(fp1, "%d", &num1);
	for (i = 0; i < num1; i++) {
		fscanf(fp1, "%d %d", &coef, &expon);
		a = append(a, coef, expon);
	}
	printf("poly1:\n");
	printData(a);

	// ���׽� b
	fscanf(fp2, "%d", &num2);
	for (i = 0; i < num2; i++) {
		fscanf(fp2, "%d %d", &coef, &expon);
		b = append(b, coef, expon);
	}
	printf("poly2:\n");
	printData(b);

	// ���׽� c = a*b
	pmultiply(num1, num2);
	printf("poly1 * poly2:\n");
	printData(c);

	fclose(fp1);
	fclose(fp2);
	return 0;
}

/* ���׽� a, b ���� ����Ʈ ����� �Լ� */
polyPointer append(polyPointer h, int coef, int expon){
	polyPointer p, curr;

	curr = (polyNode*)malloc(1 * sizeof(polyNode));
	curr->coef = coef;
	curr->expon = expon;
	curr->link = NULL;

	if (h == NULL)
		h = curr;
	else {
		p = h;
		while (p->link != NULL)
			p = p->link;
		p->link = curr;
	}
	return h;
}

/* ���׽� a, b�� ���Ͽ� ���׽� c�� ����� �Լ� */
void pmultiply(int num1, int num2) {
	polyPointer aCopy, bCopy, temp;
	int i, j, coef, expon;
	aCopy = a;
	bCopy = b;

	for (i = 0; i < num1; i++) {
		for (j = 0; j < num2; j++) {
			coef = (aCopy->coef) * (bCopy->coef);
			if ((aCopy->expon) == 0)
				expon = bCopy->expon;
			else if ((bCopy->expon) == 0)
				expon = aCopy->expon;
			else
				expon = (aCopy->expon)+(bCopy->expon);
			insertSorted(coef, expon);
			bCopy = bCopy->link;
		}
		aCopy = aCopy->link;
		bCopy = b;
	}
}

/* ���׽� c�� ���� ����Ʈ�� ����� �Լ� */
void insertSorted(int coef, int expon) {
	polyPointer node, p, q;

	node = (polyNode*)malloc(1 * sizeof(polyNode));
	node->coef = coef;
	node->expon = expon;

	p = c;
	q = c;
	while (p != NULL) {
		if (p->expon <= expon)
			break;

		q = p;
		p = p->link;
	}

	if (p == c) {	// ù ��°�� ��
		node->link = c;
		c = node;
	}
	else if ((p!=NULL) && p->expon == expon) {	// ������ ���� �� (p!=NULL ���� ����)
		p->coef = p->coef + coef;
		if (p->coef == 0) {
			/* delete Node */
			q->link = p->link;
			free(p);
		}
	}
	else {	// �׷��� ���� ��
		node->link = p;
		q->link = node;
	}
}

/* ���� ����Ʈ�� ����ϴ� �Լ� */
void printData(polyPointer h) {
	polyPointer p;

	p = h;
	while (p != NULL) {
		printf("[%d, %d] ", p->coef, p->expon);
		p = p->link;
	}
	printf("\n");
}