#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 80
#define MAX_MEMORY_SIZE 50

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;

typedef enum {
	plus, minus, times, divide, mod, eos, operand
}precedence;

char expr[MAX_EXPR_SIZE];
treePointer memory[MAX_MEMORY_SIZE];
int top[3] = { -1, 2 };
int boundary[3] = { -1, 2, 49 };

void push(int i, treePointer elm);
treePointer pop(int i);
int inStack(int i, treePointer elm);
precedence getToken(char* symbol, int j);
void createTree(int j);
void iterPreorder(treePointer ptr);
void iterPostorder(treePointer ptr);

int main() {
	FILE* fp = fopen("input.txt", "r");
	treePointer root = NULL;

	printf("the length of input string should be less than %d\n", MAX_EXPR_SIZE);
	int j = 0;
	while (fscanf(fp, "%c", &expr[j]) != EOF) {
		createTree(j);
		j++;
	}
	printf("input string (postfix expression) from input.txt : %s\n", expr);
	printf("creating its binary tree\n\n");
	root = pop(0);

	printf("%-30s", "\niterative preorder traversal");
	printf(": ");
	iterPreorder(root);

	printf("%-30s", "\niterative postorder traversal");
	printf(": ");
	iterPostorder(root);
}

// 스택 기능
void push(int i, treePointer elm) {
	if (top[i] == boundary[i + 1])
		return;		// 스택 FULL
	memory[++top[i]] = elm;
}
treePointer pop(int i) {
	if (top[i] == boundary[i])
		return NULL;		// 스택 Empty
	return memory[top[i]--];
}

int inStack(int i, treePointer elm) {
	for (int j = boundary[i] + 1; j <= top[i]; j++) {
		if (memory[j] == elm)
			return 1;
	}
	return 0;
}

// 연산자 구분
precedence getToken(char* symbol, int j) {
	(*symbol) = expr[j];

	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

// 트리 만들기
void createTree(int j) {
	char symbol;
	precedence token = getToken(&symbol, j);
	treePointer temp = (treePointer)malloc(sizeof(node));
	if (!temp) return;

	temp->data = symbol;

	if (token == operand) {
		temp->leftChild = NULL;
		temp->rightChild = NULL;
		push(0, temp);
	}
	else {
		temp->rightChild = pop(0);
		temp->leftChild = pop(0);
		push(0, temp);
	}
}

// preorder로 순회하며 출력
void iterPreorder(treePointer ptr) {
	for (;;) {	// break문에서 끝나므로 종료 조건 없어도 OK!
		while (ptr) {
			push(1, ptr);
			printf("%c", ptr->data);
			ptr = ptr->leftChild;
		}
		ptr = pop(1);
		if (!ptr) break;
		ptr = ptr->rightChild;
	}
}

void iterPostorder(treePointer ptr) {
	treePointer p = NULL;
	for (;;) {	// break문에서 끝나므로 종료 조건 없어도 OK!
		for (; ptr; ptr = ptr->leftChild)
			push(1, ptr);
		// 가장 최근에 스택에 넣은 노드 확인
		ptr = memory[top[1]];
		if (!ptr) break;

		// ptr의 오른쪽 노드가 없거나, 이미 검사헀다면 ptr출력
		if ((!ptr->rightChild) || ptr->rightChild == p) {
			printf("%c", ptr->data);
			p = pop(1);		// 이전에 검사한 노드 넣음
			ptr = NULL;
		}
		else
			ptr = ptr->rightChild;
	}
}