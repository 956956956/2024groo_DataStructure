// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>

/* 이동 방향 자료구조 */
typedef struct {
	short int vert;
	short int horiz;
} offsets;

/* 스택의 자료구조 */
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;

offsets move[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1}};	// 이동 방향(북, 동, 남, 서)
element stack[MAX_STACK_SIZE];	// 방문한 지점을 저장하는 스택

int start_x, start_y, finish_x, finish_y, top = -1, input_row, input_col;

void input_maze(FILE* fp, int** maze, int row, int col);	// 미로를 입력받는 함수
void path(int** maze, int **mark);	// 미로 찾기 함수
void reset(void);	// 다음 미로 찾기를 하기 전, 초기화 함수

/* stack을 다루는 함수 */
int isEmpty();
int isFull();
void push(element item);
element pop();

int main() {
	FILE *fp1, *fp2, *fp3, *fp4;
	int** maze;
	int ** mark;
	int i;

	/* maze1.txt */
	fp1 = fopen("maze1.txt", "r");
	if (!fp1) {
		puts("Cannot open the file.");
		exit(1);
	}

	fscanf(fp1, "%d %d", &input_row, &input_col);

	maze = (int**)malloc(sizeof(int*) * (input_row + 2));	// 동적 할당으로 미로 생성
	for (i = 0; i < (input_row +2); i++)
		maze[i] = (int*)malloc(sizeof(int) * (input_col + 2));

	input_maze(fp1, maze, input_row, input_col);	// 미로 입력

	mark = (int**)calloc((input_row + 2), sizeof(int*));	// 동적 할당으로 과거 방문 여부 행렬 생성
	for (i = 0; i < (input_row +2); i++)
		mark[i] = (int*)calloc((input_col + 2), sizeof(int));

	path(maze, mark);	// 미로 찾기

	for (i = 0; i < (input_row + 2); i++)	// maze 동적 할당 해제
		free(maze[i]);
	free(maze);

	for (i = 0; i < (input_row + 2); i++)	// mark 동적 할당 해제
		free(mark[i]);
	free(mark);

	fclose(fp1);

	reset();	// 초기화

	/* maze2.txt */
	fp2 = fopen("maze2.txt", "r");
	if (!fp1) {
		puts("Cannot open the file.");
		exit(1);
	}

	fscanf(fp2, "%d %d", &input_row, &input_col);

	maze = (int**)malloc(sizeof(int*) * (input_row + 2));	// 동적 할당으로 미로 생성
	for (i = 0; i < (input_row + 2); i++)
		maze[i] = (int*)malloc(sizeof(int) * (input_col + 2));

	input_maze(fp2, maze, input_row, input_col);	// 미로 입력

	mark = (int**)calloc((input_row + 2), sizeof(int*));	// 동적 할당으로 과거 방문 여부 행렬 생성
	for (i = 0; i < (input_row + 2); i++)
		mark[i] = (int*)calloc((input_col + 2), sizeof(int));

	path(maze, mark);	// 미로 찾기

	for (i = 0; i < (input_row + 2); i++)	// maze 동적 할당 해제
		free(maze[i]);
	free(maze);

	for (i = 0; i < (input_row + 2); i++)	// mark 동적 할당 해제
		free(mark[i]);
	free(mark);

	fclose(fp2);

	reset();

	/* maze3.txt */
	fp3 = fopen("maze3.txt", "r");
	if (!fp1) {
		puts("Cannot open the file.");
		exit(1);
	}

	fscanf(fp3, "%d %d", &input_row, &input_col);

	maze = (int**)malloc(sizeof(int*) * (input_row + 2));	// 동적 할당으로 미로 생성
	for (i = 0; i < (input_row + 2); i++)
		maze[i] = (int*)malloc(sizeof(int) * (input_col + 2));

	input_maze(fp3, maze, input_row, input_col);	// 미로 입력

	mark = (int**)calloc((input_row + 2), sizeof(int*));	// 동적 할당으로 과거 방문 여부 행렬 생성
	for (i = 0; i < (input_row + 2); i++)
		mark[i] = (int*)calloc((input_col + 2), sizeof(int));

	path(maze, mark);	// 미로 찾기

	for (i = 0; i < (input_row + 2); i++)	// maze 동적 할당 해제
		free(maze[i]);
	free(maze);

	for (i = 0; i < (input_row + 2); i++)	// mark 동적 할당 해제
		free(mark[i]);
	free(mark);

	fclose(fp3);

	reset();

	/* maze4.txt */
	fp4 = fopen("maze4.txt", "r");
	if (!fp1) {
		puts("Cannot open the file.");
		exit(1);
	}

	fscanf(fp4, "%d %d", &input_row, &input_col);	// 동적 할당으로 미로 생성

	maze = (int**)malloc(sizeof(int*) * (input_row + 2));
	for (i = 0; i < (input_row + 2); i++)
		maze[i] = (int*)malloc(sizeof(int) * (input_col + 2));

	input_maze(fp4, maze, input_row, input_col);	// 미로 입력

	mark = (int**)calloc((input_row + 2), sizeof(int*));	// 동적 할당으로 과거 방문 여부 행렬 생성
	for (i = 0; i < (input_row + 2); i++)
		mark[i] = (int*)calloc((input_col + 2), sizeof(int));

	path(maze, mark);	// 미로 찾기

	for (i = 0; i < (input_row + 2); i++)	// maze 동적 할당 해제
		free(maze[i]);
	free(maze);

	for (i = 0; i < (input_row + 2); i++)	// mark 동적 할당 해제
		free(mark[i]);
	free(mark);

	fclose(fp4);

	return 0;
}

