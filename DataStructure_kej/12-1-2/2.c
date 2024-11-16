// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct {
	char name[10];
	int key;
} Student;

int num;
int link[1000] = { 0, };
Student* student;

int rmergeSort(int left, int right);
int listMerge(int start1, int start2);

int main() {
	int i, index;
	FILE* fp = fopen("in.txt", "r");

	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &num);
	student = (Student*)malloc((num + 1) * sizeof(Student));

	for (i = 1; i <= num; i++)
		fscanf(fp, "%s %d", student[i].name, &student[i].key);

	printf("[Recursive merge sort]\n");
	index = rmergeSort(1, num);

	for (i = 1; i <= num; i++) {
		printf("%5s: %5d\n", student[index].name, student[index].key);
		index = link[index];
	}

	return 0;
}

int rmergeSort(int left, int right) {
	if (left >= right) return left;
	int mid = (left + right) / 2;
	return listMerge(rmergeSort(left, mid), rmergeSort(mid + 1, right));
}

int listMerge(int start1, int start2) {
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (student[last1].key >= student[last2].key) {	// non increasing order라도 stable을 위해 = 포함하기!
			link[lastResult] = last1;
			lastResult = last1;
			last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2;
			last2 = link[last2];
		}
	}

	if (last1 == 0)
		link[lastResult] = last2;
	else
		link[lastResult] = last1;

	return link[0];
}