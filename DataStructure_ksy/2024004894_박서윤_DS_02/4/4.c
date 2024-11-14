#include <stdio.h>
#include <time.h>
#include <stdlib.h>  // For rand() and exit()

#define MAX_SIZE 2001

void sort(int a[], int n) {
    for (int j = 0; j < n - 1; j++) {
        for (int k = j + 1; k < n; k++) {
            if (a[j] > a[k]) {
                int tmp = a[j];
                a[j] = a[k];
                a[k] = tmp;
            }
        }
    }
}

int main() {
    FILE* fp;
    fopen_s(&fp, "out.txt", "w");
    if (!fp) {
        printf("error");
        exit(1);
    }

    int i, n, step = 10;
    int a[MAX_SIZE];
    double duration;

    fprintf(fp, "     n       descending      ascending      random\n");

    for (n = 0; n <= 2000; n += step) {
        double duration_reverse = 0, duration_sorted = 0, duration_random = 0;
        long repetitions;

        // Reverse Order
        repetitions = 0;
        clock_t start = clock();
        do {
            repetitions++;
            for (i = 0; i < n; i++) a[i] = n - i;
            sort(a, n);
        } while (clock() - start < 1000);
        duration_reverse = ((double)(clock() - start)) / CLOCKS_PER_SEC / repetitions;

        // Sorted Order
        repetitions = 0;
        start = clock();
        do {
            repetitions++;
            for (i = 0; i < n; i++) a[i] = i;
            sort(a, n);
        } while (clock() - start < 1000);
        duration_sorted = ((double)(clock() - start)) / CLOCKS_PER_SEC / repetitions;

        // Random Order
        repetitions = 0;
        start = clock();
        do {
            repetitions++;
            for (i = 0; i < n; i++) a[i] = rand() % n;
            sort(a, n);
        } while (clock() - start < 1000);
        duration_random = ((double)(clock() - start)) / CLOCKS_PER_SEC / repetitions;

        fprintf(fp, "%6d   %10f  %10f  %10f\n", n, duration_reverse, duration_sorted, duration_random);
        if (n == 100) step = 100;
    }

    fclose(fp);
    return 0;
}

