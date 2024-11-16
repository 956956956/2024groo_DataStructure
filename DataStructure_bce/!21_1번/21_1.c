#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void selectionSort(int* ary, int* size) {
	int i, j, tmp;
	for (i = 0; i < *size - 1; i++) {
		tmp = i;
		for (j = i+1; j < *size; j++) {
			if (ary[j] < ary[tmp])
				tmp = j;
		}
		swap(&ary[tmp], &ary[i]);
	}
	return;
}

void binarySearch(int*ary, int low, int high, int num) {
	int mid = (high + low) / 2;
	for (int i = low; i <= high; i++)
		printf("%d ", ary[i]);
	printf("\n");
	if (ary[mid] == num)
		printf("%d번째 인덱스에 위치", mid);
	else if (ary[mid] < num)
		binarySearch(ary, mid + 1, high, num);
	else
		binarySearch(ary, low, mid-1, num);
}

int main() {
	FILE* fp;
	int ary[MAX_SIZE], size = 0, i, snum;
	if ((fp = fopen("input1.txt", "r")) == NULL) {
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &ary[size++]);
	}

	printf("정렬 전 :\n");
	for (i = 0; i < size; i++) {
		printf("%d ", ary[i]);
	}

	selectionSort(&ary, &size);
	printf("\n\n정렬 후 :\n");
	for (i = 0; i < size; i++) {
		printf("%d ", ary[i]);
	}

	printf("\n\n탐색할 숫자 입력:");
	scanf("%d", &snum);
	binarySearch(&ary, 0, size-1, snum);


}