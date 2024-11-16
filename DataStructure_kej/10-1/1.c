// 2023012565 ������
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

	/* undirected graph�� ���� adjacency matrix �Է� �ޱ� */
	fscanf(fp, "%d", &nodeNum);
	visited = (int*)calloc(nodeNum, sizeof(int));	// visited 0���� ����
	input = (int**)malloc(nodeNum * sizeof(int*));
	for (i = 0; i < nodeNum; i++)
		input[i] = (int*)malloc(nodeNum * sizeof(int));
	for (i = 0; i < nodeNum; i++) {
		for (j = 0; j < nodeNum; j++)
			fscanf(fp, "%d", &input[i][j]);
	}

	/* (1) DFS, BFS�� ��� ��� */
	printf("[DFS]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		dfs(inputNumber);
	}

	for (i = 0; i < nodeNum; i++)	// visited 0���� ����
		visited[i] = 0;

	printf("[BFS]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		bfs(inputNumber);
	}

	/* (2) DFS�� BFS�� ����� connected component ��� */
	for (i = 0; i < nodeNum; i++)	// visited 0���� ����
		visited[i] = 0;

	printf("\n[DFS Component]\n");
	for (i = 0; i < nodeNum; i++) {
		if (!visited[i]) {
			printf("Component %d:", i);
			dfs(i);
			printf("\n");
		}
	}

	for (i = 0; i < nodeNum; i++)	// visited 0���� ����
		visited[i] = 0;

	printf("[BFS Component]\n");
	for (i = 0; i < nodeNum; i++) {
		if (!visited[i]) {
			printf("Component %d:", i);
			bfs(i);
			printf("\n");
		}
	}

	/* (3) vertex ��ȣ�� ��������� �� DFS/BFS spanning tree ��� */
	for (i = 0; i < nodeNum; i++)	// visited 0���� ����
		visited[i] = 0;

	printf("\n[DFS Spanning Tree]");
	while (1) {
		printf("\nInput starting number: ");
		scanf("%d", &inputNumber);
		if (inputNumber == -1)
			break;
		dfsSpanningTree(inputNumber);
	}

	for (i = 0; i < nodeNum; i++)	// visited 0���� ����
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

/* dfs�� ���ϴ� �Լ� */
void dfs(int node) {
	visited[node] = 1;	// �湮 ��, 1�� ����
	printf("%3d", node);
	for (int i = 0; i < nodeNum; i++) {
		if (input[node][i] == 1 && !visited[i])
			dfs(i);
	}
}

/* bfs�� ���ϴ� �Լ� */
void bfs(int node) {
	printf("%3d", node);
	visited[node] = 1;	// �湮 ��, 1�� ����
	addQ(node);
	while (front < rear) {
		node = deleteQ();
		for (int i = 0; i < nodeNum; i++) {
			if (input[node][i] == 1 && !visited[i]) {
				printf("%3d", i);
				addQ(i);
				visited[i] = 1;	// �湮 ��, 1�� ����
			}
		}
	}
}

/* dfs spanning tree�� ���ϴ� �Լ� */
void dfsSpanningTree(int node) {
	visited[node] = 1;	// �湮 ��, 1�� ����
	for (int i = 0; i < nodeNum; i++) {
		if (input[node][i] == 1 && !visited[i]) {
			printf("(%d, %d) ", node, i);
			dfsSpanningTree(i);
		}
	}
}

/* bfs spanning tree�� ���ϴ� �Լ� */
void bfsSpanningTree(int node) {
	visited[node] = 1;	// �湮 ��, 1�� ����
	addQ(node);
	while (front < rear) {
		node = deleteQ();
		for (int i = 0; i < nodeNum; i++) {
			if (input[node][i] == 1 && !visited[i]) {
				printf("(%d, %d) ", node, i);
				addQ(i);
				visited[i] = 1;	// �湮 ��, 1�� ����
			}
		}
	}
}

/* bfs ���� �� ���� Queue ���� �Լ� */
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