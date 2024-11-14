#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int col;
	int row;
	int value;
}term;

int main() {
	int n, col = 0, row = 0;

	int a[20][20] = { 0 };

	printf("원소의 개수를 쓰시오: ");
	scanf_s("%d", &n);

	printf("random generated Matrix(20,20)\n");
	
	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		col = rand() % 20;
		row = rand() % 20;
		a[col][row] = rand() % 100 + 1;
	}

	for(int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
			printf("%4d", a[i][j]);
		printf("\n");
	}

	term sps[20];

	sps[0].col = 20;
	sps[0].row = 20;
	sps[0].value = n;

	int idx = 1;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++) {
			
			if (a[i][j] != 0) {
				sps[idx].col = i;
				sps[idx].row = j;
				sps[idx].value = a[i][j];
				idx++;
			}
		}

	printf("sparce matrix\n");

	for (int i = 0; i < n + 1; i++)
		printf("%4d %4d %4d\n", sps[i].col, sps[i].row, sps[i].value);
}