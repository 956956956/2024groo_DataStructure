// 2023012565 ±Ë¿∫¡§
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    int key;
} Student;

int num;
Student* student, * extra;

void rmergeSort(int left, int right);
void merge(int left, int mid, int right);

int main() {
    int i;
    FILE* fp = fopen("in.txt", "r");

    if (!fp) {
        printf("Cannot open the file.");
        exit(1);
    }

    fscanf(fp, "%d", &num);
    student = (Student*)malloc((num + 1) * sizeof(Student));
    extra = (Student*)malloc((num + 1) * sizeof(Student));

    for (i = 1; i <= num; i++)
        fscanf(fp, "%s %d", student[i].name, &student[i].key);

    printf("[Recursive merge sort]\n");
    rmergeSort(1, num);

    for (i = 1; i <= num; i++)
        printf("%5s: %5d\n", student[i].name, student[i].key);

    fclose(fp);
    free(student);
    free(extra);
    return 0;
}

void rmergeSort(int left, int right) { // recursive merge sort
    if (left < right) {
        int mid = (left + right) / 2;
        rmergeSort(left, mid); 
        rmergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (student[i].key >= student[j].key)  // non-increasing order
            extra[k++] = student[i++];
        else
            extra[k++] = student[j++];
    }

    while (i <= mid) {
        extra[k++] = student[i++];
    }

    while (j <= right) {
        extra[k++] = student[j++];
    }

    for (i = left; i <= right; i++) {
        student[i] = extra[i];
    }
}
