// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void binary(int number); // 함수 원형
int zero(int num);

int main() {
	int decimal;

	printf("Input num: ");
	while ((scanf("%d", &decimal) && decimal > 1)) {
		printf("2진표현: ");
		binary(decimal);
		printf("\n%d내 %d는 %d개 있다.\n", decimal, 0, zero(decimal));
		printf("Input num: ");
	}
	printf("Exit");
	return 0;
}

// 이진수를 구하는 재귀 함수
void binary(int number) {
	int bin;

	if (number > 0) {
		// 변수 bin에 나머지를 저장
		bin = number % 2;
		number /= 2;

		// 재귀 호출
		binary(number);
		printf("%d", bin);
	}

	return;
}

// 0의 개수를 구하는 재귀 함수
int zero(int num) {
	int count = 0;

	if (num == 1) { // 1인 경우
		return count;
	}
	else if (num % 2 == 1) { // 홀수인 경우
		num /= 2;
		count += zero(num);
	}
	else if (num % 2 == 0) { // 짝수인 경우
		num /= 2;
		count += zero(num) + 1;
	}
	return count;
}