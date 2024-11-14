#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;

treePointer queue[50];
int front = -1, rear = -1;

void Enqueue(treePointer newNode);
treePointer Dequeue();
treePointer createNode(char lett);
void insert(treePointer *root, char lett);
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

void Enqueue(treePointer newNode) {
	if (rear >= 50 - 1) // ť FULL
		return;
	queue[++rear] = newNode;
}

treePointer Dequeue() {
	if (front == rear) // ť EMPTY
	{
		printf("\nempty\n");
		return NULL;
	}
	return queue[++front];
}

treePointer createNode(char lett) {
	treePointer ptr = (treePointer)malloc(sizeof(*ptr));
	if (!ptr) return NULL;

	ptr->data = lett;
	ptr->leftChild = NULL;
	ptr->rightChild = NULL;

	return ptr;
}

void insert(treePointer* root, char lett) {
	treePointer frtNode = NULL;
	treePointer newNode = createNode(lett);
	
	if ((*root) == NULL)
		(*root) = newNode;
	else {
		frtNode = queue[front + 1];
		
		if (frtNode->leftChild == NULL)
			frtNode->leftChild = newNode;
		else if (frtNode->rightChild == NULL) {
			frtNode->rightChild = newNode;
			Dequeue();
		}
	}
	Enqueue(newNode);
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf(" %c", ptr->data);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf(" %c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf(" %c", ptr->data);
	}
}

int main() {
	treePointer rootP = NULL, newNode = NULL;
	char lett;
	FILE* fp = fopen("input.txt", "r");
	
	printf("creating a complete binary tree\n");

	while (fscanf(fp, "%c", &lett) != EOF) {
		// printf("%c\n", lett);
		insert(&rootP, lett);	// insert
	}

	printf("\nthree binary tree traversals");
	printf("\ninorder traversal");
	printf("%5s", ":");
	inorder(rootP);

	printf("\npreorder traversal");
	printf("%4s", ":");
	preorder(rootP);

	printf("\npostorder traversal");
	printf("%3s", ":");
	postorder(rootP);
}