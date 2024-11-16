#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct node* listPointer;
typedef struct node {
	int m;
	int vertex1, vertex2;
	listPointer link1, link2;
} node;

listPointer* adjList;
listPointer nod;


int main() {
	int vertex, edge, v1, v2;
	int i, j, idx;
	listPointer tmp;

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	adjList = malloc(sizeof(node) * vertex);
	nod = malloc(sizeof(node) * edge);

	for (i = 0; i < vertex; i++)
		adjList[i] = NULL;

	for(i=0;i<edge;i++){
		fscanf(fp, "%d %d", &v1, &v2);
		nod[i].vertex1 = v1;
		nod[i].vertex2 = v2;
		nod[i].link1 = nod[i].link2 = NULL;
	}

	for (j = 0; j < vertex; j++) {
		for (i = 0; i < edge; i++) {
			if ((j == nod[i].vertex1 || j == nod[i].vertex2)
				&& adjList[j] == NULL)
			{
				adjList[j] = &nod[i];
				break;
			}
		}
	}

	for (i = 0; i < edge; i++) {
		tmp = &nod[i];
		idx = i;
		while (++idx!=edge) {
			if (tmp->vertex1 == nod[idx].vertex1 || tmp->vertex1 == nod[idx].vertex2) {
				tmp->link1 = &nod[idx];
				break;
			}
		}
		idx = i;
		while (++idx != edge) {
			if (tmp->vertex2 == nod[idx].vertex1 || tmp->vertex2 == nod[idx].vertex2) {
				tmp->link2 = &nod[idx];
				break;
			}
		}
	}

	printf("<<<<<<<<<< edges incident to each vertex >>>>>>>>>>\n\n");
	printf("간선의 정점 출력 순서 - 입력데이터 순서대로\n");
	for (i = 0; i < vertex; i++) {
		listPointer p = adjList[i];
		printf("edges incident to vertex %d : ", i);
		while (p) {
			printf("(%d, %d) ", p->vertex1, p->vertex2);
			p = (i == p->vertex1) ? p->link1 : p->link2;
		}
		printf("\n");
	}

	printf("\n간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
	for (i = 0; i < vertex; i++) {
		listPointer p = adjList[i];
		printf("edges incident to vertex %d : ", i);
		while (p) {
			if(i==p->vertex1)
				printf("(%d, %d) ", p->vertex1, p->vertex2);
			else
				printf("(%d, %d) ", p->vertex2, p->vertex1);
			p = (i == p->vertex1) ? p->link1 : p->link2;
		}
		printf("\n");
	}
}

