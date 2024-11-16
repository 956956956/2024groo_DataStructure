// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	struct node* next;
};

typedef struct node NODE;
typedef struct node* LINK;

LINK insertSorted(LINK head, int data);
LINK deleteNode(LINK head, int data);
void printList(LINK);

int main() {
	FILE* fp = fopen("list3.txt", "r");
	LINK head = NULL;
	int i, count, data;

	if (!fp) {
		puts("Cannot open the file");
		exit(1);
	}

	fscanf(fp, "%d", &count);
	for (i = 0; i < count; i++) {
		fscanf(fp, "%d", &data);
		head = insertSorted(head, data);
	}
	printf("[�������� ����]\n");
	printList(head);
	printf("\n");

	while (1) {
		printf("\n������ ��� ��ȣ: ");
		scanf("%d", &data);

		if (data == -1)
			break;

		head = deleteNode(head, data);

		printList(head);
	}
	printf("����");
	return 0;
}

/* ������������ �����ϴ� �Լ� */
LINK insertSorted(LINK head, int data) {
	LINK node, p, q;

	node = (NODE*)malloc(sizeof(NODE));
	node->num = data;

	p = head;
	q = head;
	while (p != NULL) {    // ��ġ ã��
		if (p->num > data)
			break;

		q = p;
		p = p->next;
	}

	if (p == head) {    // ���� �տ� �����ϴ� ���
		node->next = head;
		head = node;
	}
	else {    // �׷��� ���� ���
		node->next = p;
		q->next = node;
	}
	return head;
}

/* ��带 �����ϴ� �Լ� */
LINK deleteNode(LINK head, int data) {
	LINK p, q;

	p = head;
	q = head;
	while (p != NULL) {
		if (p->num == data)
			break;
		if (p->num > data)
			return head;
		q = p;
		p = p->next;
	}

	if (p == NULL) {	// ����Ʈ�� ���� ���
		printf("%d�� ����Ʈ�� ����.\n", data);
		return head;
	}
	else if (p == head) {	// ���� �տ� �ִ� ����� ���
		head = head->next;
		free(p);
		return head;
	}
	else {	// �׷��� ���� ���
		q->next = p->next;
		free(p);
		return head;
	}
}

/* ����ϴ� �Լ� */
void printList(LINK head) {
	LINK nextnode = head;
	while (nextnode) {
		printf("%d ", nextnode->num);
		nextnode = nextnode->next;
	}
}