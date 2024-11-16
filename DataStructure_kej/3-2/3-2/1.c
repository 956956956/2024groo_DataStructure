// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int col;
	int row;
	int value;
} term;

int main() {
	FILE* fp = fopen("m1.txt", "r");
	term* a, *b;
	int* rowTerms, * startingPos;
	int i, j, numRows, numCols, numTerms, index;
	if (!fp) {
		puts("Cannt open the file");
		exit(1);
	}

	/* 희소행렬 a, b 동적할당으로 생성 */
	fscanf(fp, "%d %d %d", &numRows, &numCols, &numTerms);
	a = (term*)malloc((numTerms + 1) * sizeof(term));
	b = (term*)malloc((numTerms + 1) * sizeof(term));

	a[0].row = numRows;		a[0].col = numCols;		a[0].value = numTerms;
	b[0].row = numCols;		b[0].col = numRows;		b[0].value = numTerms;

	/* 희소행렬 a 파일 입력 */
	for (i = 1; i <= numTerms; i++) {
		fscanf(fp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
	}

	/* rowTerms, startingPos 동적할당으로 생성 */
	rowTerms = (int*)calloc(a[0].col, sizeof(int));	// calloc을 이용하여 0으로 바로 초기화
	startingPos = (int*)calloc(a[0].col, sizeof(int));

	if (numTerms > 0) {
		/* rowTerms 정하기 */
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		
		/* startingPos 정하기 */
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		/* 희소행렬 b 채우기 */
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}

	/* 희소행렬 a 표준 출력 */
	index = 1;
	printf("Before Transposing\n");
	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			if (i == a[index].row && j == a[index].col) {
				printf("%d ", a[index].value);
				index++;
			}
			else
				printf("%d ", 0);
		}
		printf("\n");
	}

	/* 희소행렬 b 표준 출력 */
	index = 1;
	printf("\nAfter Transposing\n");
	for (i = 0; i < numCols; i++) {
		for (j = 0; j < numRows; j++) {
			if (i == b[index].row && j == b[index].col) {
				printf("%d ", b[index].value);
				index++;
			}
			else
				printf("%d ", 0);
		}
		printf("\n");
	}

	/* 동적할당 해제 */
	fclose(fp);
	free(a);
	free(b);
	free(rowTerms);
	free(startingPos);
	return 0;
}