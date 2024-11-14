#include <stdio.h>

int* func1();
void func2(int *p);
void func3(int **p);
char *func4(int n);

int main(void)
{
	int *pNum;
	char *pChar;

	pNum = func1();
	printf("%d\n", *pNum);

	func2(pNum);
	printf("%d\n", *pNum);

	func3(&pNum);
	printf("%d\n", *pNum);

	pChar = func4(100);

	printf("입력할 문자열 = ");
	scanf_s("%s", pChar, 100);
	printf("pChar contents = %s\n", pChar);

	free(pNum);
	free(pChar);
	return 0;
}

int *func1() {
	int *p = (int *)malloc(sizeof(int));
	*p = 10;
	return p;
}

void func2(int *p) {
	*p = 100;
}

void func3(int **p) {
	**p = 200;
}

char *func4(int n) {
	char* c = (char*)malloc(sizeof(char) * n);
	return c;
}