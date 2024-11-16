#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 9999

int* winTree, *sort;
int makeWinTree(int);
void inorder(int, int);

int main() {
	int k, seed, i, winindex;

	printf("<<<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>>>\n\n");
	printf("the number of keys ( 4, 8, 16, or 32 as a power of 2 )  >> ");
	scanf("%d", &k);

	printf("value of seed >>  ");
	scanf("%d", &seed);
	srand(seed);

	winTree = calloc(2*k, sizeof(int));
	sort = calloc(k, sizeof(int));

	for (i = 0; i < k; i++) {
		winTree[k + i] = 1 + rand() % 499 ;
		printf("%5d", winTree[k + i]);
	}

	printf("\n\ninitialization of min-winner tree\n");
	winindex = makeWinTree(k);

	printf("\ninorder traversal for min-winner tree\n");
	inorder(1, k);

	sort[0] = winTree[winindex];

	for (i = 0; i < k; i++) {
		winTree[winindex] = 9999;
		winindex = makeWinTree(k);
		sort[i + 1] = winTree[winindex];

		if (i == 1) {
			printf("\nWinner Tree inorder traversal after find 2 winners. . .\n");
			inorder(1, k);
		}
	}

	printf("\n\nsorting with min-winner tree. . .\n\n");
	printf("sorted result\n");
	for (i = 0; i < k; i++)
		printf("%5d", sort[i]);


}

int makeWinTree(int n) {
	int i = -2;
	int temp = n;
	while (1) {

		i += 2;
		if (winTree[n +i] > winTree[n+i+1]) {
			winTree[(n + i) / 2] = winTree[n + i + 1];
		}
		else {
			winTree[(n + i) / 2] = winTree[n + i];
		}

		if ((n + i + 1) / 2 == 1)
			break;

		if (i == n-2) {
			n /= 2;
			i = -2;
		}
	}

	winTree[0] = winTree[1];
	for (i = 0; i < temp; i++) {
		if (winTree[temp + i] == winTree[0])
			return temp + i;
	}
	return 0;
}

void inorder(int k, int n) {
	if (k < n * 2) {
		inorder(k * 2, n);
		printf("%5d", winTree[k]);
		inorder(k * 2 + 1, n);
	}
}