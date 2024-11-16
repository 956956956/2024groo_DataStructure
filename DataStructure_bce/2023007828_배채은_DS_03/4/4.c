#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101
#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0: 1 ) 

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

void poly_print(char ch[], polynomial a) {
	printf("%s = ", ch);
	for (int i = 0; i < a.degree; i++) {
		printf("%.0fx^%d + ", a.coef[i], a.degree - i);
	}
	printf("%.0f\n", a.coef[a.degree]);
}

polynomial add_poly(polynomial A, polynomial B) {
	polynomial C;
	int a_deg = A.degree, b_deg = B.degree;
	int a_idx = 0, b_idx = 0, c_idx = 0;
	C.degree = (a_deg > b_deg) ? a_deg : b_deg;
	while (a_deg >= 0 && b_deg >= 0) {
		switch COMPARE(a_deg, b_deg) {
		case -1:
			C.coef[c_idx++] = B.coef[b_idx++];
			b_deg--;
			break;
		case 0:
			C.coef[c_idx++] = A.coef[a_idx++] + B.coef[b_idx++];
			a_deg--;
			b_deg--;
			break;
		case 1:
			C.coef[c_idx++] = A.coef[a_idx++];
			a_deg--;
			break;
		}
	}
	for (; a_deg >= 0; a_deg--) {
		C.coef[c_idx++] = A.coef[a_idx++];
		a_deg--;
	}
	for (; b_deg >= 0; b_deg--) {
		C.coef[c_idx++] = B.coef[b_idx++];
		b_deg--;
	}
	return C;

}

int main() {
	polynomial A, B, C;
	int i;
	printf("<< C(x) = A(x) + B(x) >>\n");
	printf("Input the degree of items of A(x) : ");
	scanf("%d", &A.degree);
	printf("Input the coefficients A(x) : ");
	for (i = 0; i < A.degree + 1; i++)
		scanf("%f", &A.coef[i]);

	printf("Input the degree of items of B(x) : ");
	scanf("%d", &B.degree);
	printf("Input the coefficients B(x) : ");
	for (i = 0; i < B.degree + 1; i++)
		scanf("%f", &B.coef[i]);

	C = add_poly(A, B);
	poly_print("A(x)", A);
	poly_print("B(x)", B);
	poly_print("C(x)", C);

}