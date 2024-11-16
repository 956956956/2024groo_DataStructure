// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void binary(int number); // �Լ� ����
int zero(int num);

int main() {
	int decimal;

	printf("Input num: ");
	while ((scanf("%d", &decimal) && decimal > 1)) {
		printf("2��ǥ��: ");
		binary(decimal);
		printf("\n%d�� %d�� %d�� �ִ�.\n", decimal, 0, zero(decimal));
		printf("Input num: ");
	}
	printf("Exit");
	return 0;
}

// �������� ���ϴ� ��� �Լ�
void binary(int number) {
	int bin;

	if (number > 0) {
		// ���� bin�� �������� ����
		bin = number % 2;
		number /= 2;

		// ��� ȣ��
		binary(number);
		printf("%d", bin);
	}

	return;
}

// 0�� ������ ���ϴ� ��� �Լ�
int zero(int num) {
	int count = 0;

	if (num == 1) { // 1�� ���
		return count;
	}
	else if (num % 2 == 1) { // Ȧ���� ���
		num /= 2;
		count += zero(num);
	}
	else if (num % 2 == 0) { // ¦���� ���
		num /= 2;
		count += zero(num) + 1;
	}
	return count;
}