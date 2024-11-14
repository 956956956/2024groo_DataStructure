#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001

void selectsort(int num[MAX_SIZE], int size);
void swap(int* a, int* b);

void selectsort(int num[MAX_SIZE], int size)
{
	int i = 0, j = 0;

	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (*(num + i) > *(num + j))										
			{
				swap(num + i, num + j);
			}
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
	fp = fopen("out.txt", "w");
	clock_t start;

	fprintf(fp, "	n	time\n");
	for (n = 0; n <= 1000; n += step)
	{
		for (i = 0; i < n; i++) {
			a[i] = n - i;
		}

		start = clock();
		selectsort(a, n);
		duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
		fprintf(fp, "%6d	%f\n", n, duration);
		if (n == 100) step = 100;
	}

	fclose(fp);
}