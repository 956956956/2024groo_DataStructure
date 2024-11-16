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

void insert(int item);
node* modifiedSearch(treePointer root, int item);
int search(treePointer root, int item);
void inorder(treePointer ptr);
treePointer deletion(treePointer root, int item);
treePointer minValueNode(treePointer node);

int main() {
	int num, i, data;
	FILE* fp = fopen("in.txt", "r");

	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &num);
	for (i = 0; i < num; i++) {
		fscanf(fp, "%d", &data);
		insert(data);
	}

	printf("[Inorder traversal]\n");
	inorder(root);
	printf("\n\n");
	fclose(fp);

	fp = fopen("search.txt", "r");

	fscanf(fp, "%d", &num);
	for (i = 0; i < num; i++) {
		fscanf(fp, "%d", &data);
		if (search(root, data) == 1)
			printf("%5d: ����\n", data);
		else
			printf("%5d: ����\n", data);
	}
	
	fclose(fp);

	while (1) {
		printf("\n>> ������ ���: ");
		scanf("%d", &data);
		if (data == -1)
			break;
		root = deletion(root, data);
		inorder(root);
	}
	printf("Quit.");
	return 0;
}

void insert(int item) {
	treePointer ptr, temp = modifiedSearch(root, item);
	if (temp || !root) {
		ptr = (node*)malloc(1 * sizeof(node));
		ptr->data = item;
		ptr->leftChild = NULL;
		ptr->rightChild = NULL;

		if (root) {
			if (item < temp->data)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
			root = ptr;
	}
}

node* modifiedSearch(treePointer root, int item) {
	treePointer parent = NULL;
	while (root) {
		parent = root;

		if (item == root->data)
			return NULL;

		if (item < root->data) {
			root = root->leftChild;
		}
		else {
			root = root->rightChild;
		}
	}
	return parent;
}

int search(treePointer root, int item) {
	treePointer parent = NULL;
	while (root) {
		parent = root;

		if (item == root->data)
			return 1;

		if (item < root->data) {
			root = root->leftChild;
		}
		else {
			root = root->rightChild;
		}
	}
	return 0;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf(" %d", ptr->data);
		inorder(ptr->rightChild);
	}
}

/* ǥ���Է����� ���� ��ȣ�� ��带 �����ϴ� �Լ� */
treePointer deletion(treePointer root, int key) {
	if (root == NULL) return root;

	if (key < root->data)	// ��� ã��
		root->leftChild = deletion(root->leftChild, key);
	else if (key > root->data)	// ��� ã��
		root->rightChild = deletion(root->rightChild, key);
	else {	// ��� ã�� ��
		// �� ���̶� child ��尡 NULL�� ���
		if (root->leftChild == NULL) {
			treePointer temp = root->rightChild;
			free(root);
			return temp;
		}
		else if (root->rightChild == NULL) {
			treePointer temp = root->leftChild;
			free(root);
			return temp;
		}
		// ���� child ��尡 ��� �ִ� ���
		treePointer temp = minValueNode(root->rightChild);
		root->data = temp->data;
		root->rightChild = deletion(root->rightChild, temp->data);
	}
	return root;
}

/* right subtree���� �ּڰ��� ã���ִ� �Լ� */
treePointer minValueNode(treePointer node) {
	treePointer current = node;

	while (current && current->leftChild != NULL)
		current = current->leftChild;

	return current;
}
