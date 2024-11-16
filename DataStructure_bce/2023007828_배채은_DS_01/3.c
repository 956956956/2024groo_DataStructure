#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


//반복적인 방법
int binarySearch(int* p, int left, int right, int n) {
	int mid;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (p[mid] < n)
			left = mid + 1;
		else if (p[mid] == n)
			return mid;
		else
			right = mid - 1;
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


	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n;j++) {
			if (ary[j] < ary[min])
				min = j;
		}
		if (i != min) {
			tmp = ary[i];
			ary[i] = ary[min];
			ary[min] = tmp;
		}
	}

	printf("\n\nSorted array:\n");
	for (i = 0; i < n; i++)
		printf("%d ", ary[i]);

	printf("\n\nEnter the number to search: ");
	scanf("%d", &snum);
	printf("The search number is present in list[%d]", binarySearch(ary, 0, n - 1, snum));
}