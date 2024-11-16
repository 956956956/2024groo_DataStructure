#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 20


typedef struct {
	int front, rear;
	int key[MAX_QUEUE_SIZE];
} QueueType;

int* list;
QueueType queue[MAX_QUEUE_SIZE];
void enqueue(QueueType* q, int item);
int dequeue(QueueType* q);
void radixSort(int list[], int digit, int n);
void init_queue(QueueType* q);
void printList(int list[], int n);

int main() {
	FILE* fp;
	int i, n, digit;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d %d", &digit, &n);
	list = malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		fscanf(fp, "%d", &list[i]);
	fclose(fp);

	printf("input data ---\n");
	for (i = 0; i < n; i++)
		fprintf(stdout, "%5d", list[i]);

	printf("\n");
	radixSort(list, digit, n);

	free(list);

}

void radixSort(int list[], int digit, int n) {
	int i, j, k, factor = 1;
	for (i = 0; i < digit; i++)
		init_queue(&queue[i]);

	for (i = 0; i < digit; i++) {
		printf("\nstep %d 자리 ---\n", i);
		for (j = 0; j < n; j++) {
			enqueue(&queue[(list[j] / factor) % 10], list[j]);
		}

		printf("\nQueue의 내용 ---\n");
		for (j = 0; j < n; j++) {
			printf("%5d", j);
		}
		printf("\n\n\n");
		for (k = digit; k > 0; k--) {
			for (j = 0; j < n; j++) {
				if (queue[j].key[(queue[j].front) + k] == 0) printf("%5s", "");
				else printf("%5d", queue[j].key[(queue[j].front) + k]);
			}
			printf("\n\n");
		}
		printf("-------------------------------------------------------\n");


		for (k = 0,j = 0; j < n; j++) {
			while (!isEmpty(&queue[j])) {
				list[k++] = dequeue(&queue[j]);
			}
		}

		factor *= 10;
		printList(list, n);
	}

	printf("\nresult ---\n");
	printList(list, n);
}

void printList(int list[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%5d", list[i]);
	}
	printf("\n");
}

void init_queue(QueueType* q) {
	int i;
	q->front = 0; q->rear = 0;
	for (i = 0; i < MAX_QUEUE_SIZE; i++) {
		q->key[i] = 0;
	}
}

void enqueue(QueueType* q, int item) {
	q->key[++q->rear] = item;
}

int dequeue(QueueType *q) {
	if (isEmpty(q)) {
		fprintf(stderr, "queue is empty\n");
		exit(EXIT_FAILURE);
	}
	return q->key[++q->front];
}

int isEmpty(QueueType* q) {
	if (q->front == q->rear) return 1;
	return 0;
}