#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 20

typedef struct node* nodePointer;
typedef struct node{
	char fruit[MAX_NAME_SIZE];
	char country[MAX_NAME_SIZE];
	int price;
	nodePointer link;
} node;

nodePointer head = NULL;

nodePointer insertHead(nodePointer head, nodePointer new) {
	new->link = head;
	head = new;
	return head;
}

nodePointer insertBack(nodePointer head, nodePointer new) {
	if (!head)
		head = new;
	else {
		nodePointer p = head;
		while (p->link!=NULL)
			p = p->link;
		p->link = new;
	}
	return head;
}

void printList(nodePointer head) {
	nodePointer p = head;
	while (p) {
		printf("(%p %s, %s, %4d %p)  ", p, p->fruit, p->country, p->price, p->link);
		p = p->link;
	}
	printf("\n\n");
	return;
}

void search(nodePointer head, char* coun) {
	nodePointer p = head;
	while (p) {
		if (strcmp(p->country, coun) == 0) {
			printf("%s ", p->fruit);
		}
		p = p->link;
	}
	printf("\n");
	return;
}

nodePointer reverse(nodePointer head) {
	nodePointer trail = NULL, mid = NULL, rear = head;
	while (rear) {
		trail = mid;
		mid = rear;
		rear = rear->link;
		mid->link = trail;
	}
	return mid;

}

nodePointer moreThanThousand(nodePointer head) {
	nodePointer prev = NULL, p = head;
	while (p) {
		if (p->price < 1000) {
			if (p == head) {
				head = head->link;
				free(p);
				p = head;
				prev = NULL;
				continue;
			}
			else {
				prev->link = p->link;
				free(p);
				p = prev->link;
				continue;
			}
		}
		prev = p;
		p = p->link;
	}
	return head;
}

int main() {
	FILE* fp;
	char coun[MAX_NAME_SIZE];
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	while (!feof(fp)) {
		nodePointer new = (nodePointer)malloc(sizeof(struct node));
		fscanf(fp, "%s %s %d", new->fruit, new->country, &new->price);
		new->link = NULL;
		head = insertHead(head, new);
	}
	printf("순방향 출력: \n");
	printList(head);

	printf("탐색할 나라 이름: ");
	scanf("%s", coun);
	search(head, &coun);

	head = reverse(head);
	printf("역방향 출력: \n");
	printList(head);

	printf("100이상 과일 노드 출력:\n");
	head = moreThanThousand(head);
	printList(head);

}