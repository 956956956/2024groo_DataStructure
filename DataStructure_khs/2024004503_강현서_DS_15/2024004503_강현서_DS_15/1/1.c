#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 499
#define INF_NUM 9999

int nums[MAX_SIZE + 1] = { 0 };
int winTree[MAX_SIZE * 2] = { 0 };
int sorted[MAX_SIZE + 1] = { 0 };

void winner(int cur, int k, int winTree[]);
void inorder(int root, int k, int winTree[]);
void adjust(int ind, int winTree[]);

int main() {
	int i, j, cnt, k, seed;
	printf("<<<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>>>\n");
	printf("\nthe number of keys ( 4, 8, 16, or 32 as a power of 2 )  >> ");
	scanf_s("%d", &k);
	printf("%s", "value of seed >>  ");
	scanf_s("%u", &seed);
	srand(seed);

	for (i = 1; i <= k; i++) {
		nums[i] = rand() % MAX_SIZE + 1;
		printf(" %5d", nums[i]);
	}

	printf("\n\ninitialization of min-winner tree\n");
	for (cnt = k, i = 1; i <= k; cnt++, i++) {
		winTree[cnt] = nums[i];
	}
	winner(1, k, winTree);

	printf("\nWinner Tree inorder traversal after find 2 winners\n");
	for (i = 1; i <= k; i++) {
		sorted[i] = winTree[1];

		for (j = k; j < k * 2; j++) {
			if (sorted[i] == winTree[j]) {
				winTree[j] = INF_NUM;
				break;
			}
		}
		adjust(j, winTree);

		if (i == 2)
			break;
	}
	inorder(1, k, winTree);

	printf("\n\nsorting with min-winner tree...\n");
	for (i = 3; i <= k; i++) {
		sorted[i] = winTree[1];

		for (j = k; j < k * 2; j++) {
			if (sorted[i] == winTree[j]) {
				winTree[j] = INF_NUM;;
				break;
			}
		}
		adjust(j, winTree);

	}

	printf("\nsorted result\n");
	for (i = 1; i <= k; i++)
		printf("%5d", sorted[i]);
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

	printf("\ninorder traversal for min-winner tree\n");
	inorder(1, k, winTree);
}

void inorder(int root, int k, int winTree[]) {
	if (root < k * 2) {
		inorder(root * 2, k, winTree);
		printf("%5d", winTree[root]);
		inorder(root * 2 + 1, k, winTree);
	}
}

void adjust(int ind, int winTree[]) {
	int cmp;

	while (ind >= 1) {
		if (ind % 2)
			cmp = ind - 1;
		else
			cmp = ind + 1;

		if (winTree[ind] >= winTree[cmp])
			winTree[ind / 2] = winTree[cmp];
		else
			winTree[ind / 2] = winTree[ind];

		ind /= 2;
	}
}