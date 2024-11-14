#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_ROW 10
#define MAX_COL 10

// 8방향: 북, 북동, 동, 남동, 남, 남서, 서, 북서
int move[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
int maze[MAX_ROW][MAX_COL];
int visited[MAX_ROW][MAX_COL];
int row, col;

typedef struct {
    int x, y;
} Point;

// 출구 (4, 5)
Point exit_point = { 3, 4 };

// 경로 저장을 위한 배열
Point path[MAX_ROW * MAX_COL];
int pathIndex = 0;

// 미로 출력 함수
void printMaze() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

// 경로 출력 함수
void printPath() {
    for (int i = 0; i < pathIndex; i++) {
        printf("%d  %d\n", path[i].x + 1, path[i].y + 1);
    }
    printf("The exit is found. Finish the program.\n");
}

// 미로 탐색 함수 (경로 백트래킹 제거)
int findPath(int x, int y) {
    // 현재 위치가 출구인 경우
    if (x == exit_point.x && y == exit_point.y) {
        path[pathIndex++] = (Point){ x, y };  // 출구 좌표 저장
        printPath();  // 경로 출력
        return 1;
    }

    // 방문한 곳은 2로 표시
    visited[x][y] = 1;
    path[pathIndex++] = (Point){ x, y };  // 현재 좌표 저장

    // 시계방향으로 이동 가능 여부 확인
    for (int i = 0; i < 8; i++) {
        int newX = x + move[i][0];
        int newY = y + move[i][1];

        // 미로 내부이고, 이동할 수 있는 길이며, 방문하지 않았을 때만 이동
        if (newX >= 0 && newX < row && newY >= 0 && newY < col && maze[newX][newY] == 0 && !visited[newX][newY]) {
            if (findPath(newX, newY)) {
                return 1;  // 출구에 도달하면 즉시 종료
            }
        }
    }

    // 이동할 수 없는 경우 경로에서 제거 (백트래킹)
    pathIndex--;
    return 0;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File error. Cannot open the file.\n");
        return 1;
    }

    fscanf(file, "%d %d", &row, &col);  // 미로의 행과 열 크기 입력
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fscanf(file, "%d", &maze[i][j]);  // 미로 정보 입력
        }
    }
    fclose(file);

    printf("The path is :\nrow col\n");
    if (!findPath(0, 0)) {  // (1,1)에서 탐색 시작
        printf("There is no way to the path.\n");
    }

    return 0;
}
