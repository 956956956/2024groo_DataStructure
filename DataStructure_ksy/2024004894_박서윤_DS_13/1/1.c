#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 100

typedef struct Node {
    char value;
    struct Node* left, * right;
} Node;

// 스택 구조
typedef struct Stack {
    Node* nodes[MAX_EXPR_SIZE];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* stack) {
    stack->top = -1;
}

// 스택이 비었는지 확인
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택에 노드를 추가
void push(Stack* stack, Node* node) {
    stack->nodes[++stack->top] = node;
}

// 스택에서 노드를 제거
Node* pop(Stack* stack) {
    if (isEmpty(stack)) return NULL;
    return stack->nodes[stack->top--];
}

// 새 노드 생성
Node* newNode(char value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// Postfix 표현식을 이용해 이진 트리 구성
Node* buildExpressionTree(char* postfix) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        Node* node = newNode(ch);

        if (ch == '&' || ch == '|') {
            node->right = pop(&stack);
            node->left = pop(&stack);
        }
        else if (ch == '~') {
            node->left = pop(&stack);
        }

        push(&stack, node);
    }
    return pop(&stack);
}

// 이진 트리를 후위 순회하여 명제식을 계산
int evaluateExpression(Node* root, int a, int b, int c) {
    if (!root) return 0;

    // 피연산자일 경우 값 반환
    if (root->value == 'a') return a;
    if (root->value == 'b') return b;
    if (root->value == 'c') return c;

    // 연산자일 경우
    int left = evaluateExpression(root->left, a, b, c);
    int right = root->right ? evaluateExpression(root->right, a, b, c) : 0;

    switch (root->value) {
    case '&': return left && right;
    case '|': return left || right;
    case '~': return !left;
    }
    return 0;
}

// 모든 변수 조합을 테스트하고 명제식이 참이 되는 경우 출력
void findSatisfyingAssignments(Node* root) {
    printf("find true condition:\n");

    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            for (int c = 0; c <= 1; c++) {
                if (evaluateExpression(root, a, b, c)) {
                    printf("a = %d, b = %d, c = %d\n", a, b, c);
                }
            }
        }
    }
}

// 트리의 모든 노드를 재귀적으로 해제
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    char postfix[MAX_EXPR_SIZE];
    FILE* file = fopen("input.txt", "r");

    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    // 파일로부터 postfix 표현식 읽기
    fscanf(file, "%s", postfix);
    fclose(file);

    printf("input string(postfix): %s\n", postfix);

    // 이진 트리 생성
    Node* root = buildExpressionTree(postfix);

    // 참이 되는 모든 조합 찾기
    findSatisfyingAssignments(root);

    // 메모리 해제
    freeTree(root);

    return 0;
}
