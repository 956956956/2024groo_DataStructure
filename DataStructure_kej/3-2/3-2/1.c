// 2023012565 ������
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

	/* ������ a, b �����Ҵ����� ���� */
	fscanf(fp, "%d %d %d", &numRows, &numCols, &numTerms);
	a = (term*)malloc((numTerms + 1) * sizeof(term));
	b = (term*)malloc((numTerms + 1) * sizeof(term));

	a[0].row = numRows;		a[0].col = numCols;		a[0].value = numTerms;
	b[0].row = numCols;		b[0].col = numRows;		b[0].value = numTerms;

	/* ������ a ���� �Է� */
	for (i = 1; i <= numTerms; i++) {
		fscanf(fp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
	}

	/* rowTerms, startingPos �����Ҵ����� ���� */
	rowTerms = (int*)calloc(a[0].col, sizeof(int));	// calloc�� �̿��Ͽ� 0���� �ٷ� �ʱ�ȭ
	startingPos = (int*)calloc(a[0].col, sizeof(int));

	if (numTerms > 0) {
		/* rowTerms ���ϱ� */
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		
		/* startingPos ���ϱ� */
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		/* ������ b ä��� */
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}

	/* ������ a ǥ�� ��� */
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

	/* ������ b ǥ�� ��� */
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

	/* �����Ҵ� ���� */
	fclose(fp);
	free(a);
	free(b);
	free(rowTerms);
	free(startingPos);
	return 0;
}