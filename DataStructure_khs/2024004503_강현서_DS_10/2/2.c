#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
}node;

void dinsert(nodePointer node, int num);
void ddelete(nodePointer deleted);
void printListFrnt(nodePointer head);
void printListBack(nodePointer head);

void dinsert(nodePointer node, int num) {
	nodePointer newNode = NULL;
	newNode = (nodePointer)malloc(sizeof(*newNode));
	if (!newNode) return;
	newNode->data = num;
	newNode->llink = node;
	newNode->rlink = node->rlink;

	node->rlink->llink = newNode;
	node->rlink = newNode;
}

void ddelete(nodePointer deleted) {
	deleted->llink->rlink = deleted->rlink;
	deleted->rlink->llink = deleted->llink;
	free(deleted);
}

void printListFrnt(nodePointer head) {
	int cnt = 0;
	printf("forward\n");
	nodePointer temp = head->rlink;
	while (temp != head) {
		cnt++;
		printf("(%p %5d %p)   ",
			temp->llink, temp->data, temp->rlink);
		temp = temp->rlink;
		if (cnt % 4 == 0) printf("\n");
	} 
}

void printListBack(nodePointer head) {
	int cnt = 0;
	printf("backward\n");
	nodePointer temp = head->llink;
	while (temp != head) {
		cnt++;
		printf("(%p %5d %p)   ",
			temp->llink, temp->data, temp->rlink);
		temp = temp->llink;
		if (cnt % 4 == 0) printf("\n");
	}
}

int main() {
	FILE* fp;
	fp = fopen("input.txt", "r");
	int num = 0;
	nodePointer header = NULL;
	header = (nodePointer)malloc(sizeof(*header));
	if (!header) return 0;
	header->llink = header;
	header->rlink = header;

	// 이중연결환형리스트 만들기
	while (fscanf(fp, "%d ", &num) != EOF)
		dinsert(header->llink, num);

	// 이중연결환형리스트 앞뒤로 출력
	printf("After creating a doubly lnked circular list with a head node :\n");
	printListFrnt(header);
	printf("\n");
	printListBack(header);

	// 50 이하의 데이터 삭제
	nodePointer trail = header->rlink;
	while (trail != header) {			// 마지막 노드가 삭제되면 trail = head인 상태
		trail = trail->rlink;			// 다음으로 이동 (2번째 노드부터 시작)
		if (trail->llink->data <= 50)	// trail 이전의 data가 50이하면
			ddelete(trail->llink);		//  trail 이전노드 삭제
	}

	printf("\nAfter deleting numbers less than and equal to 50\n");
	printListFrnt(header);
	printf("\n");
	printListBack(header);
	printf("\n");

	// 전부 삭제
	trail = header->rlink;
	while (trail != header) {
		trail = trail->rlink;
		ddelete(trail->llink);
	}
	free(header);
}