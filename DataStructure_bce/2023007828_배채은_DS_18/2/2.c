#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define TRUE 1
#define FALSE 0
#define INF 1000L
#define MAX_VERTICES 7


typedef struct {
	int u; //vertex 1
	int v; //vertex 2
	int w; //weight value
}element;


int edgeNum;
int selected[MAX_SIZE];
int dist[MAX_SIZE];
int weight[MAX_SIZE][MAX_SIZE];

void prim(int s, int n);
int getMinVertex(int n);

int main() {
	FILE* fp;
	int i, j, u, v, w;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &edgeNum);

	for (i = 0; i < edgeNum; i++) {
		for (j = 0; j < edgeNum; j++) {
			if (i == j) weight[i][j] = 0;
			else weight[i][j] = INF;
		}
	}

	for (i = 0; i < edgeNum; i++) {
		fscanf(fp, "%d %d %d", &u, &v, &w);
		weight[u][v] = w;
		weight[v][u] = w;
	}

	prim(0, MAX_VERTICES);

	fclose(fp);
}



void prim(int s, int n) {
	int i, u, v, j, cost = 0, prev;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	dist[s] = 0;
	for (i = 0; i < n; i++) {
		u = getMinVertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		printf("선택 vertex : %d,    distance :", u);
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
		}

		for (j = 0; j < n; j++) {
			if (dist[j] == INF) printf("%5s", "INF");
			else printf("%5d", dist[j]);
		}

		if (i != 0) {
			printf("    선택 edge : (%d, %d) distance : %d", prev, u, dist[u]);
			cost += dist[u];
		}
		prev = u;
		puts("");
	}

	printf("최소 비용 : %d\n", cost);
}


int getMinVertex(int n) {
	int v = 0;
	for (int i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i;
	}
	return v;
}