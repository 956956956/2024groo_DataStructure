// 2023012565 ������
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

	FILE* fp = fopen("in.txt", "r");	// ���� ����
	if (!fp) {
		puts("Cannot open the file");
		exit(1);
	}

	fscanf(fp, "%d", &size);	// ���� �Է�
	stu = (Student*)malloc(sizeof(Student)*size);	// ���� �Ҵ�
	
	fgets(line, 100, fp);	// ���� �Է�
	while(!feof(fp)) {
		sscanf(line, "%s %d %d", stu[i].name, &stu[i].score, &stu[i].age);
		fgets(line, 100, fp);
		i++;
	}

	printf("�������� �Է�: ");	// ǥ�� �Է�
	scanf("%d", &standard);

	printf("\n90�� �̻��� �л��� ���>>\n");	// ǥ�� ���
	for (i = 0; i < size; i++) {
		if (stu[i].score >= standard)
			printf("�̸�: %s, ����: %d, ����: %d\n", stu[i].name, stu[i].score, stu[i].age);
	}

	fclose(fp);
	free(stu);
	return 0;
}