#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct {
	int row;
	int col;
	int dir;
}element;

element stack[MAX_SIZE];
int top = 0;

typedef struct {
	int vert;
	int horiz;
} offsets;

offsets move[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
int** ary;

void push(int row, int col, int dir) {
	stack[++top].row = row;
	stack[top].col = col;
	stack[top].dir = dir;
}

element pop() {
	return stack[top--];
}


void findP(int Outrow, int OutCol) {
	int nextRow, nextCol, row =1, col =1, find = 0, dir=0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (!find) {
		element tmp = pop();
		row = tmp.row; col = tmp.col; dir = tmp.dir;

		while (dir <= 8&&!find) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == Outrow && nextCol == OutCol) {
				find = 1;
			}

			if (!ary[nextRow][nextCol]) {
				ary[nextRow][nextCol] = 1;
				push(row, col, ++dir);
				row = nextRow; col = nextCol;
				dir = 1;
			}
			else
				dir++;

		}
	}
	if (find) {
		printf("row    col\n");
		for (int i = 0; i <= top; i++)
			printf("%d    %d\n", stack[i].row, stack[i].col);
		printf("%d    %d\n", Outrow, OutCol);
	}

}

int main() {
	int row, col, i, j;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &row, &col);

	ary = (int**)malloc((row+2) * sizeof(int*));
	for (i = 0; i <= row + 1; i++) {
		ary[i] = (int*)malloc((col+2) * sizeof(int));
		for (j = 0; j <= col + 1; j++)
			ary[i][j] = 0;
	}

	for (i = 0; i <= row + 1; i++) {
		ary[i][0] = 1;
		ary[i][col + 1] = 1;
	}
	for (j = 0; j <= col + 1; j++) {
		ary[0][j] = 1;
		ary[row + 1][j] = 1;
	}


	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			fscanf(fp, "%d", &ary[i][j]);

	findP(row, col);
}