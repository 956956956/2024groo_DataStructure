// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int*** A;
	int I, J, K, i, j, k;
	
	printf("A[I][J][K]...\n");	// 표준 입력
	printf("Input I: ");
	scanf("%d", &I);
	printf("Input J: ");
	scanf("%d", &J);
	printf("Input K: ");
	scanf("%d", &K);

	A = (int***)malloc(sizeof(int**) * I);	// 메모리 할당
	for (i = 0; i < I; i++) {
		A[i] = (int**)malloc(sizeof(int*) * J);
	}
	for (i = 0; i < I; i++) {
		for (j = 0; j < J; j++) {
			A[i][j] = (int*)malloc(sizeof(int) * K);
		}
	}

	for (i = 0; i < I; i++) {	// 표준출력
		for (j = 0; j < J; j++) {
			for (k = 0; k < K; k++) {
				A[i][j][k] = i + j + k;
				printf("A[%d][%d][%d]=%d ", i, j, k, A[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (i = 0; i < I; i++) {	// 메모리 해제
		for (j = 0; j < J; j++) {
			free(A[i][j]);
		}
	}
	for (i = 0; i < I; i++) {
		free(A[i]);
	}
	free(A);	
	return 0;
}