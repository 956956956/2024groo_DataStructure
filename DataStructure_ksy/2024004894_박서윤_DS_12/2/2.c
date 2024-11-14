#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 80
#define MAX_QUEUE_SIZE 10

typedef struct node* treepointer;
struct node {
	char data;
	treepointer leftchild, rightchild;
};
typedef struct node Node;
treepointer stack[MAX_STACK_SIZE];
int top = -1;

int index = 0;
char d[MAX_STACK_SIZE];

treepointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

void push(treepointer node);
treepointer pop();
void iterinorder(treepointer node);
void levelorder(treepointer node);
void insert(treepointer* node, char* c, int n);
treepointer deleteq();
void addq(treepointer item);

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
	printf("input string (postfix expression) from input.txt : %s\n", exp);
	printf("creating its binary tree\n\n");

	int n = strlen(exp);
	root->data = exp[--n];
	root->leftchild = NULL;
	root->rightchild = NULL;
	insert(&root, exp, n);

	fclose(fp);
	printf("iterative inorder traversal   : ");
	iterinorder(root);
	printf("스택에 들어가는 데이터의 순서 : ");
	for (i = 0; i < index; i++) printf("%c ", d[i]);
	puts("");

	printf("\nlevel order traversal	      : ");
	levelorder(root);
	puts("");

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


void iterinorder(treepointer node) {
	for (;;) {
		for (; node; node = node->leftchild) push(node);
		node = pop();
		if (!node) break;
		printf("%c ", node->data);
		node = node->rightchild;
	}
	puts("");
}

void levelorder(treepointer node) {
	if (!node) return;
	addq(node);
	for (;;) {
		node = deleteq();
		if (node) {
			printf("%c ", node->data);
			if (node->leftchild) addq(node->leftchild);
			if (node->rightchild) addq(node->rightchild);
		}
		else break;
	}
}

void push(treepointer node) {
	if (top == MAX_STACK_SIZE - 1) {
		fprintf(stderr, "stack full\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = node;
	d[index++] = node->data;
}
treepointer pop() {
	return stack[top--];
}

void addq(treepointer item)
{
	if (front == (rear + 1) % MAX_QUEUE_SIZE) {
		fprintf(stderr, "queue full\n");
		exit(EXIT_FAILURE);
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = item;
}

treepointer deleteq()
{
	treepointer item;
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}