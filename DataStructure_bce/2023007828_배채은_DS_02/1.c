#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int* func1() {
	int* p = (int*)malloc(sizeof(int));
	*p = 10;
	return p;
}

void func2(int*p) {
	*p = 100;
	return;
}

void func3(int** p) {
	**p = 200;
	return;
}

char* func4(int n) {
	char* p = (char*)malloc(n);
	return p;
}

int main(void)
{
	int* pNum;
	char* pChar;
	pNum = func1(); // int ũ�⸸ŭ �����Ҵ� �޾� 10�� ������ ������ ������ ����
	printf("%d\n", *pNum);

	func2(pNum);// pNum�� ����Ű�� ���� 100���� ����
	printf("%d\n", *pNum);
	
	func3(&pNum); // pNum�� ����Ű�� ���� 200���� ����
	printf("%d\n", *pNum);
	
	pChar = func4(100); // pChar �� 100byte �Ҵ� ���� �޸𸮿� Ű����κ��� �Է� ���� ���ڿ� ����
	printf("\n�Է��� ���ڿ� : ");
	scanf("%s", pChar);
	printf("pChar contents = %s\n", pChar);
	
	free(pNum);
	free(pChar);
	return 0;
}