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

void printList(LINK);

int main() {
	FILE* fp = fopen("list2.txt", "r");
	LINK head = NULL, cur;
	int i, count, data;

	if (!fp) {
		puts("Cannot open the file");
		exit(1);
	}

	fscanf(fp, "%d", &count);
	for (i = 0; i < count; i++) {
		fscanf(fp, "%d", &data);

		// 맨 앞에 바로 삽입
		cur = (NODE*)malloc(sizeof(NODE));
		cur->num = data;
		cur->next = head;
		head = cur;
	}
	printList(head);
	return 0;
}

/* 노드 출력하는 함수 */
void printList(LINK head) {
	LINK nextnode = head;
	while (nextnode) {
		printf("%d ", nextnode->num);
		nextnode = nextnode->next;
	}
}