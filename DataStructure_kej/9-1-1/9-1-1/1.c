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
			printf("%3d: ����\n", data);
		else
			printf("%3d: ����\n", data);
	}

	fclose(fp);
	return 0;
}

/* ���Ϸκ��� �Է¹��� ���ҵ��� �����Ͽ� binary search tree�� �����ϴ� �Լ� */
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

/* insert �Լ��� �ʿ��� ������ search �Լ� */
node* modifiedSearch(treePointer root, int item) {
	treePointer parent = NULL;
	while (root) {
		parent = root;

		// �̹� �ִ� ���� NULL ��ȯ
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

/* �̹� �ִ� ������� ã�� �Լ� */
int search(treePointer root, int item) {
	treePointer parent = NULL;
	while (root) {
		parent = root;

		// �̹� �ִ� ���� 1 ��ȯ
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

/* inorder traversal�� ����ϴ� �Լ� */
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
}