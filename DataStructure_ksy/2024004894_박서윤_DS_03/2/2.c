/* 2.입력 받은 이차원 배열의 행의 수와 열의 수를 함수 make2dArray()에 전달하면, 함수
make2dArray()는 전달 받은 원소 갯수 만큼 동적으로 메모리를 할당 받아 램덤으로 100보다
적은 값으로 메모리를 초기화 시킨 후, 주소값을 반환한다. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** make2dArray(int rows, int cols) {
    int** arr = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        arr[i] = (int*)malloc(sizeof(int) * cols);
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % 100;
        }
    }
    return arr;
}

int main() {
    int** ipp;
    int i, j, rows, cols;
    printf("이차원 배열의 행과 열의 수를 입력하세요: ");
    scanf_s("%d %d", &rows, &cols);

    // 2차원 배열 생성
    ipp = make2dArray(rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("ipp[%d][%d] = %d ", i, j, ipp[i][j]);
        }
        printf("\n");
    }
    return 0; // break point 설정
}