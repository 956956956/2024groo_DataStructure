#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20


typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;

void qprint() {
	for (int i = front + 1; i <= rear; i++) {
		printf("%d %s\n", queue[i].id, queue[i].name);
	}
	printf("\n\n");
}



void add(element item) {
	if (rear == MAX_QUEUE_SIZE - 1) {
		if(front == -1)
			printf("queue is full, not added\n");
		else {
			printf("data shift\n");
			int offset = front + 1;
			for (int i = front + 1; i < MAX_QUEUE_SIZE; i++) {
				queue[i - offset] = queue[i];
			}
			front = front - offset;
			rear = rear - offset;
			queue[++rear] = item;
		}
	}
	else {
		queue[++rear] = item;
	}
}

element delete() {
	if (front == rear) {
		printf("queue is empty, cannot delete element\n");
		exit(0);
	}
	return queue[++front];
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	char com[5],trash[80];
	element tmp;
	while (!feof(fp)) {
		fscanf(fp, "%s", com);
		if (strcmp(com, "add") == 0) {
			fscanf(fp, "%d %s", &tmp.id, tmp.name);
			add(tmp);
		}
		else if (strcmp(com, "delete") == 0) {
			delete();
		}
		else if (strcmp(com, "qprint") == 0) {
			qprint();
		}
		else if (strcmp(com, "quit") == 0) {
			exit(0);
		}
		else {
			printf("wrong command! try again!\n\n");
			fgets(trash, 50, fp);
		}
	}
}