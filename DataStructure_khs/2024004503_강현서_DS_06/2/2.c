#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EXIT_ROW 4
#define EXIT_COL 5

typedef struct {
	short int vert;
	short int horiz;
}offsets;

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

int maze[EXIT_COL + 2][EXIT_ROW + 2];
int mark[EXIT_COL + 2][EXIT_ROW + 2] = { 0 };
element stack[(EXIT_COL + 2) * (EXIT_ROW + 2)];
int top = -1;
offsets move[8] = {
	{ -1, 0 },
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
	{ 1, -1 },
	{ 0, -1 },
	{ -1, -1 } };

void path(void);
bool empty();
bool full();
void push(element item);
element pop();

bool empty() {
	return top < 0;
}

bool full() {
	return top >= EXIT_COL * EXIT_ROW - 1;
}

void push(element item) {
	if (top >= EXIT_COL * EXIT_ROW - 1) {
		full();
		return;
	}
	stack[(++top)].col = item.col;
	stack[top].row = item.row;
	stack[top].dir = item.dir;
}

element pop() {
	if (top < 0) {
		empty();
		return;
	}

	return stack[top--];
}

void path(void) {
	int i, row, col, nextRow, nextCol, dir;
	bool found = false;
	element position;

	mark[1][1] = 1; top = 0;
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = 1;

	while (top > -1 && !found) {
		position = pop();

		row = position.row;
		col = position.col;
		dir = position.dir;

		while ((dir < 8) && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			
			if ((nextRow == EXIT_ROW) && (nextCol == EXIT_COL))
				found = true;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path is:\n");
		printf("row   col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else
		printf("THe maze does not have a path\n");
}

int main() {
	FILE* fp;
	fp = fopen("input.txt", "r");
	int m, p;

	fscanf(fp, "%d", &m);
	fscanf(fp, "%d", &p);


	for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < p + 2; j++) {
			if ((i == 0) || (i == m + 1) || (j == 0) || (j == p + 1))
				maze[i][j] = 1;
			else {
				fscanf(fp, "%d ", &maze[i][j]);
			}
		}
	}

	path();
}