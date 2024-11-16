#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int r, int c) {
	int** p = (int**)malloc(r * sizeof(int*));
	for (int i = 0; i < r; i++) {
		p[i] = (int*)malloc(c * sizeof(int));
		for (int j = 0; j < c; j++) {
			p[i][j] = rand() % 100;
		}
	}
	return p;
}

int main() {
	int** ipp;
	int i, j, rows, cols;
	printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
	scanf("%d %d", &rows, &cols);
	ipp = make2dArray(rows, cols);
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++)
			printf("ipp[%d][%d] =%d ", i, j, ipp[i][j]);
		printf("\n");
	}
	return 0;
}