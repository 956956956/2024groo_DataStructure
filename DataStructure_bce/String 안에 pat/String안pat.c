#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 80


//abcabcabaaabcabcabcabcabcabccqabcabcabcabb
//abcabcabca


int main() {
	int slen, plen, i, j, len = 0, end = 0;
	char str[MAX_SIZE];
	char pat[MAX_SIZE];
	char ch;
	
	printf("���ڿ� : ");
	scanf("%s", str);
	printf("���� : ");
	scanf("%s", pat);
	slen = strlen(str);
	plen = strlen(pat);

	ch = pat[plen - 1];
	for (i = plen - 1; i < slen; i++) {
		if (end)
			break;
		if (str[i] == ch) {
			len = 1;
			j = i;
			while (1) {	
				if (str[--j] == pat[plen - len - 1])
					len++;
				else {
					len = 0;
					break;
				}
				if (len == plen) {
					printf("���ڿ� %d��°���� ����", j);
					end = 1;
					break;
				}
			}
		}

	}


}