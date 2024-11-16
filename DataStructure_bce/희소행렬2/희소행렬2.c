#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS_SIZE 20
#define MAX_ROW 20
#define MAX_COL 20

typedef struct {
	int item;
	int row;
	int col;
} term;

term sp[MAX_TERMS_SIZE];
term tp[MAX_TERMS_SIZE];

void fastTranspose(term* a, term* b) {
	int i, size, num_col;
	int starting_pos[MAX_TERMS_SIZE] = { 0, };
	int row_term[MAX_TERMS_SIZE] = { 0, };
	size = a[0].item;
	num_col = a[0].col;
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].item = a[0].item;
	
	for (i = 1; i <= size; i++) {
		row_term[a[i].col]++;
	}
	starting_pos[0] = 1;
	for (i = 0; i < num_col; i++) {
		starting_pos[i + 1] = starting_pos[i] + row_term[i];
	}
	for (i = 1; i <= size; i++) {
		int j = starting_pos[a[i].col]++;
		b[j].row = a[i].col;
		b[j].col = a[i].row;
		b[j].item = a[i].item;
	}
}

void transposeMatrix(term *a, term *b) {
	int n, i, j, currentb = 1;
	n = a[0].item;

	//b 정보 초기화
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].item = n;



	for (i = 0; i < a[0].col; i++) {
		for (j = 1; j <= n; j++) {
			if (a[j].col == i) {
				b[currentb].row = a[j].col;
				b[currentb].col = a[j].row;
				b[currentb].item = a[j].item;
				currentb++;
			}
		}
	}


}

void makeArry(char ch[], term *a) {
	int i, j;
	int arry[MAX_ROW][MAX_COL] = { 0, };
	printf("%s\n", ch);
	for (i = 1; i <= a[0].item; i++)
		arry[a[i].row][a[i].col] = a[i].item;

	for (i = 0; i < sp[0].row; i++) {
		for (j = 0; j < sp[0].col; j++)
			printf(" %3d", arry[i][j]);
		printf("\n");
	}
}


int main() {
	FILE* fp1, *fp2;
	int i, j, size;

	fp1 = fopen("input.txt", "r");
	//희소행렬 초기화
	fscanf(fp1, "%d %d %d", &sp[0].row, &sp[0].col, &sp[0].item);
	size = sp[0].item;
	for (i = 1; i <= size; i++) {
		fscanf(fp1, "%d %d %d", &sp[i].row, &sp[i].col, &sp[i].item);
	}
	fclose(fp1);

	//시간복잡도 높음
	//transposeMatrix(sp, tp);
	fastTranspose(sp, tp);
	
	makeArry("A", sp);
	makeArry("B", tp);
	
	//파일에 transpose sparse matrix 출력
	fp2 = fopen("output.txt", "w");
	for (i = 0; i <= size; i++) {
		fprintf(fp2, "%3d%3d%3d\n", tp[i].row, tp[i].col, tp[i].item);
	}
}