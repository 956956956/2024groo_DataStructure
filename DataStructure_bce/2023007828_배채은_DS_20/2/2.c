#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* list;
int cnt = 0;
void quickSort(int list[], int left, int right, int n);
void swap(int* a, int* b);

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
	fclose(fp);

	printf("<<<<<<<<<<<< Input List >>>>>>>>>>>>\n");
	for (i = 0; i < n; i++)
		fprintf(stdout, "%2d ", list[i]);

	printf("\n\nexecution of quick sort ...");
	quickSort(list, 0, n - 1, n);
	printf("\n\ncalls of quick sort: %d", cnt);


	printf("\n\n<<<<<<<<<<<< Sorted List >>>>>>>>>>>>\n");
	for (i = 0; i < n; i++)
		fprintf(stdout, "%2d ", list[i]);
	free(list);
}

void quickSort(int list[], int left, int right, int n) {
	int pivot, i, j;
	int tmp;

	if (left < right) {
		cnt++;
		i = left; j = right;
		pivot = list[left];
		while (i < j) {
			while (list[j] > pivot)
				j--;
			while (list[i] <= pivot)
				i++;
			if (i < j)
				swap(&list[i], &list[j]);
		}
		swap(&list[left], &list[j]);

		printf("\npivot = %d : ", pivot);
		for (int k = 0; k < n; k++)
			fprintf(stdout, "%2d ", list[k]);
		quickSort(list, left, j - 1, n);
		quickSort(list, j + 1, right, n);
	}
}


void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}