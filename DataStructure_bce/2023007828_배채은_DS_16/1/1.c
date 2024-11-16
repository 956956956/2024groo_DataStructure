#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct graph* graphPointer;
typedef struct graph {
	int data;
	graphPointer link;
} graph;

graphPointer* list;

void insertHead(graphPointer*);
void printAdj(graphPointer*, int);

int main() {
	int vertex, edge, tmpv, tmpe;
	FILE* fp = fopen("input.txt", "r");
	char listType;
	fscanf(fp, "%c %d %d", &listType, &vertex, &edge);
	list = malloc(sizeof(graph) * vertex);
	for (int i = 0; i < vertex; i++)
		list[i] = NULL;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &tmpv, &tmpe);
		if (listType == 'u') {
			insertHead(&list[tmpv], tmpe);
			insertHead(&list[tmpe], tmpv);
		}
		else {
			insertHead(&list[tmpv], tmpe);
		}
	}
	printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>\n");
	for (int i = 0; i < vertex; i++)
		printAdj(&list[i], i);
}

void printAdj(graphPointer* first, int i) {
	graphPointer node = *first;
	printf("adjList[%d] :", i);
	while (node) {
		printf("%4d", node->data);
		node = node->link;
	}
	printf("\n");

}

void insertHead(graphPointer* head, int data) {
	graphPointer new = malloc(sizeof(graph));
	new->data = data;
	new->link = *head;
	*head = new;
}
