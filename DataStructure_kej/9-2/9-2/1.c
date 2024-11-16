// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

/* 파일 데이터를 넣어둘 구조체 */
typedef struct {
	int ver;
	int edg;
} Input;

/* linked adjacency list를 위한 vertex 구조체 */
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

	/* (1) adjacency matrix G 구성 및 출력 */
	printf("Adjacency matrix\n");
	adjacencyMatrix();

	/* (2) linked adjacency list 구성 및 출력 */
	printf("\nLinked adjacency list\n");
	adjacencyList();

	/* (3) inverse adjacency list 구성 및 출력 */
	printf("\n\nInverse adjacency list\n");
	inverseAdjacencyList();

	/* (4) 각 vertex별 Indegree 출력 */
	printf("\nIndegree\n");
	countDegree(inverseAdjList);

	/* (5) 각 vertex별 Outdegree 출력 */
	printf("\nOutdegree\n");
	countDegree(adjList);

	return 0;
}

/* (1) adjacency matrix G 구성 및 출력 */
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

/* (2) linked adjacency list 구성 및 출력 */
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

/* (3) inverse adjacency list 구성 및 출력 */
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

/* degree를 구해주는 함수 */
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

/* 헤더 배열별로 list를 따라 출력해주는 함수 */
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