#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 20

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild;
	treePointer rightChild;
};
treePointer root = NULL;
treePointer stack[MAX_STACK_SIZE];
int top = -1;
char expr[82];

typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, eos, operand
} precedence;

treePointer pop(){
	if (top == -1)
		printf("stack is empty");
	return stack[top--];
}

void stackFull(){
	printf("stack is full, cannot add item\n");
}

void push(treePointer item){
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	else
		stack[++top] = item;
}



precedence getToken(char* symbol, int* n){
	*symbol = expr[(*n)++];
	switch (*symbol){
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
	while( token != eos ){
		if( token == operand ){
			new = (treePointer)malloc(sizeof(struct node));
			new->data = symbol;
			new->leftChild = NULL;
			new->rightChild = NULL;
			
			push(new);
		}
		else{ 
			new = (treePointer)malloc(sizeof(struct node));
			new->data = symbol;
			new->rightChild = pop();
			new->leftChild = pop();

			push(new);
		}
		token = getToken( &symbol, &n);
	}
	return pop();
}

void inorder(treePointer p) {
	if (p) {
		inorder(p->leftChild);
		printf("%c", p->data);
		inorder(p->rightChild);
	}
}

void preorder(treePointer p) {
	if (p) {
		printf("%c", p->data);
		preorder(p->leftChild);
		preorder(p->rightChild);
	}
}

void postorder(treePointer p) {
	if (p) {
		postorder(p->leftChild);
		postorder(p->rightChild);
		printf("%c", p->data);
	}
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression) : ");
	int idx = 0;
	fgets(expr, 80, fp);
	printf("%s\n", expr);
	printf("creating its binary tree\n\n");
	root = binaryTree();
	fclose(fp);

	printf("inorder traversal	: ");
	inorder(root);
	printf("\npreorder traversal	: ");
	preorder(root);
	printf("\npostorder traversal	: ");
	postorder(root);

}