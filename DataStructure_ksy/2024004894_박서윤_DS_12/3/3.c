#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 80

typedef struct Node* treepointer;
struct Node {
	char data;
	treepointer leftchild, rightchild;
};
typedef struct Node Node;
treepointer stack[MAX_STACK_SIZE];
int top = -1;

void push(treepointer node);
treepointer pop();
int iterpreorder(treepointer node);
int iterpostorder(treepointer node);
void insert(treepointer* node, char* c, int n);


int main() {
	FILE* fp;
	char exp[80];
	int i;
	treepointer root = (treepointer)malloc(sizeof(Node));
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	fgets(exp, 80, fp);
	printf("the length of input string should be less than 80\n");
	printf("input string (postfix expression): %s\n", exp);
	printf("creating its binary tree\n\n");

	int n = strlen(exp);
	root->data = exp[--n];
	root->leftchild = NULL;
	root->rightchild = NULL;
	insert(&root, exp, n);

	fclose(fp);
	printf("preorder traversal   : ");
	i = iterpreorder(root);
	top = -1;

	printf("postorder traversal : ");
	i = iterpostorder(root);

}

void insert(treepointer* node, char* c, int n) {
	int i = n - 1;
	treepointer newnode;
	treepointer tmp = *node;
	for (; i >= 0;) {
		newnode = (treepointer)malloc(sizeof(Node));
		newnode->data = c[i--];
		newnode->leftchild = NULL;
		newnode->rightchild = NULL;
		tmp->rightchild = newnode;

		newnode = (treepointer)malloc(sizeof(Node));
		newnode->data = c[i--];
		newnode->leftchild = NULL;
		newnode->rightchild = NULL;
		tmp->leftchild = newnode;
		tmp = tmp->leftchild;
	}
}

int iterpreorder(treepointer node) {
	int cnt = 0;
	for (;;) {
		for (; node; node = node->leftchild) {
			push(node);
			cnt++;
			printf("%c ", node->data);
		}
		node = pop();
		if (!node) break;
		node = node->rightchild;
	}
	puts("");
	return cnt;
}

int iterpostorder(treepointer node) {
	treepointer stack2[MAX_STACK_SIZE];
	int top2 = -1;
	int cnt = 0;
	push(node);
	cnt++;
	while (top != -1) {
		node = pop();
		if (node->leftchild) {
			push(node->leftchild);
			cnt++;
		}
		if (node->rightchild) {
			push(node->rightchild);
			cnt++;
		}
		stack2[++top2] = node;
	}

	while (top2 != -1) {
		printf("%c ", stack2[top2--]->data);
	}
	puts("");
	return cnt;
}


void push(treepointer node) {
	if (top == MAX_STACK_SIZE - 1) {
		fprintf(stderr, "stack full\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = node;
}
treepointer pop() {
	return stack[top--];
}
