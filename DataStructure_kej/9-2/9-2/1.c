// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

/* ���� �����͸� �־�� ����ü */
typedef struct {
	int ver;
	int edg;
} Input;

/* linked adjacency list�� ���� vertex ����ü */
typedef struct vertex* vertexPointer;
typedef struct vertex {
	int data;
	vertexPointer link;
} vertex;

int count, index = 0;
int** G;
Input inputData[100];
vertexPointer* adjList, * inverseAdjList;

void adjacencyMatrix();
void adjacencyList();
void inverseAdjacencyList();
void countDegree(vertexPointer* list);
void printList(vertexPointer* list);

int main() {
	int i, j, vertex, edge;
	FILE* fp = fopen("in.txt", "r");
	if (!fp) {
		printf("Can't open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &count);

	while(!feof(fp)) {
		fscanf(fp, "%d %d", &vertex, &edge);
		inputData[index].ver = vertex;
		inputData[index].edg = edge;
		index++;
	}
	index--;

	/* (1) adjacency matrix G ���� �� ��� */
	printf("Adjacency matrix\n");
	adjacencyMatrix();

	/* (2) linked adjacency list ���� �� ��� */
	printf("\nLinked adjacency list\n");
	adjacencyList();

	/* (3) inverse adjacency list ���� �� ��� */
	printf("\n\nInverse adjacency list\n");
	inverseAdjacencyList();

	/* (4) �� vertex�� Indegree ��� */
	printf("\nIndegree\n");
	countDegree(inverseAdjList);

	/* (5) �� vertex�� Outdegree ��� */
	printf("\nOutdegree\n");
	countDegree(adjList);

	return 0;
}

/* (1) adjacency matrix G ���� �� ��� */
void adjacencyMatrix() {
	int i, j;

	G = (int**)calloc(count, sizeof(int*));
	for (i = 0; i < count; i++)
		G[i] = (int*)calloc(count, sizeof(int));

	for (i = 0; i < index; i++)
		G[inputData[i].ver][inputData[i].edg] = 1;

	for (i = 0; i < count; i++) {
		for (j = 0; j < count; j++)
			printf("%3d", G[i][j]);
		printf("\n");
	}

	for (i = 0; i < count; i++)
		free(G[i]);
	free(G);
	return;
}

/* (2) linked adjacency list ���� �� ��� */
void adjacencyList() {
	int i, j;
	vertex* curr;
	adjList = (vertexPointer*)calloc(count, sizeof(vertexPointer));

	for (i = 0; i < index; i++) {
		curr = (vertex*)malloc(1 * sizeof(vertex));
		curr->data = inputData[i].edg;
		curr->link = adjList[inputData[i].ver];
		adjList[inputData[i].ver] = curr;
	}

	printList(adjList);
}

/* (3) inverse adjacency list ���� �� ��� */
void inverseAdjacencyList() {
	int i, j;
	vertex* curr;
	inverseAdjList = (vertexPointer*)calloc(count, sizeof(vertexPointer));

	for (i = 0; i < index; i++) {
		curr = (vertex*)malloc(1 * sizeof(vertex));
		curr->data = inputData[i].ver;
		curr->link = inverseAdjList[inputData[i].edg];
		inverseAdjList[inputData[i].edg] = curr;
	}

	printList(inverseAdjList);
}

/* degree�� �����ִ� �Լ� */
void countDegree(vertexPointer* list) {
	int i, degree;
	vertex* p;

	for (i = 0; i < count; i++) {
		printf("[%2d]", i);
		p = list[i];
		degree = 0;
		while (p != NULL) {
			degree++;
			p = p->link;
		}
		printf("%3d\n", degree);
	}
}

/* ��� �迭���� list�� ���� ������ִ� �Լ� */
void printList(vertexPointer* list) {
	int i;
	vertex* p;

	for (i = 0; i < count; i++) {
		printf("[%2d]", i);
		p = list[i];
		while (p != NULL) {
			printf("%3d", p->data);
			p = p->link;
		}
		printf("\n");
	}
}