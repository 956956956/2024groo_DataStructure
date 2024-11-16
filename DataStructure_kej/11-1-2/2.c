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

void quickSort(int left, int right);

int main() {
	int i;
	FILE* fp = fopen("in3.txt", "r");

	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &num);
	student = (Student*)malloc((num + 1) * sizeof(Student));

	for (i = 1; i <= num; i++)
		fscanf(fp, "%s %d", student[i].name, &student[i].key);

	printf("[Quick Sort]\n");
	quickSort(1, num);
	for (i = 1; i <= num; i++)
		printf("%5s: %5d\n", student[i].name, student[i].key);

	return 0;
}

// rightmost 데이터를 pivot으로 이용하여 nonincreasing order로 quick sort하는 함수
void quickSort(int left, int right) {
	int pivot, i, j;
	Student temp;
	if (left < right) {
		i = left-1; j = right;
		pivot = student[right].key;
		printf("Pivot: %3d\n", pivot);
		do{
			do i++; while (student[i].key > pivot);
			do j--; while (student[j].key < pivot);
			if (i < j) {
				temp = student[i];
				student[i] = student[j];
				student[j] = temp;
			}
		} while (i < j);

		temp = student[right];
		student[right] = student[i];
		student[i] = temp;

		quickSort(left, i-1);
		quickSort(i+1, right);
	}
}