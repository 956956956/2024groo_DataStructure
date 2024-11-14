/*1. 입력 받은 일차원 배열의 원소 개수를 함수 make1dArray()에 전달하면, 함수
make1dArray()는 전달 받은 원소 갯수 만큼 동적으로 메모리를 할당 받아 램덤으로 100
보다 적은 값으로 메모리를 초기화 시킨 후, 주소값을 반환한다. (즉 함수 호출로 1차원 배열 만들기)*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* make1dArray(int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 100;
	}
	return arr;
}

int main() {
	int* ipp;
	int i, num;

	printf("일차원 배열의 수를 입력하세요: ");
	scanf_s("%d", &num);

	ipp = make1dArray(num);
	for (i = 0; i < num; i++) {
		printf("ipp[%2d] =%2d ", i, ipp[i]);
		if ((i % 5) == 4)
			printf("\n");
	}
	return 0;

}