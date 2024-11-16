// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild, rightChild;
} node;

treePointer root = NULL;

// Binary Tree ���� �Լ�
void makeBT(treePointer cur, int data);
// Binary Tree Traversal �Լ�
void inorder(treePointer ptr);
void postorder(treePointer ptr);
void preorder(treePointer ptr);

int main() {
	int input;

	while (1) {
		printf("input data: ");
		scanf("%d", &input);

		if (input == -1) {
			printf("����");
			break;
		}

		root = (node*)malloc(1 * sizeof(node));
		root->leftChild = NULL;
		root->data = input;
		root->rightChild = NULL;

		makeBT(root, input);

		printf("\nInorder: ");		inorder(root);
		printf("\nPostorder: ");	postorder(root);
		printf("\nPreorder: ");		preorder(root);

		printf("\n\n");
	}

	free(root);
	return 0;
}

/* Binary Tree �����ϴ� �Լ� */
void makeBT(treePointer cur, int data) {
	// left child ����
	if (data * 3 <= 100) {
		treePointer child = (node*)malloc(1 * sizeof(node));
		child->leftChild = NULL;
		child->data = data*3;
		child->rightChild = NULL;

		cur->leftChild = child;

		makeBT(cur->leftChild, data * 3);	// ���
	}
	// right child ����
	if (data * 4 <= 100) {
		treePointer child = (node*)malloc(1 * sizeof(node));
		child->leftChild = NULL;
		child->data = data*4;
		child->rightChild = NULL;

		cur->rightChild = child;

		makeBT(cur->rightChild, data * 4);	// ���
	}
}

/* Binary Tree Traversal �Լ� */
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%d ", ptr->data);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}