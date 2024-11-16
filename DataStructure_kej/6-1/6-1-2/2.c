// 2023012565 김은정
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
	printf("[오름차순 정렬]\n");
	printList(head);
	printf("\n");

	while (1) {
		printf("\n삭제할 노드 번호: ");
		scanf("%d", &data);

		if (data == -1)
			break;

		head = deleteNode(head, data);

		printList(head);
	}
	printf("종료");
	return 0;
}

/* 오름차순으로 정렬하는 함수 */
LINK insertSorted(LINK head, int data) {
	LINK node, p, q;

	node = (NODE*)malloc(sizeof(NODE));
	node->num = data;

	p = head;
	q = head;
	while (p != NULL) {    // 위치 찾기
		if (p->num > data)
			break;

		q = p;
		p = p->next;
	}

	if (p == head) {    // 가장 앞에 삽입하는 경우
		node->next = head;
		head = node;
	}
	else {    // 그렇지 않은 경우
		node->next = p;
		q->next = node;
	}
	return head;
}

/* 노드를 삭제하는 함수 */
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

	if (p == NULL) {	// 리스트에 없는 경우
		printf("%d가 리스트에 없음.\n", data);
		return head;
	}
	else if (p == head) {	// 가장 앞에 있는 노드의 경우
		head = head->next;
		free(p);
		return head;
	}
	else {	// 그렇지 않은 경우
		q->next = p->next;
		free(p);
		return head;
	}
}

/* 출력하는 함수 */
void printList(LINK head) {
	LINK nextnode = head;
	while (nextnode) {
		printf("%d ", nextnode->num);
		nextnode = nextnode->next;
	}
}