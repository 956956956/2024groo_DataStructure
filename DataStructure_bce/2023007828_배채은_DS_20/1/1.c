#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* list;
void insertionSort(int list[], int first, int last, int gap);
void shellSort(int list[], int n);


int main() {
	FILE* fp;
	int i, n;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &n);
	list = malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		fscanf(fp, "%d", &list[i]);

	printf("list[] data\n");
	for (i = 0; i < n; i++)
		fprintf(stdout, "%5d", list[i]);

	shellSort(list, n);
}

void shellSort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		printf("\n\ngap is %5d ====>\n", gap);
		for (i = 0; i < gap; i++)
			insertionSort(list, i, n - 1, gap);
		for (i = 0; i < n; i++)
			fprintf(stdout, "%5d", list[i]);
		printf("\n");
	}
}


void insertionSort(int list[], int first, int last, int gap) {
	int i, j, key;

	for (i = first+gap; i <=last; i= i+gap) {
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j = j-gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}
