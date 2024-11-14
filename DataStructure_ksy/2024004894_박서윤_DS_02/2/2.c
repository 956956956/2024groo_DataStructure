#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 2000

void sort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main() {
    int n, i, step = 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;
    FILE* fp = fopen("out.txt", "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다");
        return 1;
    }

    //times for n = 0, 10, ... , 100 ,..., 1000
    fprintf(fp, "     n      time\n");
    for (n = 0; n <= 2000; n += step) {
        for (i = 0; i < n; i++) {
            a[i] = n - 1;
        }

        start = clock();
        sort(a, n);
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        fprintf(fp, "%6d     %f\n", n, duration);

        // n이 100 이하이면 10씩, 그 이상이면 100씩 증가
        if (n < 100) {
            step = 10;
        }
        else {
            step = 100;
        }
    }

    fclose(fp);
    return 0;
}

