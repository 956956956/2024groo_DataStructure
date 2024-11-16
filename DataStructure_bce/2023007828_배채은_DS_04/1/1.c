#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TERM 20

typedef struct{
	int row;
	int col;
	int value;
} term;

int main() {
	int n, i, j, idx = 1;
	int arr[20][20] = { 0, };
	term a[MAX_TERM];
	srand((unsigned)time(NULL));
	printf("원소의 개수를 쓰시오 .. ");
	scanf("%d", &a[0].value);
	n = a[0].value;
	a[0].row = a[0].col = 20;
	for (i = 0; i < a[0].value; i++) {
		arr[rand() % 20][rand() % 20] = 1 + rand() % 100;
	}

	printf("Random generated Matrix(20, 20)\n");
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			printf("%5d", arr[i][j]);
			if (arr[i][j] != 0) {
				a[idx].row = i;
				a[idx].col = j;
				a[idx].value = arr[i][j];
				idx++;
			}
		}
		printf("\n");
	}

	printf("sparce matrix\n");
	for (int i = 0; i <= n; i++) {
		printf("%3d %3d %3d\n", a[i].row, a[i].col, a[i].value);
	}
}