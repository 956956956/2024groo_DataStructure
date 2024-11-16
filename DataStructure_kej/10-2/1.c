// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct vertex* vertexPointer;
typedef struct vertex {
	int data;
	int cost;
	vertexPointer link;
} vertex;

int edgeNum = 0, vertexNum;
int* parent;
vertexPointer* adjList;

void insertSorted(int i, int j, int cost);
void simpleUnion(int i, int j);
int simpleFind(int i);
void KruskalAlgorithm();

int main() {
	int i, j, input;
	FILE* fp = fopen("in.txt", "r");
	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	/* weighted undirected graph에 대한 adjacency matrix 입력 받기 */
	fscanf(fp, "%d", &vertexNum);
	adjList = (vertexPointer*)calloc(vertexNum, sizeof(vertexPointer));
	parent = (int*)calloc(vertexNum, sizeof(int));
	for (i = 0; i < vertexNum; i++)
		parent[i] = -1;

	for (i = 0; i < vertexNum; i++) {
		for (j = 0; j < vertexNum; j++) {
			fscanf(fp, "%d", &input);
			if (input != 0)
				insertSorted(i, j, input);
		}
	}

	fclose(fp);

	/* Kruskal's algorithm 적용하기 */
	printf("(edge):weight\n");
	KruskalAlgorithm();

	/* 동적할당된 메모리 해제하기 */
	for (i = 0; i < vertexNum; i++) {
		vertexPointer p = adjList[i];
		while (p != NULL) {
			vertexPointer temp = p;
			p = p->link;
			free(temp);
		}
	}
	free(adjList);
	free(parent);

	return 0;
}

/* cost값에 따라 오름차순으로 list를 연결하는 함수 */
void insertSorted(int i, int j, int cost) {
	vertexPointer p, q, curr;
	curr = (vertex*)calloc(1, sizeof(vertex));
	curr->data = j;
	curr->cost = cost;
	curr->link = NULL;

	p = adjList[i];
	q = adjList[i];

	while (p != NULL) {    // 위치 찾기
		if (p->cost > cost)
			break;
		q = p;
		p = p->link;
	}
	if (p == adjList[i]) {    // 첫 번째일 때
		curr->link = adjList[i];
		adjList[i] = curr;
	}
	else {    // 그렇지 않을 때
		curr->link = q->link;
		q->link = curr;
	}
}

/* Union 함수 */
void simpleUnion(int i, int j) {
	int iRoot = simpleFind(i);
	int jRoot = simpleFind(j);
	if (iRoot != jRoot)
		parent[jRoot] = iRoot;
}

/* Find 함수 */
int simpleFind(int i) {
	if (parent[i] == -1)
		return i;
	return simpleFind(parent[i]);
}

/* Kruskal Algorithm을 적용하는 함수 */
void KruskalAlgorithm() {
	int i, minCost;
	while (edgeNum < vertexNum - 1) {
		int minIndex = -1, data = -1;
		minCost = 1000;

		/* choose a least cost edge */
		for (i = 0; i < vertexNum; i++) {
			if (adjList[i] != NULL && adjList[i]->cost < minCost) {
				minIndex = i;
				data = adjList[i]->data;
				minCost = adjList[i]->cost;
			}
		}

		if (minIndex == -1)
			break;

		/* delete the edge*/
		adjList[minIndex] = adjList[minIndex]->link;

		/* if the edge does not crete a cycle */
		if (simpleFind(minIndex) != simpleFind(data)) {
			/* print and add to union */
			printf("(%d, %d): %d\n", minIndex, data, minCost);
			edgeNum++;
			simpleUnion(minIndex, data);
		}
	}
}

/*
GPT 돌리기 전 망한 내 코드.
void KruskalAlgorithm() {
	int i, minCost;
	while (edgeNum < vertexNum) {
		int minIndex, data, minCost;
		for (i = 0; i < vertexNum; i++) {
			if (adjList[i] != NULL) {
				minIndex = i;
				data = adjList[i]->data;
				minCost = adjList[i]->cost;
				break;
			}
		}

		for (i = 0; i < vertexNum; i++) {
			if (adjList[i]->cost < adjList[minIndex]->cost) {
			minIndex = i;
			data = adjList[i]->data;
			minCost = adjList[i]->cost;
		}
	}

	adjList[minIndex] = adjList[minIndex]->link;
	adjList[data] = adjList[data]->link;

	if (simpleFind(minIndex) != simpleFind(data)) {
		printf("(%d, %d): %d\n", minIndex, data, minCost);
		edgeNum++;
		simpleUnion(minIndex, data);
		}
	}
}
*/