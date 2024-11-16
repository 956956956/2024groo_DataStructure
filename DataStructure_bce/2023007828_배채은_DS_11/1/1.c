#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild;
	treePointer rightChild;
};
treePointer root = NULL;

treePointer createNode(char data) {
	treePointer new = (treePointer)malloc(sizeof(struct node));
	new->data = data;
	new->leftChild = new->rightChild = NULL;
	return new;
}

void inorder(treePointer p) {
	if (p) {
		inorder(p->leftChild);
		printf("(%p : %p  %c  %p)\n", p, p->leftChild, p->data, p->rightChild);
		inorder(p->rightChild);
	}
}

void preorder(treePointer p) {
	if (p) {
		printf("(%p : %p  %c  %p)\n", p, p->leftChild, p->data, p->rightChild);
		preorder(p->leftChild);
		preorder(p->rightChild);
	}
}

void postorder(treePointer p) {
	if (p) {
		postorder(p->leftChild);
		postorder(p->rightChild);
		printf("(%p : %p  %c  %p)\n", p, p->leftChild, p->data, p->rightChild);
	}
}

int main() {
	printf("creating a binary tree\n\n");
	treePointer A = createNode('A');
	treePointer B = createNode('B');
	treePointer C = createNode('C');
	treePointer D = createNode('D');
	treePointer E = createNode('E');
	A->leftChild = B;
	B->leftChild = D;
	B->rightChild = E;
	A->rightChild = C;
	root = A;

	printf("three binary tree traversals\n");
	printf("inorder traversal	:\n");
	inorder(root);
	printf("\npreorder traversal	:\n");
	preorder(root);
	printf("\npostorder traversal	:\n");
	postorder(root);

}