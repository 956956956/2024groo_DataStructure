#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

//왼쪽 서브트리들은 부모보다 작아야 하고 오른쪽 서브트리들은 커야 함
//key값은 전부 다 달라야 함

typedef struct {
	int key;
}element;

typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
} node;
treePointer root = NULL;

element* search(treePointer, int);
void insertBST(treePointer, int);
treePointer modifiedSearch(treePointer, int);
element* iterSearch(treePointer , int );
void inorder(treePointer);


int main() {
	int n, seed, k, i = 0;
	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf("%d", &n);
	printf("%s", "seed : ");
	scanf("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);
	

	int* arr = (int*)malloc(sizeof(int) * n);
	int flag = 0;
	printf("generating number : ");
	while(i<n) {
		flag = 0;
		k = rand() % 501;
		for (int j = 0; j < i; j++) {
			if (k == arr[j]) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			arr[i] = k;
			insertBST(&root, k);
			i++;
		}
	}
	printf("\nthe key to search : ");
	scanf("%d", &k);
	printf("the search process : ");
	if (iterSearch(root, k)) printf("\nthe element is in BST\n");
	else printf("\nthe element is not in BST\n");

	printf("\ninorder traversal of the BST shows the sorted sequence\n");
	inorder(root);

}

void inorder(treePointer tree)
{
	if (tree)
	{
		inorder(tree->leftChild);
		printf("%4d", tree->data.key);
		inorder(tree->rightChild);
	}
}

void insertBST(treePointer *node, int k) {
	treePointer tmp = modifiedSearch(*node, k);
	if (tmp || !(*node)) { //k가 없거나 node가 비었으면
		treePointer new = malloc(sizeof(node));
		new->data.key = k;
		new->leftChild = new->rightChild = NULL;
		if ((*node)) {
			if (k < tmp->data.key)
				tmp->leftChild = new;
			else tmp->rightChild = new;
		}
		else (*node) = new; //노드가 비었으면
		printf("%d ", k);
	}
}

treePointer modifiedSearch(treePointer root, int k)
{
	treePointer temp = root;
	while (root) {
		temp = root;
		if (k < root->data.key)
			root = root->leftChild;
		else if (k > root->data.key)
			root = root->rightChild;
		else
			return NULL;
	}
	return temp;
}

element* search(treePointer root, int k) {
	if (!root) 
		return NULL;
	if (k == root->data.key) 
		return &root->data;
	if (k < root->data.key) 
		return search(root->leftChild , k);
	return search(root->rightChild, k);
}

element* iterSearch(treePointer tree, int k){
	while (tree) {
		printf("%d => ", tree->data.key);

		if (k == tree->data.key) return &(tree->data);
		if (k < tree->data.key)
			tree = tree->leftChild;
		else
			tree = tree->rightChild;
	}
	return NULL;
}