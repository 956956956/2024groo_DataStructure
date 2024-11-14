#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int row, int col);

int** make2dArray(int row, int col) {
	int** arr = (int**)malloc(sizeof(int) * row);
	for (int i = 0; i < row; i++) {
		arr[i] = (int*)malloc(sizeof(int) * col);

		for (int j = 0; j < col; j++)
			arr[i][j] = rand() % 100;
	}

	return arr;
}

int main() {
	int** ipp;
	int i, j, rows, cols;

	printf("이차원 배열의 행과 열의 수를 입력하세요: ");
	scanf_s("%d %d", &rows, &cols);

	ipp = make2dArray(rows, cols);
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++)
			printf("ipp[%d][%d] = %2d ", i, j, ipp[i][j]);
		printf("\n");
	}

	return 0;
}