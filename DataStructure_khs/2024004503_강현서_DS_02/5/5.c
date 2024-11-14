#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001

void sort(int a[MAX_SIZE], int n);
void swap(int* a, int* b);

void sort(int a[MAX_SIZE], int n) {

	for (int i = 1; i < n; i++) {

		for (int k = 0; k < i; k++) {
			if (*(a + k) > *(a + i))
				swap(a + k, a + i);
		}
	}
}

void swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	FILE* fp;
	fp = fopen("out3.txt", "w");

	fprintf(fp, "	n	repetitions		time\n");
	for (n = 0; n <= 1000; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		do
		{
			repetitions++;

			for (i = 0; i < n; i++) {
				a[i] = rand();
			}

			sort(a, n);
		}

		while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, "%6d	%9d	%f\n", n, repetitions, duration);
		if (n == 100) step = 100;
	}

	fclose(fp);
}