#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fp1 = fopen("in1.txt", "r"), * fp2 = fopen("in2.txt", "r");
	int num1, num2;

	if (!fp1 || !fp2) {
		puts("Can't open the file");
		exit(1);
	}

	fscanf(fp1, "%d", &num1);
	fscanf(fp2, "%d", &num2);

	while (!feof(fp1) && !feof(fp2)) {
		if (num1 > num2)				// in1.txt의 숫자가 큰 경우
			fscanf(fp1, "%d", &num1);
		else if (num1 < num2)			// in2.txt의 숫자가 큰 경우
			fscanf(fp2, "%d", &num2);
		else {							// 숫자가 같아서 출력하는 경우
			printf("%d ", num1);
			fscanf(fp1, "%d", &num1);
			fscanf(fp2, "%d", &num2);
		}
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}