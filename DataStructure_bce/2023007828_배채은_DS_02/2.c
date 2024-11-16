#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 2001


void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void sort(int list[], int n) {
	int i, j, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		swap(&list[i], &list[min]);
	}
}

int main() {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	FILE* fp = fopen("out1.txt", "w");
	clock_t start;

	fprintf(fp, "   n    time\n");
	for (n = 0; n <= 2000; n += step) {
		for (i = 0; i < n; i++)
			a[i] = n - i;

		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		fprintf(fp, "%6d %f\n", n, duration);
		if (n == 100) step = 100;
	}
	fclose(fp);
}


