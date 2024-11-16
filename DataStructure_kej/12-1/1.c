// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct {
	char name[10];
	int key;
} Student;

int num;
Student* student;

void iterMergeSort();
void mergePass(Student initList[], Student mergedList[], int n, int s);
void merge(Student initList[], Student mergedList[], int i, int m, int n);

int main() {
	int i;
	FILE* fp = fopen("in.txt", "r");

	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &num);
	student = (Student*)malloc((num + 1) * sizeof(Student));

	for (i = 1; i <= num; i++)
		fscanf(fp, "%s %d", student[i].name, &student[i].key);

	printf("[Iterative merge sort]\n");
	iterMergeSort();

	for (i = 1; i <= num; i++)
		printf("%5s: %5d\n", student[i].name, student[i].key);

	return 0;
}

void iterMergeSort() {
	Student* extra = (Student*)malloc(sizeof(Student) * (num + 1));
	int s = 1;
	while (s < num) {
		printf("    s: %2d\n", s);
		mergePass(student, extra, num, s);
		s *= 2;
		mergePass(extra, student, num, s);
		s *= 2;
	}
}

void mergePass(Student initList[], Student mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else {
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];
	}
}

void merge(Student initList[], Student mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].key >= initList[j].key)	// non increasing order라도 stable을 위해 = 포함하기!
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}

	if (i > m) {
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	}
	else {
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
	}
}