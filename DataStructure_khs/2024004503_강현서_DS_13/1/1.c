#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE (1==1)
#define FALSE !TRUE
#define MAX_SIZE 30

typedef enum {
	and, or, not, operand, true, false, eos
}logical;

typedef struct node* treePointer;
typedef struct node {
	treePointer leftChild;
	logical data;
	short int value;
	treePointer rightChild;
}node;

int combi[MAX_SIZE][3];
int cnt = 0;
char expr[MAX_SIZE];
treePointer stack[MAX_SIZE];
int top = -1;

void makeTruthTB();
void push(treePointer ptr);
treePointer pop();
logical getToken(char* symbol, int* n);
treePointer createTree();
void postOrderEval(treePointer ptr);

int main() {
	FILE* fp = fopen("input.txt", "r");
	int i = 0;
	treePointer root;
	while (fscanf(fp, "%c", &expr[i++]) != EOF);

	printf("%-25s", "input string(postfix)");
	printf(": ");
	printf("%s\n", expr);

	makeTruthTB();

	root = createTree();

	printf("find true condition\n");

	for (int row = 0; row < 8; row++) {
		postOrderEval(root);
		cnt++;
		if (root->value) {
			printf("a=%d, b=%d, c=%d",
				combi[row][0], combi[row][1], combi[row][2]);
		}
		if (row < 6) printf("\n");
	}
	fclose(fp);
}

void makeTruthTB() {
	int row, col = 0;

	for (row = 0; row < 8; row++) {
		combi[row][col] = (row >> 2) & 1;
		combi[row][col+1] = (row >> 1) & 1;
		combi[row][col+2] = (row) & 1;
	}
}

void push(treePointer ptr) {
	if (top >= MAX_SIZE - 1)
		return;
	stack[++top] = ptr;
}

treePointer pop() {
	if (top < 0)
		return NULL;
	return stack[top--];
}

logical getToken(char* symbol, int* n) {
	(*symbol) = expr[(*n)++];
	switch (*symbol) {
	case '&': return and;
	case '|' : return or;
	case '~': return not;
	case '\0': return eos;
	default: return operand;
	}
}

treePointer createTree() {
	char symbol;
	int n = 0;
	top = -1;
	treePointer temp = NULL;
	logical token = getToken(&symbol, &n);
	while (token != eos) {
		if((temp = (treePointer)malloc(sizeof(node))) ==  NULL)
			return NULL;
		if (token == operand) {
			temp->data = symbol;
			temp->leftChild = NULL;
			temp->rightChild = NULL;
		}
		else if (token == not) {
			temp->data = symbol;
			temp->rightChild = pop();
			temp->leftChild = NULL;
		}
		else {
			temp->data = symbol;
			temp->rightChild = pop();
			temp->leftChild = pop();
		}
		push(temp);
		token = getToken(&symbol, &n);
	}
	return pop();
}

void postOrderEval(treePointer ptr) {
	if (ptr) {
		postOrderEval(ptr->leftChild);
		postOrderEval(ptr->rightChild);
		switch (ptr->data) {
		case '~':
			ptr->value = !(ptr->rightChild->value);
			break;
		case '&':
			ptr->value = ptr->rightChild->value && ptr->leftChild->value;
			break;
		case '|':
			ptr->value = ptr->rightChild->value || ptr->leftChild->value;
			break;
		case 'a':
			ptr->value = combi[cnt][0];
			break;
		case 'b':
			ptr->value = combi[cnt][1];
			break;
		case 'c' :
			ptr->value = combi[cnt][2];
			break;
		}
	}
}