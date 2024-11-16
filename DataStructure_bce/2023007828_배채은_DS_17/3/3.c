#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50


typedef struct graph {
	int vertex;
	struct graph* link;
}graph;

typedef struct graphType {
	int n;
	graph* adj_list[MAX_VERTICES];
}graphType;

typedef struct queue {
	int element[MAX_VERTICES];
	int front, rear;
	int size;
}queue;

int visited[MAX_VERTICES];
void printConnect(graphType* g);
void enqueue(queue* q, int item);
int dequeue(queue* q);
void dfs_list(graphType* g, int v);
void insert_edge(graphType* g, int u, int v);
void printList(graphType* g);


int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_num;
	int edge_num;
	int n, v;
	graphType* g;
	g = (graphType*)malloc(sizeof(graphType));
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adj_list[i] = NULL;
	}
	fscanf(fp, "%d %d", &vertex_num, &edge_num);
	for (int i = 0; i < vertex_num; i++) {
		g->n++;
	}
	while (fscanf(fp, "%d %d", &n, &v) == 2) {
		insert_edge(g, n, v);
		insert_edge(g, v, n);
	}
	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	printList(g);

	printf("<<<<<<<<<< Connected Components >>>>>>>>>>\n");
	printConnect(g);

	fclose(fp);
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

void dfs_list(graphType* g, int v) {
	graph* w;
	visited[v] = 1;
	printf("%d ", v);
	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			dfs_list(g, w->vertex);
		}
	}
}


void insert_edge(graphType* g, int u, int v) {
	graph* node = (graph*)malloc(sizeof(graph));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void printList(graphType* g) {
	for (int i = 0; i < g->n; i++) {
		graph* curNode;
		printf("graph[%d] : ", i);
		curNode = g->adj_list[i];
		while (curNode != NULL) {
			printf("%5d", curNode->vertex);
			curNode = curNode->link;
		}
		printf("\n");
	}
}

void printConnect(graphType* g) {
	int cnt = 1;
	for (int i = 0; i < g->n; i++) {
		if (!visited[i]) {
			printf("Connected Component %d : ", cnt);
			dfs_list(g, i);
			cnt++;
			printf("\n");
		}
	}
}



