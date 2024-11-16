#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX_ROW 20
#define MAX_COL 20
#define MAX_TERMS_SIZE 20


typedef struct {
	int item;
	int row;
	int col;
} term;

term sp[MAX_TERMS_SIZE];
int avail = 0;

void add_item(int row, int col, int n) {
	sp[avail].item = n;
	sp[avail].row = row;
	sp[avail].col = col;
	avail++;
}

int main() {
	int i, j, n, item, row, col;
	int arry[MAX_ROW][MAX_COL] = { 0, };
	srand(time(NULL));
	printf("원소 개수 : ");
	scanf("%d", &n);
	add_item(MAX_ROW, MAX_COL, n);

	

	for (i = 0; i < n; i++) {
		item = rand() % 100;
		row = rand() % 20; col = rand() % 20;
		
		//이미 값이 들어가있을 때 예외처리!!
		//rand 쓸 때 항상 주의

		if (arry[row][col])
			i--;
		else
			arry[row][col] = item;
	}
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			if(arry[i][j])
				add_item(i, j, arry[i][j]);
			printf(" %3d", arry[i][j]);
		}
		printf("\n");
	}
	printf("sparce matrix\n");
	for (i = 0; i <= n; i++)
		printf("%3d %3d %3d\n", sp[i].row, sp[i].col, sp[i].item);

}

//튜터 희소행렬 print 함수

/*
void printMatrix(term matrix[])
{
	int row, col, i, j, element, p;
	row = matrix[0].row;
	col = matrix[0].col;

	element = 0;
	p = 1;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (i == matrix[p].row && j == matrix[p].col)
				element = matrix[p++].value;
			else
				element = 0;
			printf("%4d", element);
		}
		printf("\n");
	}
	getchar();
}
*/