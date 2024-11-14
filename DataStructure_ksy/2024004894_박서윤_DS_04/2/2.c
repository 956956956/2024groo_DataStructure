#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 100

typedef struct term {
    int row;
    int col;
    int value;
}term;

void fastTranspose(term a[], term b[]) {
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;

    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < numCols; i++)
            rowTerms[i] = 0;
        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;
        for (i = 1; i < numCols; i++)  // i = 1로 수정
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        for (i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void printMatrix(term a[]) {
    printf("row\tcol\tvalue\n");
    for (int i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n", a[i].row, a[i].col, a[i].value);
    }
}

void saveMatrixToFile(term a[], const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {  // fopen_s 사용
        printf("Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "%d %d %d\n", a[0].row, a[0].col, a[0].value);
    for (int i = 1; i <= a[0].value; i++) {
        fprintf(file, "%d %d %d\n", a[i].row, a[i].col, a[i].value);
    }

    fclose(file);
}

int main() {
    FILE* file;
    term a[MAX_COL], b[MAX_COL];
    int i, numTerms;

    if (fopen_s(&file, "a.txt", "r") != 0) {  // fopen_s 사용
        printf("Error opening input file a.txt\n");
        return 1;
    }

    fscanf(file, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
    numTerms = a[0].value;
    for (i = 1; i <= numTerms; i++) {
        fscanf(file, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
    }
    fclose(file);

    printf("A\n");
    printMatrix(a);

    fastTranspose(a, b);  // 함수 이름 수정

    printf("\nB\n");
    printMatrix(b);

    saveMatrixToFile(b, "b.txt");

    return 0;
}
