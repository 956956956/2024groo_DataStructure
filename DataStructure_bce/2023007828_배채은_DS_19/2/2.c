#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10


typedef struct node* nodePointer;
typedef struct node {
	int v;
	nodePointer link;
}node;
typedef struct {
	int count;
	nodePointer link;
} hdnodes;
hdnodes *graph;

void init();
void insert(hdnodes graph[], int v1, int v2);
void topSort(hdnodes graph[], int n);
void push(int item);
int pop();

int stack[MAX_STACK_SIZE];
int top = -1;


int main() {
	FILE* fp;
	int verN, v1, v2;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &verN);
	init(verN);
	
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &v1, &v2);
		insert(graph, v1, v2);
	}

	topSort(graph, verN);

}

void insert(hdnodes graph[], int v1, int v2) {
	nodePointer new = malloc(sizeof(node));
	new->v = v2;
	new->link = NULL;
	if (graph[v1].link == NULL) {
		graph[v1].link = new;
	}
	else {
		new->link = graph[v1].link;
		graph[v1].link = new;
	}
	graph[v2].count++;

}

void topSort(hdnodes graph[], int n) {
	int i, j, k;
	nodePointer p;

	for (i = 0; i < n; i++) {
		if (graph[i].count == 0) {
			push(i);
		}
	}

	for (i = 0; i < n; i++) {
		if (top == -1) {
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated. \n");
			exit(EXIT_FAILURE);
		}
		else {
			j = pop();
			printf("%-d ", j);
			if (i != n - 1)
				printf(" -> ");
			for (p = graph[j].link; p; p = p->link) {
				k = p->v;
				graph[k].count--;
				if (graph[k].count == 0) {
					push(k);
				}
			}
		}
	}
}

void init(int n) {
	graph = malloc(sizeof(*graph) * n);
	for (int i = 0; i < n; i++) {
		graph[i].count = 0;
		graph[i].link = NULL;
	}
}

void push(int item){
	stack[++top] = item;
}

int pop(){
	return stack[top--];
}