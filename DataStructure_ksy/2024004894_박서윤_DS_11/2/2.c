#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 30

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
} node;
treePointer root = NULL;

treePointer queue[MAX_QUEUE_SIZE];
int rear = 0;
int front = 0;

void insert(treePointer newnode);
void addq(treePointer item);
treePointer deleteq();
void queueFull();
void queueEmpty();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main()
{
	FILE* f;
	treePointer node = NULL;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "cannot open the file\n");
		exit(EXIT_FAILURE);
	}

	node = malloc(sizeof(*node));
	node->data = fgetc(f);
	node->leftChild = NULL; node->rightChild = NULL;
	printf("creating a complete binary tree\n\n");
	while (!feof(f)) {
		insert(node);
		node = malloc(sizeof(*node));
		node->data = fgetc(f);
		node->leftChild = NULL; node->rightChild = NULL;
	}
	free(node);
	fclose(f);

	printf("three binary tree traversals\n");
	printf("inorder traversal     : ");
	inorder(root);
	printf("\npreorder traversal    : ");
	preorder(root);
	printf("\npostorder traversal   : ");
	postorder(root);
	puts("");

	return 0;
}

void insert(treePointer newnode)
{
	if (root == NULL)
	{
		root = newnode;
	}
	else {
		if
			(queue[front + 1]->leftChild == NULL) queue[front + 1]->leftChild = newnode;
		else if
			(queue[front + 1]->rightChild == NULL) queue[front + 1]->rightChild = newnode;
		if (queue[front + 1]->leftChild != NULL && queue[front + 1]->rightChild != NULL)
			deleteq();
	}
	addq(newnode);
}

void addq(treePointer item)
{
	if (rear >= MAX_QUEUE_SIZE - 1) {
		queueFull();
		return;
	}

	queue[++rear] = item;
}

treePointer deleteq()
{
	if (front == rear)
		queueEmpty();

	return queue[++front];
}

void queueFull()
{
	if (front == -1) {
		fprintf(stderr, "queue is full, not added\n");
		exit(EXIT_FAILURE);
	}

	else {
		printf("data shift\n");
		while (front != -1) {
			for (int i = front; i <= rear; i++) {
				queue[i] = queue[i + 1];
			}
			front--;
			rear--;
		}
	}
}

void queueEmpty()
{
	fprintf(stderr, "queue is empty, cannot delete element\n");
	exit(EXIT_FAILURE);
}

void inorder(treePointer ptr)
{
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c ", ptr->data);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr)
{
	if (ptr) {
		printf("%c ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr)
{
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c ", ptr->data);
	}
}