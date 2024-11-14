#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

typedef struct {
	int key;
	int item;
}element;

typedef struct node* treePointer;
typedef struct node{
	element data;
	treePointer leftChild, rightChild;
}node;

void insert(treePointer* node, int k, int itm);
element* search(treePointer root, int k);
treePointer modifySearch(treePointer *node, int k);
void inorder(treePointer root);

int main() {
	int n, seed, findN;
	element elm;
	treePointer head = NULL;
	element* res = NULL;

	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf_s("%d", &n);
	printf("%s", "seed : ");
	scanf_s("%u", &seed);
	printf("\ncreating a BST from random numbers\n");

	printf("generating number :");
	srand(seed);
	for (int i = 0; i < n; i++) {
		elm.key = rand() % 500 + 1;
		elm.item = elm.key;
		printf(" %3d", elm.key);
		insert(&head, elm.key, elm.item);
	}

	printf("\nthe key to search : ");
	scanf_s("%d", &findN);

	printf("the search process :");
	res = search(head, findN);
	if (res)
		printf("\nthe element is in BST\n");
	else
		printf("\nthe element is not in BST\n");

	printf("\ninorder traversal of the BST shows the sorted sequence\n");
	inorder(head);
}

treePointer modifySearch(treePointer* node, int k) {
	treePointer root = (*node);
	treePointer pre = root;
	if (!root)
		return NULL;
	else {
		while (root) {
			if (k < root->data.key) {
				pre = root;
				root = root->leftChild;
			}
			else {
				pre = root;
				root = root->rightChild;
			}
		}
		return pre;
	}
}

element* search(treePointer root, int k) {
	while (root) {
		printf(" %d =>", root->data.key);
		if (k == root->data.key)
			return &(root->data);
		if (k < root->data.key)
			root = root->leftChild;
		else
			root = root->rightChild;
	}
	return NULL;
}

void insert(treePointer* node, int k, int itm) {
	treePointer ptr = NULL;
	treePointer temp = modifySearch(node, k);

	if (temp || !(*node)) {
		if (( ptr = (treePointer)malloc(sizeof(*ptr)) ) == NULL)
			return;
		ptr->data.key = k;
		ptr->data.item = itm;
		ptr->leftChild = NULL;
		ptr->rightChild = NULL;

		if (*node) {
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else *node = ptr;
	}
}

void inorder(treePointer root) {
	if (root) {
		inorder(root->leftChild);
		printf(" %3d", root->data.key);
		inorder(root->rightChild);
	}
}