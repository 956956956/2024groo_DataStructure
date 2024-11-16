// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int maximum(int ary[], int max, int n); // 함수 원형

int main() {
	FILE* fp = fopen("in.txt", "r");
	int i, N;
	int* arr;

	if (!fp) {
		puts("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &N);
	arr = (int*)malloc(sizeof(int) * N);
	printf("숫자리스트>>\n");
	for (i = 0; i < N; i++) {
		fscanf(fp, "%d", &arr[i]);
		printf(" %d", arr[i]);
	}
	printf("\n최댓값: %d", maximum(arr, arr[N-1], N));
	fclose(fp);
	return 0;
}

int maximum(int ary[], int max, int n) { // 최댓값 구하는 재귀 함수
	if (n == 1)
		return max;
	else {
		if (ary[n - 2] > max)
			max = ary[n - 2];
		maximum(ary, max, n-1);
	}
}