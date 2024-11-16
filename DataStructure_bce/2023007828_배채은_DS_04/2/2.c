#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 101
#define MAX_ROW 50
#define MAX_COL 50


typedef struct {
	int row;
	int col;
	int value;
} term;
term a[MAX_TERM], b[MAX_TERM];

void printMatrix(term m[]) {
	int mArr[MAX_ROW][MAX_COL] = { 0 };
	int i, j;
	for (i = 1; i <= m[0].value; i++) {
		mArr[m[i].row][m[i].col] = m[i].value;
	}
	for (i = 0; i < m[0].row; i++) {
		for (j = 0; j < m[0].col; j++) {
			printf("%5d", mArr[i][j]);
		}
		printf("\n");
	}

}

void fastTranspose(term a[], term b[]) {
	int j, numTerms = a[0].value, numCols = a[0].col;
	int rowTerms[MAX_COL], startingPos[MAX_COL], i;
	b[0].row = numCols; b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0) {
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
	}
	for (i = 1; i <= numTerms; i++)
		rowTerms[a[i].col]++;
	
	startingPos[0] = 1;

	for (i = 1; i < numCols; i++) {
		startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		printf("%d\n", startingPos[i]);
	}
	printf("\n");

	for (i = 1; i <= numTerms; i++) {
		j = startingPos[a[i].col]++;
		printf("%d %d\n", a[i].col, j);
		b[j].row = a[i].col;
		b[j].col = a[i].row;
		b[j].value = a[i].value;
	}
}

int main() {
	FILE* fp1 = fopen("a.txt", "r");
	FILE* fp2 = fopen("b.txt", "w");


	int i, j, idx = 0;
	fscanf(fp1, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
	for (i = 1; i <= a[0].value; i++) {
		fscanf(fp1, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
	}
	fclose(fp1);
	fastTranspose(a, b);
	for (i = 0; i <= b[0].value; i++) {
		printf("%3d %3d %3d\n", b[i].row, b[i].col, b[i].value);
	}

	fclose(fp2);
	printf("A\n");
	printMatrix(a);
	printf("B\n");
	printMatrix(b);
}