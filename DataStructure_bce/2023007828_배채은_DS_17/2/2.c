#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAX_VERTICES 20
#define TRUE 1
#define FALSE 0

typedef struct node* listPointer;
typedef struct node {
	int vertex;
	listPointer link;
} node;

typedef struct queue {
	int element[MAX_VERTICES];
	int front, rear;
	int size;
}queue;

listPointer* graph;
void printAdj(listPointer* first, int i);
void insertHead(listPointer* head, int vertex);
void bfs(int v);
void enqueue(queue* q, int item);
int dequeue(queue* q);
short int visited[MAX_VERTICES] = { FALSE };


int main() {
	int vertex, edge, v1, v2;
	int i, j, idx;
	listPointer tmp;

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	graph = malloc(sizeof(node) * vertex);

	for (i = 0; i < vertex; i++)
 		graph[i] = NULL;

	for (i = 0; i < edge; i++) {
		fscanf(fp, "%d %d", &v1, &v2);
		insertHead(&graph[v1], v2);
		insertHead(&graph[v2], v1);
	}

	printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>\n");
	for (int i = 0; i < vertex; i++)
		printAdj(&graph[i], i);
	
	printf("\n<<<<<<<<<<<<< Breadth First Search >>>>>>>>>>>>");
	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < MAX_VERTICES; j++)
			visited[j] = 0;
		printf("\nbfs<%d> : ", i);
		bfs(i);
	}

}

void bfs(int v) {
	listPointer w;
	queue q;
	for (int i = 0; i < MAX_VERTICES; i++) {
		q.element[i] = 0;
	}
	q.front = -1;
	q.rear = -1;
	q.size = 0;
	printf("%5d", v);
	visited[v] = TRUE;
	enqueue(&q, v);
	while (q.size !=0) {
		v = dequeue(&q);
		for (w = graph[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = TRUE;
				printf("%5d", w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}

void enqueue(queue* q, int item) {
	q->element[++q->rear] = item;
	q->size++;
}

int dequeue(queue* q) {
	int item;
	item = q->element[++(q->front)];
	q->size--;
	return item;
}

void printAdj(listPointer* first, int i) {
	listPointer node = *first;
	printf("graph[%d] :", i);
	while (node) {
		printf("%4d", node->vertex);
		node = node->link;
	}
	printf("\n");

}

void insertHead(listPointer* head, int vertex) {
	listPointer new = malloc(sizeof(node));
	new->vertex = vertex;
	new->link = *head;
	*head = new;
}