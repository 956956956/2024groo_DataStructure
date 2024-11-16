#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAX_VERTICES 20
#define TRUE 1
#define FALSE 0

typedef struct node* listPointer;
typedef struct node {
	int data;
	listPointer link;
} node;

listPointer* adjList;
void printAdj(listPointer* first, int i);
void insertHead(listPointer* head, int data);
void dfs(int v);
short int visited[MAX_VERTICES] = { FALSE };


int main() {
	int vertex, edge, v1, v2;
	int i, j, idx;
	listPointer tmp;

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	adjList = malloc(sizeof(node) * vertex);

	for (i = 0; i < vertex; i++)
		adjList[i] = NULL;

	for (i = 0; i < edge; i++) {
		fscanf(fp, "%d %d", &v1, &v2);
		insertHead(&adjList[v1], v2);
		insertHead(&adjList[v2], v1);
	}

	printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>\n");
	for (int i = 0; i < vertex; i++)
		printAdj(&adjList[i], i);
	
	printf("\n<<<<<<<<<<<<< Depth First Search >>>>>>>>>>>>");
	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < MAX_VERTICES; j++)
			visited[j] = 0;
		printf("\ndfs<%d> : ", i);
		dfs(i);
	}

}

void dfs(int v) {
	listPointer p;
	visited[v] = TRUE;
	printf("%5d", v);
	for (p = adjList[v]; p; p = p->link)
		if (!visited[p->data])
			dfs(p->data);
}

void printAdj(listPointer* first, int i) {
	listPointer node = *first;
	printf("graph[%d] :", i);
	while (node) {
		printf("%4d", node->data);
		node = node->link;
	}
	printf("\n");

}

void insertHead(listPointer* head, int data) {
	listPointer new = malloc(sizeof(node));
	new->data = data;
	new->link = *head;
	*head = new;
}