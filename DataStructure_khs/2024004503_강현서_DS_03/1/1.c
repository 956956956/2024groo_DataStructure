#include <stdio.h>
#include <stdlib.h>

int* make1dArray(int num);

int* make1dArray(int num) {
	int *arr = (int *)malloc(sizeof(int) * num);

	for (int i = 0; i < num; i++)
		arr[i] = rand() % 100;
	
	return arr;
}

int main() {
	int* ipp;
	int i, num;

	printf("일차원 배열의 수를 입력하세요: ");
	scanf_s("%d", &num);

	ipp = make1dArray(num);
	for (i = 0; i < num; i++) {
		printf("ipp[%2d] = %2d ", i, ipp[i]);
		if ((i % 5 == 4))
			printf("\n");
	}
	free(ipp);
}