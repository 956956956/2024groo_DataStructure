/*4. 다항식을 아래와 같이 표현 하는 방식을 이용하여, 두 다항식을 입력받아 더한 후 그 결과
를 출력하는 프로그램을 작성하라.
 [프로그램설명]
① 각 다항식을 사용자로부터 키보드 입력을 받음
② 다항식을 출력하는 함수를 정의
하여 사용하기
void poly_print(char ch[], polynomial a);*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
} polynomial;

void poly_print(char c, polynomial p) {
	printf("%c(X) = ", c);
	for (int i = 0; i < p.degree; i++) {
		printf("%dx^%d + ", p.coef[i], p.degree - i);
	}
	printf("%2d\n", p.coef[p.degree]);
}

int main() {
	polynomial A, B, C;
	int ia = 0, ib = 0, ic = 0;
	int da, db;

	printf("<< C(X) = A(X) + B(X) >>\n");

	printf("Input the degree of items of A(X) : ");
	scanf_s("%d", &A.degree);
	printf("Input the coefficients A(X) : ");
	for (int i = 0; i < A.degree + 1; i++)
		scanf_s("%d", &A.coef[i]);

	printf("Input the degree of items of B(X) : ");
	scanf_s("%d", &B.degree);
	printf("Input the coefficients B(X) : ");
	for (int i = 0; i < B.degree + 1; i++)
		scanf_s("%d", &B.coef[i]);

	if (A.degree > B.degree)
		C.degree = A.degree;
	else C.degree = B.degree;
	da = A.degree;
	db = B.degree;

	while (ia <= A.degree && ib <= B.degree) {
		if (da < db) {
			// B의 차수가 더 크면 B의 계수를 C로 복사
			C.coef[ic++] = B.coef[ib++];
			db--;
		}
		else if (da == db) {
			// A와 B의 차수가 같으면 두 계수를 더해 C로 복사
			C.coef[ic++] = A.coef[ia++] + B.coef[ib++];
			da--;
			db--;
		}
		else {
			// A의 차수가 더 크면 A의 계수를 C로 복사
			C.coef[ic++] = A.coef[ia++];
			da--;
		}
	}

	poly_print('A', A);
	poly_print('B', B);
	poly_print('C', C);

	return 0;
}
