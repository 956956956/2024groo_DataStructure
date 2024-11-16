#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* make1dArray(int n) {
	int* p = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		p[i] = rand() % 100;
	return p;
}

int main() {
	int* ipp;
	int i, num;
	printf("일차원 배열의 수를 입력하세요: ");
	scanf("%d", &num);
	ipp = make1dArray(num);
	for (i = 0; i < num; i++) {
		printf("ipp[%2d] =%2d ", i, ipp[i]);
		if ((i % 5) == 4)
			printf("\n");
	}
	return 0;
}