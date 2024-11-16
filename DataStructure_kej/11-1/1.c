// 2023012565 ±Ë¿∫¡§
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct {
	char name[10];
	int key;
} Student;

int num;
Student* student;

void insertSort();
void insert(Student e,int i);

int main() {
	int i;
	FILE* fp = fopen("in1.txt", "r");

	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &num);
	student = (Student*)malloc((num+1) * sizeof(Student));

	for (i = 1; i <= num; i++)
		fscanf(fp, "%s %d", student[i].name, &student[i].key);

	printf("[Insert Sort]\n");
	insertSort();
	for (i = 1; i <= num; i++)
		printf("%5s: %5d\n", student[i].name, student[i].key);

	return 0;
}

void insertSort() {
	int j;
	for (j = 2; j <= num; j++) {
		Student temp = student[j];
		insert(temp, j - 1);
	}
}
void insert(Student e, int i) {
	student[0] = e;
	while (e.key > student[i].key) {
		student[i + 1] = student[i];
		i--;
	}
	student[i + 1] = e;
}