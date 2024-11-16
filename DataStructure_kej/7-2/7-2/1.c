// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// doubly linked circular list ����
typedef struct node* nodePointer;
typedef struct node{
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;

// header node ����
nodePointer headerNode;

// doubly linked circular list�� �ٷ�� �Լ���
void dinsert(int num);
void dprint();
void dprintInverse();

int main() {
	FILE* fp = fopen("in.txt", "r");
	int i, count, num;
	if (!fp) {
		puts("Cannot open the file.");
		exit(1);
	}

	// header node ����
	headerNode = (nodePointer)malloc(1 * sizeof(node));
	headerNode->llink = NULL;
	headerNode->rlink = NULL;

	// ������ �о� �ʱ� doubly linked circular ����
	fscanf(fp, "%d", &count);
	for (i = 0; i < count; i++) {
		fscanf(fp, "%d", &num);
		dinsert(num);
	}
	
	// �ʱ� doubly linked circular ���
	printf("print list\n");
	dprint();
	printf("print inverse order\n");
	dprintInverse();

	// ���ڸ� �Է¹޾� node�� ����
	while (1) {
		printf("\nInput number: ");
		scanf("%d", &num);

		if (num == -1) {
			printf("Quit");
			break;
		}
		dinsert(num);

		printf("print list(%d inserted)\n", num);
		dprint();
		printf("print inverse order\n");
		dprintInverse();
	}

	fclose(fp);
	free(headerNode);
	return 0;
}

// ������������ node ����
void dinsert(int num) {
	nodePointer newnode, node;
	newnode = (nodePointer)malloc(1 * sizeof(node));
	newnode->llink = NULL;
	newnode->data = num;
	newnode->rlink = NULL;

	if (headerNode->rlink == NULL) {	// ù ��° ���
		newnode->llink = headerNode;
		newnode->rlink = headerNode;
		headerNode->llink = newnode;
		headerNode->rlink = newnode;
	}
	else {	// �� ��° ������
		node = headerNode->rlink;

		while (node->rlink != headerNode->rlink) {	// (������������) ���� ��ġ ã��
			if (node->data > num)
				break;
			node = node->rlink;
		}

		newnode->rlink = node;	// ��� ����
		newnode->llink = node->llink;
		node->llink->rlink = newnode;
		node->llink = newnode;
	}
}

// �� ������� ���
void dprint() {
	nodePointer p;
	p = headerNode->rlink;
	while (p->rlink != headerNode->rlink) {
		printf("[%2d] ", p->data);
		p = p->rlink;
	}
	printf("\n");
}

// �������� ���
void dprintInverse() {
	nodePointer p;
	p = headerNode->llink;
	while (p->llink != headerNode->llink) {
		printf("[%2d] ", p->data);
		p = p->llink;
	}
	printf("\n");
}