#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 80

// 스택 정의
char stack[MAX];
int top = -1;

// 스택 함수들
void push(char x) {
    if (top < MAX - 1) {
        stack[++top] = x;
    }
}

char pop() {
    if (top != -1) {
        return stack[top--];
    }
    return '\0';
}

char peek() {
    if (top != -1) {
        return stack[top];
    }
    return '\0';
}

// 연산자 우선순위 함수
int precedence(char x) {
    if (x == '(') return 0;
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/' || x == '%') return 2;
    return -1;
}

// 중위표기법을 후위표기법으로 변환
void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char x;

    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            // 피연산자일 경우 출력 (후위표기법에 추가)
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') {
            // '(' 스택에 추가
            push(infix[i]);
        }
        else if (infix[i] == ')') {
            // ')'를 만나면 '('를 만날 때까지 스택에서 꺼내 출력
            while ((x = pop()) != '(') {
                postfix[j++] = x;
            }
        }
        else {
            // 연산자일 경우
            while (top != -1 && precedence(peek()) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }

    // 스택에 남아있는 연산자 출력
    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // 문자열 끝 표시
}

int main() {
    char infix[MAX], postfix[MAX];
    FILE* fin, * fout;

    // 입력 파일 열기
    fin = fopen("input.txt", "r");
    if (fin == NULL) {
        printf("Error: input file not found.\n");
        return 1;
    }

    // 출력 파일 열기
    fout = fopen("output.txt", "w");
    if (fout == NULL) {
        printf("Error: cannot open output file.\n");
        fclose(fin);
        return 1;
    }

    // 입력 수식 읽기
    fscanf(fin, "%s", infix);

    // 중위표기법을 후위표기법으로 변환
    infixToPostfix(infix, postfix);

    // 결과 출력 (화면 및 파일)
    printf("infix expression : %s\npostfix expression : %s\n", infix, postfix);
    fprintf(fout, "%s\n", postfix);

    // 파일 닫기
    fclose(fin);
    fclose(fout);

    return 0;
}
