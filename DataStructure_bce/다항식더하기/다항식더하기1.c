#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101

typedef struct polynomial {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

void poly_print(char ch[], polynomial a);
polynomial addPoly(polynomial a, polynomial b);
int compare(int a, int b);
polynomial poly_add1(polynomial A, polynomial B);


int main() {
	polynomial a, b, c;
	printf("A degree : ");
	scanf("%d", &a.degree);
	for (int i = 0; i <= a.degree; i++)
		scanf("%f", &a.coef[i]);

	printf("B degree : ");
	scanf("%d", &b.degree);
	for (int i = 0; i <= b.degree; i++)
		scanf("%f", &b.coef[i]);

	poly_print("A(x)", a);
	poly_print("B(x)", b);

	c = poly_add1(a, b);
	//c = addPoly(a, b);
	poly_print("C(x)", c);
	
}

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}

void poly_print(char ch[], polynomial a) {
	int i;
	printf("%s = ", ch);
	for (i = 0; i < a.degree; i++)
		printf("%.0fx^%d + ", a.coef[i], a.degree - i);
	printf("%.0f\n", a.coef[i]);

}

polynomial addPoly(polynomial a, polynomial b) {
	polynomial c;
	int aDeg = a.degree, bDeg = b.degree, aIdx = 0, bIdx = 0, cIdx = 0;
	while (aDeg >= 0 && bDeg >= 0) {
		switch (compare(aDeg, bDeg))
		{
		case 1:
			c.coef[cIdx++] = a.coef[aIdx++];
			aDeg--;
			break;
		case 0:
			c.coef[cIdx++] = a.coef[aIdx++] + b.coef[bIdx++];
			aDeg--; bDeg--;
			break;
		case -1:
			c.coef[cIdx++] = b.coef[bIdx++];
			bDeg--;
			break;
		}
	}
	/*for (; aDeg >= aIdx;) {
		c.coef[cIdx++] = a.coef[aIdx++];
	}
	for (; bDeg >= bIdx;) {
		c.coef[cIdx++] = b.coef[bIdx++];
	}
	*/ //필요없음
	c.degree = cIdx - 1;
	return c;
}

//튜터답
polynomial poly_add1(polynomial A, polynomial B)  // C=A+B
{
	polynomial C;				// 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0;	// 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	//C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}

	C.degree = Cpos - 1;
	return C;
}