/* 미로를 입력받는 함수 */
void input_maze(FILE* fp, int** maze, int row, int col) {
	for (int i = 0; i <= (row+1); i++) {
		for (int j = 0; j <= (col+1); j++) {
			if (i == 0 || i == (row + 1) || j == 0 || j == (col + 1))	//미로의 boundary는 1로 둘러싸기
				maze[i][j] = 1;
			else
				fscanf(fp, "%d", &maze[i][j]);
		}
	}

	fscanf(fp, "%d %d %d %d", &start_x, &start_y, &finish_x, &finish_y);
	// boundary를 1로 둘러쌌기 때문에 시작, 종료 위치의 x, y 좌표 모두 +1씩
	start_x++;
	start_y++;
	finish_x++;
	finish_y++;
}

/* 미로 찾기 함수 */
void path(int **maze, int ** mark) {
	int i, j, count, row, col, next_row, next_col, dir, found = 0;
	element position;

	// 시작위치 세팅
	mark[start_x][start_y] = 1;
	top = 0;
	stack[0].row = start_x; stack[0].col = start_y, stack[0].dir = 0;

	// 미로 찾기
	while (top > -1 && !found) {
		position = pop();
		row = position.row;
		col = position.col;
		dir = position.dir;

		while (dir < 4 && !found) {
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == finish_x && next_col == finish_y)
				found = 1;
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
				mark[next_row][next_col] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);

				row = next_row;
				col = next_col;
				dir = 0;
			}
			else
				++dir;
		}
	}

	if (found) {	// 경로를 찾았을 때 출력
		printf("MAZE\n");
		for (i = 1; i <= input_row; i++) {
			for (j = 1; j <= input_col; j++) {
				printf("  %d", maze[i][j]);
			}
			printf("\n");
		}

		printf("The path is: \n");
		count = 0;
		for (i = 1; i <= input_row; i++) {
			for (j = 1; j <= input_col; j++) {
				if (i == start_x && j == start_y) {	// start 좌표
					printf("  S");
					continue;
				}
				else if (i == finish_x && j == finish_y) {	// finish 좌표
					printf("  F");
					continue;
				}
				else if (maze[i][j] == 1) {	// 막힌 곳
					printf("  %d", 1);
					continue;
				}
				else if (i == row && j == col) {	// 찾은 경로 중 현재 위치
					printf("  X");
					continue;
				}

				for (count = 0; count <= top; count++) {	// 찾은 경로
					if (i == stack[count].row && j == stack[count].col) {
						printf("  X");
						break;
					}
				}
				if (i == stack[count].row && j == stack[count].col)
					continue;

				// 경로가 아닌 부분
				printf("  %d", 0);
			}
			printf("\n");
		}
		printf("\n");
	}
	else {	// 경로를 찾지 못했을 때 출력
		printf("MAZE\n");
		for (i = 1; i <= input_row; i++) {
			for (j = 1; j <= input_col; j++) {
				printf("  %d", maze[i][j]);
			}
			printf("\n");
		}

		printf("No path!\n");
		count = 0;
		for (i = 1; i <= input_row; i++) {
			for (j = 1; j <= input_col; j++) {
				if (i == start_x && j == start_y) {	// start 좌표
					printf("  S");
					continue;
				}
				else if (i == finish_x && j == finish_y) {	// finish 좌표
					printf("  F");
					continue;
				}
				else if (maze[i][j] == 1) {	// 막힌 곳
					printf("  %d", 1);
					continue;
				}
				else // 경로가 아닌 부분
					printf("  %d", 0);
			}
			printf("\n");
		}
		printf("\n");
	}
}

/* 다음 미로 찾기를 하기 전, 초기화 함수 */
void reset(void) {
	while (1) {
		if (pop(stack).row == -1);
			break;
	}
}

/* stack 처리 함수들 */
int isEmpty() {		// stack이 비었는가?
	if (top == -1) {
		printf("Error : Stack is empty!\n");
		return 0;	// 비어있을 때 0 반환
	}
	return 1;
}

int isFull() {		// stack이 꽉 찼는가?
	if (top == MAX_STACK_SIZE - 1)
		return 0;	// 꽉 찼을 때 0 반환
	return 1;
}

void push(element item) {	// stack에 값 집어넣기
	if (isFull() == 0) {
		printf("Stack is full.");
		return;
	}
	stack[++top] = item;
}

element pop() {		// stack에서 값 빼오기
	if (isEmpty() == 0) {
		element error = { -1, -1, -1 };
		printf("Stack is empty.");
		return error;
	}
	return stack[top--];
}