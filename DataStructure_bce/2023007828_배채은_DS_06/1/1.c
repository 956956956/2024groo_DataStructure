#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element* queue;
int capacity = 2;
int front = 0, rear = 0;

void qprint() {
	int i = front + 1;
	while (1) {
		if (i >= capacity) {
			i = i % capacity;
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

void copy(element* a, element* b, element* c) {
	while (a != b)
		*c++ = *a++;
}

void queueFull() {
	int start;
	element * newQueue = (element*)malloc(2 * capacity * sizeof(*queue));
	start = (front + 1) % capacity;
	if (start < 2) {
		copy(queue + start, queue + start + capacity - 1, newQueue);
	}
	else {
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + front, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;

	printf("queue capacity is doubled,\ncurrent queue capacity is %d\n", capacity);
}

void add(element tmp) {
	rear = (rear + 1) % (capacity);
	if (rear == front) {
		queueFull();
		queue[++rear] = tmp;
		qprint();
		printf("\n");
	}
	else
		queue[rear] = tmp;
}

element delete() {
	if (front == rear) {
		printf("queue is empty, cannot delete element\n");
		exit(0);
	}
	front = (front + 1) % capacity;
	return queue[front];
}



int main() {
	FILE* fp = fopen("input.txt", "r");
	char com[20], trash[80];
	element tmp;
	queue = (element*)malloc((capacity) * sizeof(element));
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
			printf("end of program!!\n");
			exit(0);
		}
		else {
			printf("wrong command! try again!\n");
			fgets(trash, 50, fp);
		}
	}
	fclose(fp);
	

}