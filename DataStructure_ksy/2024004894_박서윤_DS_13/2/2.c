#include <stdio.h>
#include <stdlib.h>

#define MAX 9
#define FALSE 0
#define TRUE 1

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
};
threadedPointer root = NULL;
threadedPointer arr[MAX];

void makeThreaded();
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);

int main()
{
	root = malloc(sizeof(*root));
	for (int i = 0; i < MAX; i++) {
		arr[i] = malloc(sizeof(*root));
		arr[i]->leftChild = NULL; arr[i]->rightChild = NULL;
		arr[i]->data = 65 + i;
	}
	makeThreaded();

	printf("%p (%d, %p, %c, %d, %p)\n", root, root->leftThread, root->leftChild, root->data, root->rightThread, root->rightChild);
	tinorder(root);

	free(root);
	for (int i = 0; i < MAX; i++)
		free(arr[i]);

	return 0;
}

void makeThreaded()
{
	root->data = NULL;
	root->leftChild = arr[0];
	root->rightChild = root;
	root->leftThread = FALSE;
	root->rightThread = FALSE;

	arr[0]->leftChild = arr[1];
	arr[0]->rightChild = arr[2];

	arr[1]->leftChild = arr[3];
	arr[1]->rightChild = arr[4];

	arr[2]->leftChild = arr[5];
	arr[2]->rightChild = arr[6];

	arr[3]->leftChild = arr[7];
	arr[3]->rightChild = arr[8];

	for (int i = 0; i < MAX; i++) {
		if (arr[i]->leftChild) arr[i]->leftThread = FALSE;
		else arr[i]->leftThread = TRUE;
		if (arr[i]->rightChild) arr[i]->rightThread = FALSE;
		else arr[i]->rightThread = TRUE;
	}

	arr[4]->leftChild = arr[1];
	arr[4]->rightChild = arr[0];

	arr[5]->leftChild = arr[0];
	arr[5]->rightChild = arr[2];

	arr[6]->leftChild = arr[2];
	arr[6]->rightChild = root;

	arr[7]->leftChild = root;
	arr[7]->rightChild = arr[3];

	arr[8]->leftChild = arr[3];
	arr[8]->rightChild = arr[1];
}

threadedPointer insucc(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread)
		while (!temp->leftThread)
			temp = temp->leftChild;
	return temp;
}

void tinorder(threadedPointer tree)
{
	threadedPointer temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%p (%d, %p, %c, %d, %p)\n", temp, temp->leftThread, temp->leftChild, temp->data, temp->rightThread, temp->rightChild);
	}
}