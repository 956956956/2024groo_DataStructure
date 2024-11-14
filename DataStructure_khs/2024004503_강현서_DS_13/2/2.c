#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	short int leftThread;
	treePointer leftChild;
	char data;
	short int rightThread;
	treePointer rightChild;
}node;

treePointer createNode(char elm);
treePointer createTree();
treePointer insucc(treePointer tree);
void inorder(treePointer ptr);

int main() {
	treePointer root;
	root = createTree();

	inorder(root);
}

treePointer createNode(char elm) {
	treePointer temp = NULL;
	if ((temp = (treePointer)malloc(sizeof(node))) == NULL)
		return NULL;
	temp->leftThread = 0;
	temp->leftChild = NULL;
	temp->data = elm;
	temp->rightThread = 0;
	temp->rightChild = NULL;
}

treePointer createTree() {
	treePointer head, nodeA, nodeB, nodec, nodeD, nodeE, nodef, nodeG, nodeH, nodeI;
	head = createNode('\0');
	nodeA = createNode('A');
	nodeB = createNode('B');
	nodec = createNode('A' + 2);
	nodeD = createNode('D');
	nodeE = createNode('E');
	nodef = createNode('A' + 5);
	nodeG = createNode('G');
	nodeH = createNode('H');
	nodeI = createNode('I');

	head->leftChild = nodeA; head->rightChild = head;
	nodeA->leftChild = nodeB; nodeA->rightChild = nodec;
	nodeB->leftChild = nodeD; nodeB->rightChild = nodeE;
	nodec->leftChild = nodef; nodec->rightChild = nodeG;
	nodeD->leftChild = nodeH; nodeD->rightChild = nodeI;
	nodeE->leftThread = 1; nodeE->rightThread = 1;
	nodeE->leftChild = nodeB; nodeE->rightChild = nodeA;
	nodef->leftThread = 1;  nodef->rightThread = 1;
	nodef->leftChild = nodeA; nodef->rightChild = nodec;
	nodeG->leftThread = 1;  nodeG->rightThread = 1;
	nodeG->leftChild = nodec; nodeG->rightChild = head;
	nodeH->leftThread = 1;  nodeH->rightThread = 1;
	nodeH->leftChild = head; nodeH->rightChild = nodeD;
	nodeI->leftThread = 1;  nodeI->rightThread = 1;
	nodeI->leftChild = nodeD; nodeI->rightChild = nodeB;

	return head;
}

treePointer insucc(treePointer tree) {
	treePointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread) {
		while (!temp->leftThread)
			temp = temp->leftChild;
	}
	return temp;
}

void inorder(treePointer ptr) {
	treePointer temp = ptr;
	printf("%p(%d, %p, %c, %d, %p)\n",
		temp, temp->leftThread, temp->leftChild,
		temp->data, temp->rightThread, temp->rightChild);
	for (;;) {
		temp = insucc(temp);
		if (temp == ptr) break;
		printf("%p(%d, %p, %c, %d, %p)\n",
			temp, temp->leftThread, temp->leftChild,
			temp->data, temp->rightThread, temp->rightChild);
	}
}