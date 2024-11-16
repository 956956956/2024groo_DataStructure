#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef struct data {
	int class;
	int score;
} element;

typedef struct queue* queuePointer;
typedef struct queue {
	element* data;
	queuePointer link;
};
queuePointer front[MAX_QUEUE_SIZE];
queuePointer rear[MAX_QUEUE_SIZE];

void add(int, element*);
element* delete(int);
void qprint(int);

int main() {
	FILE* fp = fopen("input.txt", "r");
	int i, sNum;
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		front[i] = NULL;
	while (!feof(fp)) {
		element* item = (element*)malloc(sizeof(struct data));
		fscanf(fp, "%d %d %d", &sNum, &item->class, &item->score);
		add(sNum, item);
	}
	printf("과목번호, 학반, 성적\n");
	for (i = 0; i <= 2; i++)
		qprint(i);

}

void add(int i, element* item) {
	queuePointer tmp;
	tmp = (queuePointer)malloc(sizeof(struct queue));
	tmp->data = item;
	tmp->link = NULL;
	if (front[i])
		rear[i]->link = tmp;
	else
		front[i] = tmp;
	rear[i] = tmp;
}


element* delete(int i) {
	queuePointer tmp;
	element* item;
	tmp = front[i];
	item = front[i]->data;
	front[i] = front[i]->link;
	free(tmp);
	return item;
}


void qprint(int i) {
	printf("**************************\n");
	queuePointer p = front[i];
	while (p != rear[i]) {
		printf("%5d%5d%5d\n", i, p->data->class, p->data->score);
		p = p->link;
	}
	printf("%5d%5d%5d\n", i, p->data->class, p->data->score);
}


