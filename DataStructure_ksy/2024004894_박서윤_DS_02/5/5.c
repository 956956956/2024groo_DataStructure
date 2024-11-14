#include <stdio.h>
#include <time.h>
#include <stdlib.h> // for rand() function
#include <string.h> // for memset()
#define MAX_SIZE 2001

void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

double measure_sort_time(int arr[], int n, void (*sort_function)(int[], int)) {
    clock_t start = clock();
    long repetitions = 0;
    while (1) {
        repetitions++;
        // Initialize array with reverse order
        for (int i = 0; i < n; i++) arr[i] = n - i;
        sort_function(arr, n);
        if (((double)(clock() - start) / CLOCKS_PER_SEC) > 1.0) break;
    }
    return ((double)(clock() - start)) / CLOCKS_PER_SEC / repetitions;
}

int main() {
    FILE* fp;
    errno_t err = fopen_s(&fp, "out.txt", "w");
    if (err != 0) {
        printf("Error opening file\n");
        return 1;
    }

    int a[MAX_SIZE];
    double reverse_duration, sorted_duration, random_duration;

    fprintf(fp, "     n      descending      ascending      random\n"); // Header for columns

    for (int n = 0; n <= 2000; n += (n < 100) ? 10 : 100) {
        // Measure reverse sorted time
        reverse_duration = measure_sort_time(a, n, insertion_sort);

        // Measure sorted time
        clock_t start = clock();
        long repetitions = 0;
        while (1) {
            repetitions++;
            // Initialize array with sorted order
            for (int i = 0; i < n; i++) a[i] = i;
            insertion_sort(a, n);
            if (((double)(clock() - start) / CLOCKS_PER_SEC) > 1.0) break;
        }
        sorted_duration = ((double)(clock() - start)) / CLOCKS_PER_SEC / repetitions;

        // Measure random time
        start = clock();
        repetitions = 0;
        while (1) {
            repetitions++;
            // Initialize array with random values
            for (int i = 0; i < n; i++) a[i] = rand() % n;
            insertion_sort(a, n);
            if (((double)(clock() - start) / CLOCKS_PER_SEC) > 1.0) break;
        }
        random_duration = ((double)(clock() - start)) / CLOCKS_PER_SEC / repetitions;

        fprintf(fp, "%6d    %f    %f    %f\n", n, reverse_duration, sorted_duration, random_duration);
    }

    fclose(fp);
    return 0;
}
