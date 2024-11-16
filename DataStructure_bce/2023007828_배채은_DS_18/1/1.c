#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef struct {
	int u; //vertex 1
	int v; //vertex 2
	int w; //weight value
}element;


element edge_info[MAX_SIZE];
int* parent;
int edgeNum;

void sort_E(element*);
void kruskal(element*);
void simple_union(int i, int j);
void init();
int find(int i);

int main() {
	FILE* fp;
	int i;
	int n = 0, tmp;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &edgeNum);
	parent = malloc(sizeof(int) * edgeNum);
	init();

	for(i=0;i<edgeNum;i++){
		fscanf(fp, "%d %d %d", &edge_info[i].u, &edge_info[i].v, &edge_info[i].w);
		tmp = (edge_info[i].u > edge_info[i].v) ? edge_info[i].u : edge_info[i].v;
		n = (n > tmp) ? n : tmp;
	}
	sort_E(&edge_info);

	n++;
	kruskal(n);

	fclose(fp);
}

void kruskal(int n) {
	int e_accepted = 0, idx = 0;
	element e;
	int uset, vset, cost = 0;
	while (e_accepted<(n-1)) {
		e = edge_info[idx];
		uset = find(e.u);
		vset = find(e.v);
		if (uset != vset) {
			printf("(%d, %d) %d\n", e.u, e.v, e.w);
			e_accepted++;
			simple_union(uset, vset);
			cost += e.w;
		}
		idx++;
	}
	printf("\n최소비용 : %d", cost);
}


void sort_E(element* E) {
	int i, j;
	element tmp;
	for (i = 0; i < edgeNum; i++)
		for (j = i; j < edgeNum; j++) 
			if (E[i].w > E[j].w) {
				tmp = E[i];
				E[i] = E[j];
				E[j] = tmp;
			}
	return;
}

int find(int i) {
	for (; parent[i] != i; i = parent[i]);
	return i;
}

void simple_union(int i, int j) {
	parent[i] = j;
}

void init() {
	for (int i = 0; i < edgeNum; i++)
		parent[i] = i;
}