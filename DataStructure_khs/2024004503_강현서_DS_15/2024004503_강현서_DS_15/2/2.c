#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 8

int runQ[MAX_SIZE * 10];
int front[MAX_SIZE + 1];
int rear[MAX_SIZE + 1];
int boundary[MAX_SIZE + 1];
int sorted[MAX_SIZE * 10] = { 0 };
int winTree[MAX_SIZE * 2] = { 0 };

void addq(int i, int num);
int deleteq(int i);
void printq(int i);
void winner(int cur, int k, int winTree[]);
void adjust(int ind, int winTree[]);
void printT(int n, int winTree[]);

int main() {
	FILE* fp = fopen("input.txt", "r");
	int i, j, num, cnt, n;
	front[0] = rear[0] = boundary[0] = -1;
	for (i = 1; i < MAX_SIZE; i++)
		front[i] = rear[i] = boundary[i] = 10 * i - 1;
	boundary[MAX_SIZE] = MAX_SIZE * 10 - 1;
	
	printf("<<<<<<<<<<<<<<< run data >>>>>>>>>>>>>>>\n");
	
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < 10; j++) {
			fscanf(fp, "%d", &num);
			addq(i, num);
		}
		printq(i);
	}
	
	int k = MAX_SIZE;
	for (cnt = k, i = 0; i < k; cnt++, i++) {
		winTree[cnt] = deleteq(i);
	}
	winner(1, k, winTree);

	printf("\n\nLeve-oorder traversal for initial min-winner tree\n");
	printT(cnt, winTree);

	printf("\nsorting with min-winner tree...\n");
	for (i = 0; i < k * 10; i++) {
		sorted[i] = winTree[1];

		for (j = k; j < k * 2; j++) {
			if (sorted[i] == winTree[j]) {
				winTree[j] = deleteq(j - MAX_SIZE);
				break;
			}
		}
		adjust(j, winTree);
	}
	for (i = 0; i < k * 10; i++) {
		printf("%4d", sorted[i]);
		if ((i + 1) % 8 == 0) printf("\n");
	}
}

void addq(int i, int num) {
	if (rear[i] == boundary[i + 1])
		return;
	runQ[++rear[i]] = num;
}

int deleteq(int i) {
	if (front[i] == boundary[i + 1])
		return 9999;
	return runQ[++front[i]];
}

void printq(int i) {
	int j;
	printf("\n%d-th run:\n", i + 1);
	for (j = front[i] + 1; j <= rear[i]; j++)
		printf("%5d", runQ[j]);
}

void winner(int cur, int k, int winTree[]) {
	int start, parent;
	start = k * 2 - 1;
	parent = start / 2;

	while (parent >= 1) {
		if (winTree[start] > winTree[start - 1])
			winTree[parent] = winTree[start - 1];
		else
			winTree[parent] = winTree[start];

		start = start - 2;
		parent = start / 2;
	}
}

void adjust(int ind, int winTree[]) {
	int parent, cmp;

	parent = ind / 2;
	while (parent >= 1) {
		if (ind % 2)
			cmp = ind - 1;
		else
			cmp = ind + 1;

		if (winTree[ind] >= winTree[cmp])
			winTree[parent] = winTree[cmp];
		else
			winTree[parent] = winTree[ind];

		ind = ind - 2;
		parent = ind / 2;
	}
}

void printT(int n, int winTree[]) {
	for (int i = 1; i < n; i++) {
		printf("%d ", winTree[i]);
	}
	printf("\n");
}