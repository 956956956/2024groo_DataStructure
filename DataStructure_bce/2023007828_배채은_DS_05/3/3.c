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
int front = 0, rear = 0;

void qprint() {
	int i = front + 1;
	while(1){
		if (i >= MAX_QUEUE_SIZE) {
			i = i % MAX_QUEUE_SIZE;
		}
		if (i == rear) {
			printf("%d %s\n", queue[i].id, queue[i].name);
			break;
		}
		
		printf("%d %s\n", queue[i].id, queue[i].name);
		i++;
	}
	printf("\n");
}



void add(element item) {
	int back = rear;
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		printf("queue is full, not added\n");
		rear = back;
		return;
	}
	queue[rear] = item;
}

element delete() {
	if (front == rear) {
		printf("queue is empty, cannot delete element\n");
		exit(0);
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	char com[5], trash[80];
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
			printf("wrong command! try again!\n");
			fgets(trash, 50, fp);
		}
	}
}
