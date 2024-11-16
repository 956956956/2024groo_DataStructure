#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* p, int left, int right, int n) {
	int mid = (left + right) / 2;
	printf("call binsearch_recur, left=%d, right=%d\n", left, right);

	if (left <= right) {
		if (n == p[mid])
			return mid;
		else if (p[mid] > n)
			return binarySearch(p, left, mid - 1, n);
		else
			return binarySearch(p, mid + 1, right, n);
	}
	return -1;
}

int main() {
	int n, * ary, min, tmp, i, j, snum;
	printf("Enter the number of numbers to generate: ");
	scanf("%d", &n);
	ary = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		printf("%d ", ary[i] = rand() % 1000);

	for (i = 0; i < n; i++) {
		tmp = ary[i];
		for (j = i - 1; j >= 0 && ary[j] > tmp; j--) {
			ary[j + 1] = ary[j];
		}
		ary[j + 1] = tmp;
	}

	printf("\n\nSorted array:\n");
	for (i = 0; i < n; i++)
		printf("%d ", ary[i]);

	printf("\n\nEnter the number to search: ");
	scanf("%d", &snum);
	printf("The search number is present in list[%d]", binarySearch(ary, 0, n - 1, snum));
}