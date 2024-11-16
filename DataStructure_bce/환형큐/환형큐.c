#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;
element queue[MAX_QUEUE_SIZE];
int rear=0, front=0;


void add(int id, char name[]) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		printf("queue is full, not added\n");
		rear--;
		if (rear < 0)
			rear += MAX_QUEUE_SIZE;
	}
	else {
		queue[rear].id = id;
		strcpy(queue[rear].name, name);
	}
}

void qprint() {
	int i = front;
	while (i!=rear) {
		i = (i+1) % MAX_QUEUE_SIZE;
		printf("%d %s\n", queue[i].id, queue[i].name);
	}

}

void delete() {
	if (front == rear) {
		printf("queue is empty\n");
		exit(0);
	}
	else {
		front = (front + 1) % MAX_QUEUE_SIZE;
	}
}

int main() {
	char com[10], garbage[80], tmpName[MAX_NAME_SIZE];
	int tmpId;
	FILE* fp = fopen("input.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%s", com);
		if (strcmp(com, "add") == 0) {
			fscanf(fp, "%d %s", &tmpId, tmpName);
			add(tmpId, tmpName);
		}
		else if (strcmp(com, "qprint")==0) {
			qprint();
		}
		else if (strcmp(com, "delete")==0) {
			delete();
		}
		else if (strcmp(com, "quit") == 0)
			exit(0);
		else {
			printf("wrong command\n");
			fgets(garbage, 80, fp);
		}
	}
}