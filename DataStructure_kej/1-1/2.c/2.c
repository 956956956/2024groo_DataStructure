// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char name[20];
	int score;
	int age;
} Student;

int main() {
	int i = 0, size, standard;
	char line[100];
	Student *stu;

	FILE* fp = fopen("in.txt", "r");	// 파일 열기
	if (!fp) {
		puts("Cannot open the file");
		exit(1);
	}

	fscanf(fp, "%d", &size);	// 파일 입력
	stu = (Student*)malloc(sizeof(Student)*size);	// 동적 할당
	
	fgets(line, 100, fp);	// 파일 입력
	while(!feof(fp)) {
		sscanf(line, "%s %d %d", stu[i].name, &stu[i].score, &stu[i].age);
		fgets(line, 100, fp);
		i++;
	}

	printf("기준점수 입력: ");	// 표준 입력
	scanf("%d", &standard);

	printf("\n90점 이상인 학생들 명단>>\n");	// 표준 출력
	for (i = 0; i < size; i++) {
		if (stu[i].score >= standard)
			printf("이름: %s, 성적: %d, 나이: %d\n", stu[i].name, stu[i].score, stu[i].age);
	}

	fclose(fp);
	free(stu);
	return 0;
}