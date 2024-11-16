// 2023012565 ±Ë¿∫¡§
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 1001

void sort(int list[], int n);

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;

	/* time for n = 0, 10, ..., 100, 200, ..., 1000 */
	printf("     n	       repititions  		time\n");
	for (n = 0; n <= 1000; n += step) {
		/* get time for size n */
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;

			/* initialize with worst-case data */
			for (i = 0; i < n; i++)
				a[i] = n - i;

			sort(a, n);
		} while (clock() - start < 1000);
			/* repeat until enough time has elapsed */

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d		%9d		%f\n", n, repetitions, duration);
		if (n == 100) step = 100;
	}
}

void sort(int list[], int n) {		// ¡§∑ƒ
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min])
				min = j;
			SWAP(list[i], list[min], temp);
		}
	}
}