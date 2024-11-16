// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// doubly linked circular list 구조
typedef struct node* nodePointer;
typedef struct node{
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;

// header node 선언
nodePointer headerNode;

// doubly linked circular list를 다루는 함수들
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

	// header node 생성
	headerNode = (nodePointer)malloc(1 * sizeof(node));
	headerNode->llink = NULL;
	headerNode->rlink = NULL;

	// 파일을 읽어 초기 doubly linked circular 생성
	fscanf(fp, "%d", &count);
	for (i = 0; i < count; i++) {
		fscanf(fp, "%d", &num);
		dinsert(num);
	}
	
	// 초기 doubly linked circular 출력
	printf("print list\n");
	dprint();
	printf("print inverse order\n");
	dprintInverse();

	// 숫자를 입력받아 node에 삽입
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

// 오름차순으로 node 연결
void dinsert(int num) {
	nodePointer newnode, node;
	newnode = (nodePointer)malloc(1 * sizeof(node));
	newnode->llink = NULL;
	newnode->data = num;
	newnode->rlink = NULL;

	if (headerNode->rlink == NULL) {	// 첫 번째 노드
		newnode->llink = headerNode;
		newnode->rlink = headerNode;
		headerNode->llink = newnode;
		headerNode->rlink = newnode;
	}
	else {	// 두 번째 노드부터
		node = headerNode->rlink;

		while (node->rlink != headerNode->rlink) {	// (오름차순으로) 삽입 위치 찾기
			if (node->data > num)
				break;
			node = node->rlink;
		}

		newnode->rlink = node;	// 노드 연결
		newnode->llink = node->llink;
		node->llink->rlink = newnode;
		node->llink = newnode;
	}
}

// 원 순서대로 출력
void dprint() {
	nodePointer p;
	p = headerNode->rlink;
	while (p->rlink != headerNode->rlink) {
		printf("[%2d] ", p->data);
		p = p->rlink;
	}
	printf("\n");
}

// 역순으로 출력
void dprintInverse() {
	nodePointer p;
	p = headerNode->llink;
	while (p->llink != headerNode->llink) {
		printf("[%2d] ", p->data);
		p = p->llink;
	}
	printf("\n");
}