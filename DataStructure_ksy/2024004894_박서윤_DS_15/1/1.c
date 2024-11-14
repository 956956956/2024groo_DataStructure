#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

int* wintree, * sort;

int makeWinner(int n);
void inorder(int k, int n);

int main()
{
	int i, n, seed, item, winindex;

	printf("<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>\n");
	printf("%s", "the number of key ( 4,8, 16, or 32 as a power of 2) >> ");
	scanf_s("%d", &n);
	printf("%s", "value of seed : ");
	scanf_s("%u", &seed);
	srand(seed);

	wintree = malloc(2 * n * sizeof(wintree));
	sort = malloc(n * sizeof(sort));

	for (i = 0; i < n; i++) {
		item = (rand() % MAX_SIZE) + 1;
		wintree[n + i] = item;
		printf("%5d ", item);
	}

	printf("\ninitialization of min-winner tree\n");
	winindex = makeWinner(n);
	inorder(1, n);
	sort[0] = wintree[winindex];

	for (i = 0; i < n; i++) {
		wintree[winindex] = 9999;
		winindex = makeWinner(n);
		sort[i + 1] = wintree[winindex];

		if (i == 1) {
			printf("\nWinner Tree inorder traversal after find 2 winners. . .\n");
			inorder(1, n);
		}
	}

	printf("\n\nsorting with min-winner tree. . .\n");
	printf("\nsorted result\n");
	for (i = 0; i < n; i++)
		printf("%5d", sort[i]);
	puts("");

	free(wintree); free(sort);

	return 0;
}

int makeWinner(int n)
{
	int temp = n;
	int i = -2;

	while (1) {
		i += 2;

		if (wintree[n + i] < wintree[n + i + 1]) {
			wintree[(n + i) / 2] = wintree[n + i];
		}
		else
			wintree[(n + i) / 2] = wintree[n + i + 1];

		if ((n + i + 1) / 2 == 1)
			break;

		if ((n + i + 2) == n * 2) {
			n /= 2;
			i = -2;
		}
	}

	wintree[0] = wintree[1];
	for (i = 0; i < temp; i++)
		if (wintree[0] == wintree[temp + i])
			return temp + i;
}

void inorder(int k, int n)
{
	if (k < n * 2) {
		inorder(k * 2, n);
		printf("%5d", wintree[k]);
		inorder((k * 2) + 1, n);
	}
}