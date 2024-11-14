#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* treepointer;
struct node {
	char data;
	treepointer leftchild, rightchild;
};
typedef struct node Node;

void inorder(treepointer node);
void preorder(treepointer node);
void postorder(treepointer node);
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
	printf("input string (postfix expression) : %s\n", exp);
	printf("creating its binary tree\n\n");

	int n = strlen(exp);
	root->data = exp[--n];
	root->leftchild = NULL;
	root->rightchild = NULL;
	insert(&root, exp, n);

	fclose(fp);
	printf("inorder traversal	 : ");
	inorder(root);
	printf("\npreorder traversal	 : ");
	preorder(root);
	printf("\npostorder traversal	 : ");
	postorder(root);
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


void inorder(treepointer node) {
	if (node) {
		inorder(node->leftchild);
		printf("%c", node->data);
		inorder(node->rightchild);
	}
}
void preorder(treepointer node) {
	if (node) {
		printf("%c", node->data);
		preorder(node->leftchild);
		preorder(node->rightchild);
	}

}
void postorder(treepointer node) {
	if (node) {
		postorder(node->leftchild);
		postorder(node->rightchild);
		printf("%c", node->data);
	}
}