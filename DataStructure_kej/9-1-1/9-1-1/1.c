// 2023012565 김은정
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
			printf("%3d: 있음\n", data);
		else
			printf("%3d: 없음\n", data);
	}

	fclose(fp);
	return 0;
}

/* 파일로부터 입력받은 원소들을 삽입하여 binary search tree를 구성하는 함수 */
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

/* insert 함수에 필요한 수정된 search 함수 */
node* modifiedSearch(treePointer root, int item) {
	treePointer parent = NULL;
	while (root) {
		parent = root;

		// 이미 있는 노드면 NULL 반환
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

/* 이미 있는 노드인지 찾는 함수 */
int search(treePointer root, int item) {
	treePointer parent = NULL;
	while (root) {
		parent = root;

		// 이미 있는 노드면 1 반환
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

/* inorder traversal로 출력하는 함수 */
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
}