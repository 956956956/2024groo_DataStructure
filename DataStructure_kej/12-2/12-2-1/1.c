// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void heapSort(char* a[], int n);
void adjust(char* a[], int root, int n);

int main() {
    char* arr[] = { NULL, "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune", "ceres", "pluto", "haumea", "quaoar" };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("[Heap sort]\n");
    heapSort(arr, n - 1);
    for (int i = 1; i < n; i++) {
        printf("%s ", arr[i]);
    }
    return 0;
}

void heapSort(char* a[], int n) {
    int i;
    char* temp;

    for (i = n / 2; i > 0; i--) {
        adjust(a, i, n);
    }
    for (i = n - 1; i > 0; i--) {
        temp = a[1];
        a[1] = a[i + 1];
        a[i + 1] = temp;
        adjust(a, 1, i);
    }
}

void adjust(char* a[], int root, int n) {
    int child;
    char* temp = a[root];

    child = 2 * root;
    while (child <= n) {
        if (child < n && strcmp(a[child], a[child + 1]) > 0) {  // strcmp 함수로 key 값 비교
            child++;
        }
        if (strcmp(temp, a[child]) <= 0) { // strcmp 함수로 key 값 비교
            break;
        }
        a[child / 2] = a[child];
        child *= 2;
    }
    a[child / 2] = temp;
}
