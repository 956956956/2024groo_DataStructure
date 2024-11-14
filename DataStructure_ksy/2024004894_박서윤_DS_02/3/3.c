#include <stdio.h>
#include <time.h>
#define MAX_SIZE 2001
int main() {
	FILE* fp;
	fopen_s(&fp, "out.txt", "w");
	if (!fp) {
		printf("error");
		exit(1);
	}
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	fprintf(fp, "     n     repetitions 	 time\n");
	for (n = 0; n <= 2000; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		do
		{
			repetitions++;
			for (i = 0; i < n; i++) a[i] = n - i;
			for (int j = 0; j < n - 1; j++) {
				for (int k = j + 1; k < n; k++) {
					if (a[j] > a[k]) {
						int tmp = a[j];
						a[j] = a[k];
						a[k] = tmp;
					}
				}
			}
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, "%6d   %9d    %f\n", n, repetitions, duration);
		if (n == 100) step = 100;
	}
	fclose(fp);
}