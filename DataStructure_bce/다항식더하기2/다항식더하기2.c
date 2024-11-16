#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 20

typedef struct polynomial {
	float coef;
	int expon;
} term;
term terms[MAX_TERMS];

void poly_print(char ch[], int Spos, int Epos);
void padd(int a_Spos, int a_Epos, int b_Spos, int b_Epos);
void attatch(float coef, int expon);

int main() {
	int a_Num, b_Num, i, d_Spos, d_Epos;
	printf("A Num : ");
	scanf("%d", &a_Num);
	printf("B Num : ");
	scanf("%d", &b_Num);

	for (i = 0; i < a_Num; i++)
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	for (i = a_Num; i < a_Num + b_Num; i++)
		scanf("%f %d", &terms[i].coef, &terms[i].expon);

	padd(0, a_Num - 1, a_Num, i - 1, &d_Spos, &d_Epos);

	poly_print("A(x)", 0, a_Num - 1);
	poly_print("B(x)", a_Num, i - 1);
	poly_print("D(x)", d_Spos, d_Epos - 1);



}

void attach(int idx, float coef, int expon) {
	terms[idx].coef = coef;
	terms[idx].expon = expon;
}

void padd(int a_Spos, int a_Epos, int b_Spos, int b_Epos, int* d_Spos, int* d_Epos) {
	*d_Spos = *d_Epos = b_Epos + 1;
	while (a_Spos <= a_Epos && b_Spos <= b_Epos) {
		if (terms[a_Spos].expon > terms[b_Spos].expon) {
			attach((*d_Epos)++, terms[a_Spos].coef, terms[a_Spos].expon);
			a_Spos++;
		}
		else if (terms[a_Spos].expon == terms[b_Spos].expon) {
			attach((*d_Epos)++, terms[b_Spos].coef + terms[a_Spos].coef, terms[a_Spos].expon);
			a_Spos++; b_Spos++;
		}
		else {
			attach((*d_Epos)++, terms[b_Spos].coef, terms[b_Spos].expon);
			b_Spos++;
		}
	}
	for(;a_Spos<=a_Epos;a_Spos++)
		attach((*d_Epos)++, terms[a_Spos].coef, terms[a_Spos].expon);
	for (;b_Spos<= b_Epos;b_Spos++)
		attach((*d_Epos)++, terms[b_Spos].coef, terms[b_Spos].expon);

}

void poly_print(char ch[], int Spos, int Epos) {
	printf("%s = ", ch);
	int i;
	for (i = Spos; i < Epos; i++) {
		if (terms[i].coef)
			printf("%.0fx^%d + ", terms[i].coef, terms[i].expon);
	}
	if (terms[i].coef && terms[i].expon)
		printf("%.0fx^%d\n", terms[i].coef, terms[i].expon);
	else if (terms[i].coef)
		printf("%.0f\n", terms[i].coef);
}

//튜터 답은 terms의 인덱스를 avail로 표현함
//attach 함수에서 avail이 MAX_TERMS를 넘어가면 뱉어내기
//avail 전역변수로 선언하면 더 간편

/*
	startA=0;
	finishA = m-1;
	startB = finishA+1;
	finishB = startB+n-1;
	avail = finishB + 1;
	*/


