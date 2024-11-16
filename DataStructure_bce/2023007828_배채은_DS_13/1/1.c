#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 82
#define MAX_STACK_SIZE 20



typedef enum{not, and, or, true, false, operand, eos} logical;
typedef struct node* treePointer;
typedef struct node{
	treePointer leftChild;
	char data;
	int value;
	treePointer rightChild;
}node;

treePointer root = NULL;

treePointer stack[MAX_STACK_SIZE];
int top = -1;
int vtable[8][3] = { 0 };
int tcnt;

char expr[MAX_EXPR_SIZE];
treePointer createBinTree();
logical getToken(char*, int*);
void postOrderEval(treePointer);
void maketable();



int main(){
	FILE* fp;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "%s", "file open error\n");
		exit(EXIT_FAILURE);
	}
	fgets(expr, 80, fp);
	printf("input string(postfix)	: %s\n", expr);
	printf("find true condition\n");
	maketable();

	root = createBinTree();
	for (tcnt = 0; tcnt < 8; tcnt++) {
		postOrderEval(root);
		if(root->value)
			printf("a=%d, b=%d, c=%d\n", vtable[tcnt][0], vtable[tcnt][1], vtable[tcnt][2]);
	}


}

void postOrderEval(treePointer node) {
	if (node) {
		postOrderEval(node->leftChild);
		postOrderEval(node->rightChild);
		switch (node->data) {
		case '~':
			node->value = !(node->rightChild->value);
			break;
		case '&':
			node->value = node->rightChild->value && node->leftChild->value;
			break;
		case '|':
			node->value = node->rightChild->value || node->leftChild->value;
			break;
		case 'a':
			node->value = vtable[tcnt][0];
			break;
		case 'b':
			node->value = vtable[tcnt][1];
			break;
		case 'c':
			node->value = vtable[tcnt][2];
			break;
		default:
			break;
		}
	}
}

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

logical getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '~': return not;
	case '|': return or;
	case '&': return and;
	case '\0': return eos;
	default: return operand;
	}
}

treePointer createBinTree() {
	treePointer new;
	logical token;
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
		else if (token == not) {
			new = (treePointer)malloc(sizeof(struct node));
			new->data = symbol;
			new->leftChild = NULL;
			new->rightChild = pop();
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

void maketable() {
	int row, col = 0;

	for (row = 0; row < 8; row++) {
		vtable[row][col] = (row >> 2) & 1;
		vtable[row][col + 1] = (row >> 1) & 1;
		vtable[row][col + 2] = (row) & 1;
		col = 0;
	}
}