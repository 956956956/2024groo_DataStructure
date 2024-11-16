// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int coef;
	int expon;
} Polynomial;


void padd(int startA, int finishA, int startB, int finishB, int* startC, int* finishC, Polynomial* terms);
void attach(int coefficient, int exponent, Polynomial* terms);

int avail = 0;
int numA, numB;

int main() {
	FILE *fp1 = fopen("in3.txt", "r"), *fp2 = fopen("out3.txt", "w");
	Polynomial* terms;
	int sa = 0, fa, sb, fb, sc, fc;

	if (!fp1 || !fp2) {
		puts("Cannot open the file");
		exit(1);
	}

	fscanf(fp1, "%d %d", &numA, &numB);
	fa = numA - 1;
	sb = fa + 1;
	fb = sb + numB - 1;
	avail = fb + 1;
	terms = (Polynomial*)malloc(sizeof(Polynomial) * (numA + numB + 1) * 2);

	for (int i = 0; i <= (numA + numB); i++) {
		fscanf(fp1, "%d %d", &terms[i].coef, &terms[i].expon);
	}

	padd(sa, fa, sb, fb, &sc, &fc, terms);

	fprintf(fp2, "%d ", fc - sc + 1);

	if (fc - sc == -1)	/* 모든 항이 0인 경우 */
		fprintf(fp2, "%d ", 0);

	for (int i = sc; i <= fc; i++) {
		fprintf(fp2, "%d %d ", terms[i].coef, terms[i].expon);
	}

	fclose(fp1);
	fclose(fp2);
	free(terms);
	return 0;
}

void padd(int startA, int finishA, int startB, int finishB, int* startC, int* finishC, Polynomial* terms) {
	int coefficient;
	*startC = avail;
	while (startA <= finishA && startB <= finishB) {
		if (terms[startA].expon < terms[startB].expon) {	/* a 차수 < b 차수 */
			attach(terms[startA].coef, terms[startA].expon, terms);
			startA++;
		}
		else if (terms[startA].expon > terms[startB].expon) {	/* a 차수 > b 차수 */
			attach(terms[startB].coef, terms[startB].expon, terms);
			startB++;
		}
		else {	/* a 차수 == b 차수 */
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].expon, terms);
			startA++;
			startB++;
		}
	}

	/* 남은 A(x) attach 하기 */
	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].expon, terms);

	/* 남은 B(x) attach 하기 */
	for (; startB <= finishB; startB++)
		attach(terms[startB].coef, terms[startB].expon, terms);

	*finishC = avail - 1;
}

void attach(int coefficient, int exponent, Polynomial* terms) {		/* attach 함수 */
	if (avail >= (numA + numB + 1) * 2) {
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}