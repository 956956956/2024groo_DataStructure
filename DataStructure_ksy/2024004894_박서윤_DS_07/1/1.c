#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR_SIZE 80

// 스택 구조 정의
typedef struct {
    int data[MAX_EXPR_SIZE];
    int top;
} Stack;

// 스택 초기화 함수
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 확인하는 함수
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택에 값을 푸시하는 함수
void push(Stack* s, int value) {
    if (s->top < MAX_EXPR_SIZE - 1) {
        s->data[++(s->top)] = value;
    }
    else {
        printf("Stack overflow!\n");
    }
}

// 스택에서 값을 팝하는 함수
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    else {
        printf("Stack underflow!\n");
        exit(1);
    }
}

// 후위표기법 계산 함수
int evaluatePostfix(const char* expr) {
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            push(&s, expr[i] - '0');
        }
        else {
            int op2 = pop(&s);
            int op1 = pop(&s);
            switch (expr[i]) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            case '%': push(&s, op1 % op2); break;
            default: printf("Unknown operator: %c\n", expr[i]); exit(1);
            }
        }
    }
    return pop(&s);
}

int main() {
    FILE* inputFile, * outputFile;
    char expr[MAX_EXPR_SIZE];

    // 입력 파일 열기
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input.txt\n");
        return 1;
    }

    // 후위 표기법 수식 읽기
    fscanf(inputFile, "%s", expr);
    fclose(inputFile);

    // 계산 수행
    int result = evaluatePostfix(expr);

    // 결과를 화면과 파일에 출력
    printf("postfix expression : %s\nthe evaluation value = %d\n", expr, result);

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open output.txt\n");
        return 1;
    }
    fprintf(outputFile, "%s = %d\n", expr, result);
    fclose(outputFile);

    return 0;
}
