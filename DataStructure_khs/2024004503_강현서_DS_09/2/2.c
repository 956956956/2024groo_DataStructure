#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 3

typedef struct {
	int sub;
	int year;
	int score;
}element;

typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
}queue;

queuePointer front[MAX_QUEUE], rear[MAX_QUEUE];

void addq(int i, element item);
element deleteq(int i);
void printq(int i);

void addq(int i, element item) {
	queuePointer temp;
	temp = (queuePointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (front[i])
		rear[i]->link = temp;
	else
		front[i] = temp;
	rear[i] = temp;
}

element deleteq(int i) {
	element item = { -1, -1, -1 };
	queuePointer temp = front[i];
	if (!temp)
		return item;
	item = temp->data;
	front[i] = temp->link;
	free(temp);
	
	return item;
}

void printq(int i) {
	element item;
	printf("********************\n");

	while (front[i]) {
		item = deleteq(i);
		printf("%8d %5d %5d\n", item.sub, item.year, item.score);
	}
}

int main() {
	element item;
	FILE* fp;
	fp = fopen("input.txt", "r");

	for (int i = 0; i < MAX_QUEUE; i++)
		front[i] = NULL;

	while (fscanf(fp, "%d %d %d", &item.sub, &item.year, &item.score) != EOF)
		addq(item.sub, item);

	fclose(fp);

	printf("과목번호, 학년, 성적\n");

	for (int i = 0; i < MAX_QUEUE; i++)
		printq(i);
}