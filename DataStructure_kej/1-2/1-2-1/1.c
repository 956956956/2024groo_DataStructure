// 2023012565 ±Ë¿∫¡§
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 1001

void sort(int list[], int n);	/* selection sort */

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start;

	/* times for n = 0, 10, ..., 100, 200, ..., 1000 */
	printf("     n  	time\n");
	for (n = 0; n <= 1000; n += step) {
		/* get time for size n */

		/* initialize with worst-case data */
		for (i = 0; i < n; i++)
			a[i] = n - i;

		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("%6d		%f\n", n, duration);
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