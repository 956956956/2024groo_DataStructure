#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 40

typedef struct {
	short int vert;
	short int horiz;
}offsets;
offsets move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };


typedef struct {
	int row;
	int col;
	int dir;
}element;
element stack[MAX_STACK_SIZE];
top = 0;

int** maze, **mark;

void push(element tmp) {
	stack[++top] = tmp;
}

element pop() {
	return stack[top--];
}

void path(int exitRow, int exitCol) {
	int nextRow, nextCol, found = 0, dir, row, col;
	element position;
	stack[0].row = stack[0].col = stack[0].dir = 1;
	mark[1][1] = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == exitRow && nextCol == exitCol) {
				found = 1;
			}
			else if (maze[nextRow][nextCol] == 0 && mark[nextRow][nextCol] == 0) {
				position.row = row; position.col = col; position.dir = ++dir;
				push(position);
				mark[nextRow][nextCol] = 1;
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path is:\nrow  col\n");
		for (int i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", exitRow, exitCol);
	}
	else printf("The maze does not have a path\n");
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	int row, col, i, j;

	//초기화
	fscanf(fp, "%d %d", &row, &col);
	maze = (int**)malloc((row+2) * sizeof(int*));	
	mark = (int**)calloc((row + 2), sizeof(int*));

	for (i = 0; i < row + 2; i++) {
		maze[i] = (int*)malloc((col + 2) * sizeof(int));
		mark[i] = (int*)calloc((col + 2), sizeof(int));
	}

	for (i = 0; i < col + 2; i++) {
		maze[0][i] = 1;
		maze[row + 1][i] = 1;
	}
	for (i = 0; i < row + 2; i++) {
		maze[i][0] = 1;
		maze[i][col + 1] = 1;
	}

	for (i = 1; i <= row; i++) 
		for (j = 1; j <= col; j++) 
			fscanf(fp, "%d", &maze[i][j]);

	//초기화 끝

	path(row, col);

	
}