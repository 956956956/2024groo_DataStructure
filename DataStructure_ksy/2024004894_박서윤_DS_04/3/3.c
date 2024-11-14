#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat);

int main()
{
    char str[100];
    char p[100];

    char* string = str;
    char* pat = p;

    printf("문자열을 입력하세요: ");
    scanf_s("%s", string, 100);
    printf("비교할 패턴을 입력하세요: ");
    scanf_s("%s", pat, 100);

    int t = nfind(string, pat);

    if (t == -1)
        printf("문자열 내에 패턴이 존재하지 않음\n");
    else
        printf("문자열 %d번째부터 패턴이 시작됨\n", t + 1);  // 인덱스를 1부터 시작하게 변경

    return 0;
}

int nfind(char* string, char* pat)
{
    int i, j;
    int start = 0;
    int lasts = strlen(string);
    int lastp = strlen(pat);

    for (start = 0; start <= lasts - lastp; start++) {
        for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++)
            ;

        if (j == lastp) // 모든 패턴이 일치하면
            return start;
    }
    return -1;
}
