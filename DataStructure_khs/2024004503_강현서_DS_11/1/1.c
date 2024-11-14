#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}node;

treePointer createNode(char data);
treePointer createBinary();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

treePointer createNode(char letter) {
	treePointer ptr = (treePointer)malloc(sizeof(*ptr));
	if (!ptr) return NULL;

	ptr->data = letter;
	ptr->leftChild = NULL;
	ptr->rightChild = NULL;

	return ptr;
}

treePointer createBinary() {
	treePointer nodeAp = createNode('A');
	treePointer nodeBp = createNode('B');
	treePointer nodeCp = createNode('C');
	treePointer nodeDp = createNode('D');
	treePointer nodeEp = createNode('E');

	nodeAp->leftChild = nodeBp;
	nodeAp->rightChild = nodeCp;
	nodeBp->leftChild = nodeDp;
	nodeBp->rightChild = nodeEp;

	return nodeAp;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("(%p : %p %c %p)\n",
			ptr, ptr->leftChild, ptr->data, ptr->rightChild);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("(%p : %p %c %p)\n",
			ptr, ptr->leftChild, ptr->data, ptr->rightChild);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("(%p : %p %c %p)\n",
			ptr, ptr->leftChild, ptr->data, ptr->rightChild);
	}
}

int main() {
	treePointer rootP = NULL;
	printf("creating a binary tree\n");
	rootP = createBinary();

	printf("\nthree binary tree traversals\n");
	printf("inorder traversal");
	printf("%5s", ":\n");
	inorder(rootP);

	printf("\npreorder traversal");
	printf("%5s", ":\n");
	preorder(rootP);

	printf("\npostorder traversal");
	printf("%5s", ":\n");
	postorder(rootP);
}