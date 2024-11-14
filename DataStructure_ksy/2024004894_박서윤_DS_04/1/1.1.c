#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERMS 101
typedef struct {
    int col;
    int row;
    int value;
} term;

term a[MAX_TERMS];
int ary[20][20] = { 0, };

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  // SWAP 매크로

// 함수 선언
void makematrix(int n);
void sortmatrix(int n);
void printarray(int ary[][20]);

int main()
{
    int num;

    printf("희소 행렬에 포함될 원소의 개수를 입력하세요: ");
    scanf_s("%d", &num);

    // 랜덤 행렬을 만들고 희소 행렬로 변환
    makematrix(num);
    // 희소 행렬을 행, 열 기준으로 정렬
    sortmatrix(num);

    // 생성된 랜덤 행렬 출력
    printf("생성된 20x20 행렬\n");
    printarray(ary);

    // 희소 행렬 출력
    printf("희소 행렬 출력\n");
    for (int i = 0; i <= num; i++)
        printf("행: %5d, 열: %5d, 값: %5d\n", a[i].row, a[i].col, a[i].value);

    return 0;
}

// 랜덤으로 20x20 행렬을 만들고, 이를 희소 행렬로 변환하는 함수
void makematrix(int n)
{
    int row, col, val;

    // 희소 행렬의 첫 번째 원소는 행렬의 크기 정보
    a[0].col = 20;
    a[0].row = 20;
    a[0].value = n;

    // 랜덤 시드 설정
    long seconds = (long)time(NULL);
    srand(seconds);

    // n개의 랜덤 원소를 행렬에 추가
    for (int i = 1; i <= n; i++) {
        row = rand() % 20;  // 0~19 범위의 랜덤 행
        col = rand() % 20;  // 0~19 범위의 랜덤 열
        val = rand() % 99 + 1;  // 1~99 범위의 랜덤 값

        // ary 배열에 값 저장
        ary[row][col] = val;

        // 희소 행렬에 값 저장
        a[i].row = row;
        a[i].col = col;
        a[i].value = val;
    }
}

// 희소 행렬을 행과 열 순으로 정렬하는 함수
void sortmatrix(int n)
{
    int i, j, min, temp;

    // 선택 정렬을 사용하여 정렬
    for (i = 1; i <= n; i++) {
        min = i;
        for (j = i + 1; j <= n; j++) {
            // 행 기준으로 정렬, 행이 같으면 열 기준으로 정렬
            if (a[j].row < a[min].row)
                min = j;
            else if (a[j].row == a[min].row)
                if (a[j].col < a[min].col)
                    min = j;
        }
        // SWAP 매크로를 사용하여 두 항의 값을 바꿈
        SWAP(a[i].col, a[min].col, temp);
        SWAP(a[i].row, a[min].row, temp);
        SWAP(a[i].value, a[min].value, temp);
    }
}

// 20x20 행렬을 출력하는 함수
void printarray(int ary[][20])
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%5d", ary[i][j]);  // 각 원소를 5칸으로 출력
        }
        printf("\n");  // 한 행 출력 후 개행
    }
}
