#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERMS 101  // 행렬의 최대 원소 개수 정의 (최대 100개 원소를 저장)
typedef struct term {
    int col;    // 열 정보
    int row;    // 행 정보
    int value;  // 원소 값
} term;

term a[MAX_TERMS];  // 희소 행렬의 원소 정보를 저장하는 배열
int ary[20][20] = { 0, };  // 20x20 행렬을 0으로 초기화

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  // 두 변수를 교환하는 매크로

// 함수 선언
void makematrix(int n);  // 무작위 행렬 생성 함수
void sortmatrix(int n);  // 희소 행렬을 정렬하는 함수
void printarray(int ary[][20]);  // 행렬 출력 함수

int main()
{
    int num;

    // 사용자로부터 행렬의 원소 개수를 입력받음
    printf("원소의 개수를 쓰시오: ");
    scanf("%d", &num);

    makematrix(num);  // 무작위 행렬 생성
    sortmatrix(num);  // 희소 행렬을 행, 열 순으로 정렬

    printf("Random generated Matrix\n");
    printarray(ary);  // 생성된 행렬 출력

    printf("Sparse Matrix\n");
    // 희소 행렬을 출력 (행, 열, 값 순으로 출력)
    for (int i = 0; i <= num; i++)
        printf("%5d %5d %5d\n", a[i].row, a[i].col, a[i].value);

    return 0;
}

// 무작위 행렬 생성 함수
void makematrix(int n)
{
    int row, col, val;
    int used[20][20] = { 0 };  // 중복된 좌표 생성을 방지하기 위한 배열

    // a[0]에 행렬의 크기(20x20)와 원소 개수를 저장
    a[0].col = 20;
    a[0].row = 20;
    a[0].value = n;

    srand((unsigned int)time(NULL));  // 랜덤 시드 설정

    // n개의 원소를 무작위로 생성
    for (int i = 1; i <= n; i++) {
        do {
            row = rand() % 20;  // 0~19 사이의 행 좌표 무작위 생성
            col = rand() % 20;  // 0~19 사이의 열 좌표 무작위 생성
        } while (used[row][col]);  // 이미 사용된 좌표라면 다시 생성

        val = rand() % 99 + 1;  // 1~99 사이의 값 무작위 생성

        ary[row][col] = val;  // 행렬에 값을 저장

        a[i].row = row;  // 희소 행렬의 행 정보 저장
        a[i].col = col;  // 희소 행렬의 열 정보 저장
        a[i].value = val;  // 희소 행렬의 값 저장

        used[row][col] = 1;  // 해당 좌표가 사용되었음을 표시
    }
}

// 희소 행렬을 행, 열 순으로 정렬하는 함수
void sortmatrix(int n)
{
    term temp;  // 두 원소를 교환하기 위한 임시 변수
    int i, j, min;

    // 선택 정렬 알고리즘을 이용한 정렬
    for (i = 1; i <= n; i++) {
        min = i;
        for (j = i + 1; j <= n; j++) {
            // 행을 기준으로 정렬, 행이 같으면 열을 기준으로 정렬
            if (a[j].row < a[min].row)
                min = j;
            else if (a[j].row == a[min].row)
                if (a[j].col < a[min].col)
                    min = j;
        }

        // 최소값을 현재 위치로 교환
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

// 행렬을 출력하는 함수
void printarray(int ary[][20])
{
    // 20x20 행렬을 출력
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%5d", ary[i][j]);  // 5칸 공간을 두고 출력
        }
        printf("\n");
    }
}

/*
makematrix 함수: 무작위로 희소 행렬의 원소를 생성하여 20x20 행렬에 채워넣고, 중복 좌표를 방지합니다.
sortmatrix 함수: 생성된 희소 행렬을 행(row)과 열(col) 순서로 선택 정렬을 통해 정렬합니다.
printarray 함수: 20x20 행렬을 출력합니다.
메인 함수: 전체적인 프로그램 실행 흐름을 담당하며, 사용자로부터 입력을 받아 행렬을 생성하고 정렬한 후 출력합니다.*/