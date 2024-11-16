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
int rear = -1, front = -1;


void add(int id, char name[]) {
	if (rear == MAX_QUEUE_SIZE -1) {
		if (front == -1)
			printf("queue is full, not added\n");
		else {
			int i, j;
			printf("data shift\n");
			for (i=front+1, j=0; i<=rear;i++,j++ ) {
				queue[j] = queue[i];
			}
			front = -1; rear = j - 1;
			queue[++rear].id = id;
			strcpy(queue[rear].name, name);
		}
	}
	else {
		queue[++rear].id = id;
		strcpy(queue[rear].name, name);
	}
}

void qprint() {
	for(int i=front + 1;i<=rear;i++)
		printf("%d %s\n", queue[i].id, queue[i].name);

}

element delete() {
	if (front == rear) {
		printf("queue is empty\n");
		exit(0);
	}
	else {
		return queue[++front];
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
		else if (strcmp(com, "qprint") == 0) {
			qprint();
			printf("\n");
		}
		else if (strcmp(com, "delete") == 0) {
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