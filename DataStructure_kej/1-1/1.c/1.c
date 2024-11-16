// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	FILE* fp;
	int num, max = 0, min = 101, sum = 0, count = 0;
	int avg = 0;

	scanf("%d", &num);	// 표준 입력
	while (!feof(stdin)) {
		if (num > max)
			max = num;
		if (num < min)
			min = num;
		count++;
		sum += num;
		scanf("%d", &num);
	}

	avg = sum / count;

	fp = fopen("out.txt", "w");		// 파일 출력
	if (!fp) {
		puts("Cannot open the file");
		exit(1);
	}
	fprintf(fp, "MIN: %d, MAX: %d, AVG: %d", min, max, avg);
	fclose(fp);

	return 0;
}