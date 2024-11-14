#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_find(char* string, char* pat);

int str_find(char* string, char* pat) {
	int i = 0, j = 0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; (j < lastp) && (string[i] == pat[j]); i++, j++);
		
		if (j == lastp)
			return start;
	}
	return -1;
}

int main() {
	char temp[101] = { 0 };
	int start = 0;

	printf("문자열을 입력하세요 : ");
	scanf_s("%[^\n]%*c", temp, (int)sizeof(temp));

	char* str = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy_s(str, (strlen(temp) + 1), temp);

	printf("비교할 패턴을 입력하세요 : ");
	scanf_s("%[^\n]%*c", temp, (int)sizeof(temp));

	char* pat = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy_s(pat, (strlen(temp) + 1), temp);

	str_find(str, pat);
	
	start = str_find(str, pat);

	printf("\n문자열 %d 번째부터 패턴이 시작됨..", start);

	free(str);
	free(pat);
}