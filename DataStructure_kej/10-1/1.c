// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

int nodeNum;
int* visited;
int** input;

int Queue[100];
int front = -1, rear = -1;

void dfs(int node);
void bfs(int node);
void dfsSpanningTree(int node);
void bfsSpanningTree(int node);
void addQ(int n);
int deleteQ();

int main() {
	int i, j, inputNumber;
	FILE* fp = fopen("in.txt", "r");
	if (!fp) {
		printf("Cannot opne the file.");
		exit(1);
	}

	/* undirected graph에 대한 adjacency matrix 입력 받기 */
	fscanf(fp, "%d", &nodeNum);
	visited = (int*)calloc(nodeNum, sizeof(int));	// visited 0으로 설정
	input = (int**)malloc(nodeNum * sizeof(int*));
	for (i = 0; i < nodeNum; i++)
		input[i] = (int*)malloc(nodeNum * sizeof(int));
	for (i = 0; i < nodeNum; i++) {
		for (j = 0; j < nodeNum; j++)
			fscanf(fp, "%d", &input[i][j]);
	}

	/* (1) DFS, BFS한 결과 출력 */
	printf("[DFS]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		dfs(inputNumber);
	}

	for (i = 0; i < nodeNum; i++)	// visited 0으로 설정
		visited[i] = 0;

	printf("[BFS]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		bfs(inputNumber);
	}

	/* (2) DFS와 BFS에 기반한 connected component 출력 */
	for (i = 0; i < nodeNum; i++)	// visited 0으로 설정
		visited[i] = 0;

	printf("\n[DFS Component]\n");
	for (i = 0; i < nodeNum; i++) {
		if (!visited[i]) {
			printf("Component %d:", i);
			dfs(i);
			printf("\n");
		}
	}

	for (i = 0; i < nodeNum; i++)	// visited 0으로 설정
		visited[i] = 0;

	printf("[BFS Component]\n");
	for (i = 0; i < nodeNum; i++) {
		if (!visited[i]) {
			printf("Component %d:", i);
			bfs(i);
			printf("\n");
		}
	}

	/* (3) vertex 번호를 출발점으로 한 DFS/BFS spanning tree 출력 */
	for (i = 0; i < nodeNum; i++)	// visited 0으로 설정
		visited[i] = 0;

	printf("\n[DFS Spanning Tree]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		dfsSpanningTree(inputNumber);
	}

	for (i = 0; i < nodeNum; i++)	// visited 0으로 설정
		visited[i] = 0;

	printf("[BFS Spanning Tree]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		bfsSpanningTree(inputNumber);
	}

	free(visited);
	for (i = 0; i < nodeNum; i++)
		free(input[i]);
	free(input);
	return 0;
}

/* dfs를 구하는 함수 */
void dfs(int node) {
	visited[node] = 1;	// 방문 시, 1로 설정
	printf("%3d", node);
	for (int i = 0; i < nodeNum; i++) {
		if (input[node][i] == 1 && !visited[i])
			dfs(i);
	}
}

/* bfs를 구하는 함수 */
void bfs(int node) {
	printf("%3d", node);
	visited[node] = 1;	// 방문 시, 1로 설정
	addQ(node);
	while (front < rear) {
		node = deleteQ();
		for (int i = 0; i < nodeNum; i++) {
			if (input[node][i] == 1 && !visited[i]) {
				printf("%3d", i);
				addQ(i);
				visited[i] = 1;	// 방문 시, 1로 설정
			}
		}
	}
}

/* dfs spanning tree를 구하는 함수 */
void dfsSpanningTree(int node) {
	visited[node] = 1;	// 방문 시, 1로 설정
	for (int i = 0; i < nodeNum; i++) {
		if (input[node][i] == 1 && !visited[i]) {
			printf("(%d, %d) ", node, i);
			dfsSpanningTree(i);
		}
	}
}

/* bfs spanning tree를 구하는 함수 */
void bfsSpanningTree(int node) {
	visited[node] = 1;	// 방문 시, 1로 설정
	addQ(node);
	while (front < rear) {
		node = deleteQ();
		for (int i = 0; i < nodeNum; i++) {
			if (input[node][i] == 1 && !visited[i]) {
				printf("(%d, %d) ", node, i);
				addQ(i);
				visited[i] = 1;	// 방문 시, 1로 설정
			}
		}
	}
}

/* bfs 구할 때 쓰는 Queue 관련 함수 */
void addQ(int n) {
	if (rear == 99) {
		printf("Queue is full.\n");
		return;
	}
	Queue[++rear] = n;
}

int deleteQ() {
	if (front == rear)
		return -1;
	return Queue[++front];
}