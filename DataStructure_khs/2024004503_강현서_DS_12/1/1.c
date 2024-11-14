#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 80
#define MAX_STACK_SIZE 41

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;

typedef enum {
	plus, minus, times, divide, mod, eos, operand
}precedence;

char expr[MAX_EXPR_SIZE];
treePointer stack[MAX_STACK_SIZE];
int top = -1;

void push(treePointer elm);
treePointer pop();
precedence getToken(char* symbol, int i);
void createTree(int i);
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main() {
	FILE* fp = fopen("input.txt", "r");
	treePointer root = NULL;

	printf("the length of input string should be less than %d\n",
		MAX_EXPR_SIZE);
	printf("input string (postfix expression) : ");

	int i = 0;
	while (fscanf(fp, "%c", &expr[i]) != EOF) {
		createTree(i);
		printf("%c", expr[i++]);
	}

	printf("\ncreating its binary tree\n");
	root = pop();

	printf("%-20s", "\ninorder traversal");
	printf(" : ");
	inorder(root);

	printf("%-20s", "\npreorder traversal");
	printf(" : ");
	preorder(root);

	printf("%-20s", "\npostorder traversal");
	printf(" : ");
	postorder(root);
}

// 피연산자 연산자 구분
precedence getToken(char* symbol, int i) {
	*symbol = expr[i];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	default: return operand;
	}
}

// 스택 기능
void push(treePointer elm) {
	if (top >= MAX_STACK_SIZE - 1)	// 스택 full
		return;
	stack[++top] = elm;
}

treePointer pop() {
	if (top < 0)	// 스택 empty
		return NULL;
	return stack[top--];
}

// 트리 만들기
void createTree(int i) {
	char symbol;
	precedence token;
	treePointer elm = NULL;

	token = getToken(&symbol, i);

	elm = (treePointer)malloc(sizeof(*elm));
	if (!elm) return;
	elm->data = symbol;

	if (token == operand) {
		elm->leftChild = NULL;
		elm->rightChild = NULL;
		push(elm);
	}
	else {
		elm->rightChild = pop();
		elm->leftChild = pop();
		push(elm);
	}
}

// 트리 탐색 및 표현식 출력
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}