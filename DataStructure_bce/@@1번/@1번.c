#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void selectionSort(int* ary, int* size) {
	int i, j, tmp;
	for (i = 0; i < *size; i++) {
		tmp = ary[i];
		for (j = *size; j > i; j--) {
			if (tmp > ary[j])
				swap(&ary[i], &ary[j]);
		}
	}
	return;
}

int main() {
	FILE* fp;
	int* ary, size=0, i;
	if ((fp = fopen("input1.txt", "r")) == NULL) {
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}
	
	while (!feof(fp)) {
		ary[size] = (int*)malloc(sizeof(int));
		fscanf("%d", &ary[size++]);
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



}