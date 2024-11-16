#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 2
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;
element *queue;
int capacity = 2;
int front = 0, rear = 0;

void queueFull();
void add(int , char []);
void qprint();
void copy(element*, element*);
element delete();

void queueFull() {
	int nstart = capacity - front - 1;
	int qstart = (front + 1) % capacity;
	element* newQueue = (element*)malloc(2 * capacity * sizeof(element));
	copy(queue + qstart, queue + capacity, newQueue);
	if (nstart >= 2)
		copy(queue, queue + front, newQueue + nstart);
	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;
}

void copy(element* a, element*b, element*c) {
	while (a != b) {
		*c++ = *a++;
	}
}

void add(int id, char name[]) {
	rear = (rear + 1) % capacity;
	if (front == rear){
		queueFull();
		printf("queue capacity is doubled,\n current queue capacity is %d\n", capacity);
		queue[++rear].id = id;
		strcpy(queue[rear].name, name);
		qprint();
	}
	else {
		queue[rear].id = id;
		strcpy(queue[rear].name, name);
	}
}

void qprint() {
	int i = front;
	do{
		i = (i + 1) % capacity;
		printf("%d %s\n", queue[i].id, queue[i].name);
	} while (i != rear);
	printf("\n");
}

element delete() {
	front = (front + 1) % capacity;
	return queue[front];
}

int main() {
	char com[10], garbage[80], tmpName[MAX_NAME_SIZE];
	int tmpId;
	FILE* fp = fopen("input.txt", "r");
	queue = (element*)malloc(capacity * sizeof(element));
	while (!feof(fp)) {
		fscanf(fp, "%s", com);
		if (strcmp(com, "add") == 0) {
			fscanf(fp, "%d %s", &tmpId, tmpName);
			add(tmpId, tmpName);
		}
		else if (strcmp(com, "qprint") == 0) {
			qprint();
		}
		else if (strcmp(com, "delete") == 0) {
			if (front == rear) {
				printf("Queue empty\n");
				fclose(fp);
				exit(0);
			}
			delete();
		}
		else if (strcmp(com, "quit") == 0) {
			printf("end of program");
			fclose(fp);
			exit(0);
		}
		else {
			printf("wrong command\n");
			fgets(garbage, 80, fp);
		}
	}
}