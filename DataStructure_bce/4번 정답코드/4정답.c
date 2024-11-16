#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char fruit[10];
	char coun[10];
	int price;
}element;
typedef struct node* nodepointer;

struct node {
	element data;
	nodepointer link;
};
typedef struct node node;

void finsert(nodepointer* a, element n);
void print(nodepointer a);
void reverse(nodepointer* a);
void search(nodepointer* a, char* c);
void expen(nodepointer* a, nodepointer* b);

int main() {
	element tmp;
	nodepointer first = NULL;
	nodepointer thous = NULL;
	char nn[20];
	FILE* fp;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	while ((fscanf(fp, "%s %s %d", tmp.fruit, tmp.coun, &tmp.price)) != EOF) {
		finsert(&first, tmp);
	}
	fclose(fp);
	printf("순방향 출력\nThe ordered list contains:\n");
	print(first);
	puts("\n");

	printf("나라이름을 입력하세요 : ");
	scanf("%s", nn);
	search(&first, nn);

	reverse(&first);
	printf("역방향 출력\nThe ordered list contains:\n");
	print(first);
	puts("\n");

	expen(&first, &thous);
	printf("1000 이상 과일 노드 연결 리스트\nThe ordered list contains:\n");
	print(thous);
	puts("");

	return;
}

void finsert(nodepointer* a, element n) {
	nodepointer newnode = malloc(sizeof(node));
	newnode->data = n;
	newnode->link = *a;
	(*a) = newnode;
}
void print(nodepointer a) {
	nodepointer nextnode = a;
	int cnt = 1;
	while (nextnode) {
		printf("%p(%s, %s, %4d, %p) => ", nextnode, nextnode->data.fruit, nextnode->data.coun, nextnode->data.price, nextnode->link);
		if (!(cnt % 2)) puts("");
		cnt++;
		nextnode = nextnode->link;
	}
	puts("");
}

void reverse(nodepointer* a) {
	nodepointer trail = NULL, mid = NULL, rear = *a;
	while (rear) {
		trail = mid;
		mid = rear;
		rear = rear->link;
		mid->link = trail;
	}
	*a = mid;
}

void search(nodepointer* a, char* c) {
	nodepointer nextnode = *a;
	while (nextnode) {
		if (!strcmp(nextnode->data.coun, c)) {
			printf("%s, ", nextnode->data.fruit);
		}
		nextnode = nextnode->link;
	}
	puts("\n");
}

void expen(nodepointer* a, nodepointer* b) {
	nodepointer nextnode = *a;
	nodepointer Node = NULL;
	nodepointer first = NULL;
	while (nextnode) {
		if (nextnode->data.price >= 1000) {
			if (!Node) {
				Node = nextnode;
				first = Node;
				nextnode = nextnode->link;
			}
			else {
				Node->link = nextnode;
				Node = Node->link;
				nextnode = nextnode->link;
			}
		}
		else nextnode = nextnode->link;
	}
	*b = first;
}