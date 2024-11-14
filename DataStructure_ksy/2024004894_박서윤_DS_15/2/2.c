#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define MAX_TREE_SIZE 16
#define MAX_RUN 8
#define INF 9999
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

int winnerTree[MAX_TREE_SIZE];
int sortedArr[MAX_SIZE * MAX_RUN];
int idx[MAX_RUN];
int key[MAX_RUN][MAX_SIZE];

void init_winner_tree() {
	int i, j;
	for (i = MAX_RUN; i < MAX_RUN * 2; i++) {
		winnerTree[i] = key[i - MAX_RUN][0];
	}

	i = MAX_RUN * 2 - 1; j = 0;
	while (winnerTree[1] == 0) {
		winnerTree[i / 2] = MIN(winnerTree[i], winnerTree[i - 1]);
		i -= 2;
	}
}

void make_winner_tree() {
	int i, j;
	for (i = MAX_RUN; i < MAX_RUN * 2; i++) {
		winnerTree[i] = key[i - MAX_RUN][idx[i - MAX_RUN]];
	}
	winnerTree[1] = 0;

	i = MAX_RUN * 2 - 1; j = 0;
	while (winnerTree[1] == 0) {
		winnerTree[i / 2] = MIN(winnerTree[i], winnerTree[i - 1]);
		i -= 2;
	}
}

void levelorder() {
	int i;
	for (i = 1; i < 16; i++) {
		printf("%d ", winnerTree[i]);
	}
	printf("\n");
}

void sortwithMinTree(int* n) {
	int i;
	sortedArr[(*n)++] = winnerTree[1];
	for (i = 0; i < MAX_RUN; i++) {
		if (key[i][idx[i]] == winnerTree[1]) {
			idx[i]++;
			if (idx[i] >= 10) {
				key[i][0] = INF;
				idx[i] = 0;
			}
			break;
		}
	}
	make_winner_tree();
}

int main() {
	FILE* fp;
	int i, j, n = 0;
	int k;
	int temp;

	printf("<<<<<<<<<<<<< run data >>>>>>>>>>>>>\n\n");
	if (fopen_s(&fp, "input.txt", "r")) exit(1);

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 10; j++) {
			fscanf_s(fp, "%d", &key[i][j]);
		}
	}

	for (i = 0; i < 8; i++) {
		printf("%d-th run:\n", i + 1);
		for (j = 0; j < 10; j++) {
			printf(" %4d", key[i][j]);
		}
		printf("\n");
	}
	init_winner_tree();
	printf("\nLevel-order traversal for initial min-winner tree\n");
	levelorder();

	printf("\nsorting with min-winner tree...\n\n");
	while (n < MAX_RUN * MAX_SIZE) sortwithMinTree(&n);

	printf("sorted result:");
	for (i = 0; i < MAX_RUN * MAX_SIZE; i++) {
		if (i % 8 == 0) printf("\n");
		printf("%3d ", sortedArr[i]);
	}
	printf("\n");

	return 0;
}