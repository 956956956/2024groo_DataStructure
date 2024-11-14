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
char itinorder[MAX_EXPR_SIZE];
char stackOrder[MAX_EXPR_SIZE];
int k = 0, n = 0;

treePointer memory[MAX_MEMORY_SIZE];
int top[3] = {-1, 2};
int boundary[3] = {-1, 2, 49};

treePointer queue[MAX_MEMORY_SIZE];
int front = 0, rear = 0;

void push(int i, treePointer elm);
treePointer pop(int i);
void addq(treePointer elm);
treePointer deleteq();
precedence getToken(char* symbol, int j);
void createTree(int j);
void iterInorder(treePointer ptr);
void levelOrder(treePointer ptr);

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
	printf("creating its binary tree\n");
	root = pop(0);

	printf("%-33s", "\niterative inorder traversal");
	printf(": ");
	iterInorder(root);
	for (int i = 0; i < n; i++)
		printf("%c ", itinorder[i]);
	
	printf("%-33s", "\n 스택에 들어가는 데이터의 순서");
	printf(": ");
	for (int i = 0; i < k; i++)
		printf("%c ", stackOrder[i]);

	printf("%-33s", "\n\nlevel order traversal");
	printf(" : ");
	levelOrder(root);
	printf("\n\n");
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

// 큐 기능
void addq(treePointer elm) {
	if (rear == (MAX_MEMORY_SIZE - 1))
		return;		// 큐 FULL
	queue[++rear] = elm;
}
treePointer deleteq() {
	if (rear == front)
		return NULL;	// 큐 Empty
	return queue[++front];
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

// inorder로 순회하며 배열에 저장
void iterInorder(treePointer ptr) {
	for (;;) {	// break문에서 끝나므로 종료 조건 없어도 OK!
		for (; ptr; ptr = ptr->leftChild) {
			stackOrder[k++] = ptr->data;
			push(1, ptr);
		}
		ptr = pop(1);
		if (!ptr) break;
		itinorder[n++] = ptr->data;
		ptr = ptr->rightChild;
	}
}

// level order로 출력
void levelOrder(treePointer ptr) {
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%c ", ptr->data);
			if (ptr->leftChild)
				addq(ptr->leftChild);
			if (ptr->rightChild)
				addq(ptr->rightChild);
		}
		else break;
	}
}