#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

typedef int iType;
typedef struct {
	int key;
	iType item;
} element;

typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
} tNode;
treePointer root = NULL;

element* search(treePointer root, int k);
void insert(treePointer* node, int k, iType theItem);
treePointer modifiedSearch(treePointer node, int k);
void inorder(treePointer ptr);

int main()
{
	int i, n, seed, s, item;
	tNode temp;

	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf_s("%d", &n);
	printf("%s", "seed : ");
	scanf_s("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);

	printf("generating number : ");
	for (i = 0; i <= n; i++) {
		item = (rand() % MAX_SIZE) + 1;
		printf("%d ", item);
		insert(&root, item, item);
	}
	puts("");
	printf("the key to search : ");
	scanf_s("%d", &s);
	printf("the search process : ");
	if (search(root, s) != NULL) printf("\nthe element is in BST\n");
	else printf("\nthe element is not in BST\n");

	printf("\ninorder traversal of the BST shows the sorted sequence\n");
	inorder(root);
	puts("");

	return 0;
}

element* search(treePointer root, int k)
{
	if (!root) return NULL;
	printf("%d => ", root->data.key);
	if (k == root->data.key) return &(root->data);
	if (k < root->data.key)
		return search(root->leftChild, k);
	return search(root->rightChild, k);
}

void insert(treePointer* node, int k, iType theItem)
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		ptr = malloc(sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*node)
			if (k < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
		else *node = ptr;
	}
}

treePointer modifiedSearch(treePointer node, int k)
{
	if (!node)
		return NULL;
	else
	{
		while (node) {
			if (!node->leftChild && !node->rightChild)
				return node;
			if (node->data.key > k)
				node = node->leftChild;
			else if (node->data.key < k)
				node = node->rightChild;
			else
				return NULL;
		}
	}
}

void inorder(treePointer ptr)
{
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%5d", ptr->data.key);
		inorder(ptr->rightChild);
	}
}