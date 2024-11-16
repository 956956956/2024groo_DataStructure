#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ROW 8
#define COL 10
#define MAX 9999

int winTree[2 * ROW];
int run[ROW][COL];
int sort[ROW*COL];
int sortIdx[ROW] = { 0 };
int makeWinTree(int);
void inorder(int, int);

int main() {
	int i,j, idx, sortidx=1;
	FILE* fp = fopen("input.txt", "r");

	printf("<<<<<<<<<<<< run data >>>>>>>>>>>>\n\n");
	
	while (!feof(fp)) {
		for (i = 0; i < ROW; i++) {
			for (j = 0; j < COL; j++)
				fscanf(fp, "%d", &run[i][j]);

		}
	}

	for (i = 1; i <= ROW; i++) {
		printf("%d-th run:\n", i);
		for (j = 0; j < COL; j++)
			printf("%5d", run[i-1][j]);
		printf("\n");
	}

	for (i = 0; i < ROW; i++) {
		winTree[ROW + i] = run[i][0];
	}

	printf("\nLevel-order traversal for initial min-winner tree\n");

	for (i = 0; i < ROW * COL; i++) {
		idx = makeWinTree(ROW);
		sort[i] = winTree[idx];
		winTree[idx] = run[idx - ROW][++sortIdx[idx-ROW]];
		
		if (sortIdx[idx - ROW] == 10)
			winTree[idx] = 9999;

		if (i == 0) {
			for (j = 1; j < 2 * ROW; j++)
				printf("%d ", winTree[j]);
		}
	}

	printf("\nsorting with min-winner tree. . .\n\n");

	printf("sorted result\n");
	for (i = 0; i < ROW * COL; i++) {
		printf("%5d", sort[i]);
		if ((i + 1) % 8 == 0)
			printf("\n");
	}

}

int makeWinTree(int n) {
	int index = 0, j = 1;
    for (int i = 1; i < n; i++)
    {
        if (winTree[n * 2 - j] < winTree[n * 2 - (j + 1)])
            winTree[(n * 2 - j) / 2] = winTree[n * 2 - j];
        else
            winTree[(n * 2 - j) / 2] = winTree[n * 2 - (j + 1)];
        j = j + 2;
    }
    for (int i = 0; i < n; i++)
    {
        if (winTree[n + i] == winTree[1])
        {
            index = n + i;
            break;
        }
    }
    return index;
}

