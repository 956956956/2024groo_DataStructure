// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct{
	int grade;
	char class;
	int num;
} Student;

int size, *link, first = 1;	// first를 각 함수마다 만들지 말고 하나로 공유!!
Student* stu;

int GradixSort();
int CradixSort();
int NradixSort();

int main() {
	int i, index;
	FILE* fp = fopen("in.txt", "r");
	if (!fp) {
		printf("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%d", &size);
	stu = (Student*)malloc((size+1) * sizeof(Student));

	/* link setting */
	link = (int*)malloc((size+1) * sizeof(int));
	for (i = 1; i < size; i++)
		link[i] = i + 1;
	link[size] = 0;

	for (i = 1; i <= size; i++)
		fscanf(fp, "%d%c%d", &stu[i].grade, &stu[i].class, &stu[i].num);

	index = NradixSort();
	index = CradixSort();
	index = GradixSort();

	for (i = 1; i <= size; i++) {
		printf("[%d%c%02d] ", stu[index].grade, stu[index].class, stu[index].num);
		index = link[index];
	}

	fclose(fp);
	free(stu);
	free(link);
	return 0;
}
/* 학년 순서로 Radix Sort하는 함수 */
int GradixSort() {
	int front[4], rear[4];
	int i, bin, current, last;

	for (bin = 0; bin < 4; bin++)
		front[bin] = 0;

	for (current = first; current; current = link[current]) {
		bin = stu[current].grade;
		if (front[bin] == 0)
			front[bin] = current;
		else
			link[rear[bin]] = current;
		rear[bin] = current;
	}

	for (bin = 0; !front[bin]; bin++);
	first = front[bin]; last = rear[bin];
	
	for (bin++; bin < 4; bin++) {
		if (front[bin]) {
			link[last] = front[bin];
			last = rear[bin];
		}
	}
	link[last] = 0;

	return first;
}
/* 반 순서로 Radix Sort하는 함수 */
int CradixSort() {
	int front[7], rear[7];
	int i, bin, current, last;

	for (bin = 0; bin < 7; bin++)
		front[bin] = 0;

	for (current = first; current; current = link[current]) {
		bin = stu[current].class - 'A';
		if (front[bin] == 0)
			front[bin] = current;
		else
			link[rear[bin]] = current;
		rear[bin] = current;
	}

	for (bin = 0; !front[bin]; bin++);
	first = front[bin]; last = rear[bin];

	for (bin++; bin < 7; bin++) {
		if (front[bin]) {
			link[last] = front[bin];
			last = rear[bin];
		}
	}
	link[last] = 0;

	return first;
}
/* 학번 순서로 Radix Sort하는 함수 */
int NradixSort() {
	int front[21], rear[21];
	int i, bin, current, last;

	for (bin = 0; bin < 21; bin++)
		front[bin] = 0;

	for (current = first; current; current = link[current]) {
		bin = stu[current].num;
		if (front[bin] == 0)
			front[bin] = current;
		else
			link[rear[bin]] = current;
		rear[bin] = current;
	}

	for (bin = 0; !front[bin]; bin++);
	first = front[bin]; last = rear[bin];

	for (bin++; bin < 21; bin++) {
		if (front[bin]) {
			link[last] = front[bin];
			last = rear[bin];
		}
	}

	link[last] = 0;
	return first;
}