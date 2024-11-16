#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// abcabcabaaabcabcabcabcabcabccqabcabcabcabb


int nfind(char* str, char* pat) {
	int i = 0, j = 0, start = 0;
	int lasts = strlen(str) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (str[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && str[i] == pat[j]; i++, j++);
		if (j == lastp)
			return start;
	}
	return -1;
}

int main() {
	char str[50];
	char pat[30];
	int* pi, len;
	printf("문자열을 입력하세요 : ");
	scanf("%s", str);
	printf("비교할 패턴을 입력하세요 : ");
	scanf("%s", pat);

	printf("문자열 %d 번째부터 패턴이 시작됨", nfind(str, pat));
}