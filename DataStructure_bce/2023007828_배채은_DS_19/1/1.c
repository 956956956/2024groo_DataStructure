#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 20
#define MAX_VERTICES 7
#define INF 999
#define TRUE 1
#define FALSE 0

void init();
void shortest_path(int start, int end);
int choose(int n);

int top = -1;
int stack[MAX_STACK_SIZE];
int path[MAX_VERTICES];
int weight[MAX_VERTICES][MAX_VERTICES];
int distance[MAX_VERTICES];
int found[MAX_VERTICES];


int main() {
	FILE* fp;
	int verN, edgeN;
	int v, u, w, i, n;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}

	init();
	fscanf(fp, "%d %d", &verN, &edgeN);
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &v, &u, &w);
		weight[v][u] = w;
		weight[u][v] = w;
	}

	shortest_path(0, verN);
	printf("\n");

	for (i = 1; i < verN; i++) {
		printf("distance[0-%d] = %-2d    : ", i, distance[i]);
		n = i;
		while (n) {
			stack[++top] = n;
			n = path[n];  // 0 4 1 2 - - 4
		}
		while (top > -1) {
			printf("<%d->%d> ", path[stack[top]], stack[top]);
			top--;
		}
		printf("\n");
	}
}



int choose(int n) {
	int i, min = INF, minpos = -1;
	for (i = 0; i < n; i++) {
		if (distance[i] < min && found[i] == FALSE) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}


void shortest_path(int start, int n) {
	int i, j, u, w;
	found[start] = TRUE;
	
	for (i = 0; i < n; i++) {
		distance[i] = weight[start][i];
	}

	printf("%d : ", 0);
	for (j = 0; j < n; j++) {
		printf("%5d", distance[j]);
	}
	printf("\n");

	for (i = 0; i < n - 1; i++) {
		u = choose(n);
		found[u] = TRUE;
		
		for (w = 1; w < n; w++) {
			if (found[w] == FALSE) {
				if (distance[u] + weight[u][w] < distance[w]) {
					distance[w] = distance[u] + weight[u][w];
					path[w] = u;
				}
			}
		}

		printf("%d : ", u);
		for (j = 0; j < n; j++) {
			printf("%5d", distance[j]);
		}
		printf("\n");
	}

}


void init() {
	int i, j;
	for (i = 0; i < MAX_VERTICES; i++) {
		for (j = 0; j < MAX_VERTICES; j++)
			weight[i][j] = INF;
		found[i] = FALSE;
	}
	for (i = 0; i < MAX_VERTICES; i++) {
		weight[i][i] = 0;
		path[i] = 0;
	}

}