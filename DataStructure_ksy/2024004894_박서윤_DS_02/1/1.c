#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* func1() {
    int* p = (int*)malloc(sizeof(int));  // int 크기만큼 동적할당
    if (p == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    *p = 10;  // 10을 저장
    return p;
}

void func2(int* p) {
    if (p != NULL) {
        *p = 100;  // 포인터가 가리키는 값 수정
    }
}

void func3(int** p) {
    if (p != NULL && *p != NULL) {
        **p = 200;  // 이중 포인터를 통해 값 수정
    }
}

char* func4(int size) {
    char* p = (char*)malloc(size * sizeof(char));  // size만큼 동적할당
    if (p == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return p;
}

int main(void) {
    int* pNum;
    char* pChar;

    pNum = func1();  // int 크기만큼 동적할당 받아 10을 저장 후 정수형 포인터 리턴
    printf("%d\n", *pNum);

    func2(pNum);  // pNum이 가리키는 것을 100으로 수정
    printf("%d\n", *pNum);

    func3(&pNum);  // pNum이 가리키는 것을 200으로 수정
    printf("%d\n", *pNum);

    pChar = func4(100);  // pChar는 100 byte 할당받은 메모리에 키보드로부터 입력 받은 문자열 저장
    char string[100];
    printf("Enter a string: ");
    scanf_s("%99s", string, sizeof(string));  // 최대 99자까지 입력

    strncpy_s(pChar, 100, string, strlen(string));  // 안전하게 문자열 복사
    pChar[99] = '\0';  // 마지막 바이트에 널 문자 추가

    printf("pChar contents = %s\n", pChar);

    free(pNum);
    pNum = NULL;  // free 후 NULL로 초기화

    free(pChar);
    pChar = NULL;  // free 후 NULL로 초기화
    return 0;
}
