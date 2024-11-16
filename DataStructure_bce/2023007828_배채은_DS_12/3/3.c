#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 20
#define MAX_QUEUE_SIZE 20

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild;
	treePointer rightChild;
} Node;
treePointer root = NULL;

char expr[82];
treePointer stack[MAX_STACK_SIZE];
int top = -1;
typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, eos, operand
} precedence;

void push(treePointer item) {
	if (top >= MAX_STACK_SIZE - 1)
		printf("Stack is full\n");
	stack[++top] = item;
}

treePointer pop() {
	if (top == -1)
		return NULL;
	return stack[top--];
}

treePointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

void enqueue(treePointer item) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		printf("Queue is full\n");
		return;
	}
	queue[rear] = item;
}

treePointer dequeue() {
	if (front == rear) {
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

int isQueueEmpty() {
	return front == rear;
}

void iterativePreorder(treePointer root) {
	treePointer current;
	top = -1;
	push(root);

	while (top != -1) {
		current = pop();
		while (current) {
			printf("%c", current->data);

			if (current->rightChild)
				push(current->rightChild);
			current = current->leftChild;
		}
	}
}

void iterativePostorder(treePointer root) {
	treePointer current = root;
	treePointer lastVisited = NULL;
	top = -1;

	while (current || top != -1) {
		if (current) {
			push(current);
			current = current->leftChild;
		}
		else {
			treePointer topNode = stack[top];
			if (topNode->rightChild && lastVisited != topNode->rightChild) {
				current = topNode->rightChild;
			}
			else {
				printf("%c", topNode->data);
				lastVisited = pop();
			}
		}
	}
}



precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

treePointer binaryTree() {
	treePointer new;
	precedence token;
	int n = 0;
	char symbol;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) {
			new = (treePointer)malloc(sizeof(struct node));
			new->data = symbol;
			new->leftChild = NULL;
			new->rightChild = NULL;

			push(new);
		}
		else {
			new = (treePointer)malloc(sizeof(struct node));
			new->data = symbol;
			new->rightChild = pop();
			new->leftChild = pop();

			push(new);
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) from input.txt : ");
	int idx = 0;
	fgets(expr, 80, fp);
	printf("%s\n", expr);
	printf("creating its binary tree\n\n");

	root = binaryTree(expr);

	printf("Iterative preorder Traversal	: ");
	iterativePreorder(root);
	printf("\n");

	printf("Iterative postorder Traversal	: ");
	iterativePostorder(root);
	printf("\n");


	return 0;
}

