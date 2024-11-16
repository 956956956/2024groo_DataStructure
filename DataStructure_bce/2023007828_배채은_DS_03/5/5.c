#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0: 1 ) 

typedef struct {
	float coef;
	int expon;
} term;

term terms[MAX_TERMS];
int avail = 0;

void poly_print(char ch[], int s, int e) {
	printf("%s = ", ch);
	for (int i = s; i < e - 1; i++)
		printf("%.0fx^%d + ", terms[i].coef, terms[i].expon);

	if (terms[e - 1].expon == 0)
		printf("%.0f\n", terms[e - 1].coef);
	else
		printf("%.0fx^%d\n", terms[e - 1].coef, terms[e - 1].expon);
}

void attatch(float coef, int expon) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void padd(int a_s, int a_e, int b_s, int b_e, int* d_s, int* d_e) {
	float tmp;
	*d_s = b_e;
	while (a_s < a_e && b_s < b_e) {
		switch COMPARE(terms[a_s].expon, terms[b_s].expon)
		{
		case -1:
			attatch(terms[b_s].coef, terms[b_s].expon);
			b_s++;
			break;
		case 0:
			tmp = terms[b_s].coef + terms[a_s].coef;
			if (tmp) attatch(terms[b_s].coef + terms[a_s].coef, terms[b_s].expon);
			a_s++;  b_s++;
			break;
		case 1:
			attatch(terms[a_s].coef, terms[a_s].expon);
			a_s++;
			break;
		}
	}
	for(;a_s<a_e;a_s++)
		attatch(terms[a_s].coef, terms[a_s].expon);
	for(;b_s<b_e;b_s++)
		attatch(terms[b_s].coef, terms[b_s].expon);
	*d_e = avail;
}



int main() {
	int i, A_num, B_num, a_s, a_e, b_s, b_e, d_s, d_e;
	printf("<< D(x) = A(x) + B(x) >>\n");
	printf("Input the number of items of A(x) : ");
	scanf("%d", &A_num);
	printf("Input the number of items of B(x) : ");
	scanf("%d", &B_num);
	a_s = 0; a_e = A_num;
	b_s = a_e; b_e = b_s + B_num;

	printf("\nInput in descending order\n");
	printf("coefficient and exponent of A(x)=10x^5+8x^3+7 ( 10 5, 8 3, 7 0 ) : ");
	for (i = a_s; i < a_e; i++) {
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
		avail++;
	}
	printf("coefficient and exponent of B(x)=10x^5+8x^2+3 ( 10 5, 8 2, 3 0 ) : ");
	for (i = b_s; i < b_e; i++) {
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
		avail++;
	}
	padd(a_s, a_e, b_s, b_e, &d_s, &d_e);

	poly_print("\nA(x)", a_s, a_e);
	poly_print("B(x)", b_s, b_e);
	poly_print("D(x)", d_s, d_e);



}