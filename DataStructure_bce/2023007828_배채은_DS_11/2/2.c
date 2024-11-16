#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 20

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild;
	treePointer rightChild;
};
treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;

void add(treePointer new) {
	queue[++rear] = new;
	return;
}

treePointer delete() {
	return queue[++front];
}

treePointer insertNode(char data) {
	treePointer new = (treePointer)malloc(sizeof(struct node));
	new->data = data;
	new->leftChild = new->rightChild = NULL;
	if (root == NULL)
		root = new;
	else {
		while (1) {
			treePointer frontP = delete();
			front--;
			if (frontP->leftChild == NULL) {
				frontP->leftChild = new;
				break;
			}
			else if (frontP->rightChild == NULL) {
				frontP->rightChild = new;
				break;
			}
			else {
				delete();
			}
		}

	}
	add(new);
}

void inorder(treePointer p) {
	if (p) {
		inorder(p->leftChild);
		printf("%c ", p->data);
		inorder(p->rightChild);
	}
}

void preorder(treePointer p) {
	if (p) {
		printf("%c ", p->data);
		preorder(p->leftChild);
		preorder(p->rightChild);
	}
}

void postorder(treePointer p) {
	if (p) {
		postorder(p->leftChild);
		postorder(p->rightChild);
		printf("%c ", p->data);
	}
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	printf("creating a complete binary tree\n\n");
	char line[82];
	int idx = 0;
	fgets(line, 80, fp);
	while(1){
		char data = line[idx++];
		if (data == NULL) break;
		insertNode(data);
	}
	fclose(fp);

	printf("three binary tree traversals\n");
	printf("inorder traversal	: ");
	inorder(root);
	printf("\npreorder traversal	: ");
	preorder(root);
	printf("\npostorder traversal	: ");
	postorder(root);

}