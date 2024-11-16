#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

typedef struct human {
	char name[84];
	int age;
	int salary;
}humanBeing;


int humansEqual(humanBeing* person1, humanBeing* person2) {
	if (strcmp(person1->name, person2->name))
		return FALSE;
	if (person1->age != person2->age)
		return FALSE;
	if (person1->salary != person2->salary)
		return FALSE;
	return TRUE;
}

int main() {
	humanBeing person1, person2;
	printf("Input person1's name, age, salary :\n");
	gets(person1.name);
	scanf("%d %d", &person1.age, &person1.salary);
	printf("Input person2's name, age, salary :\n");
	scanf("\n");
	gets(person2.name);
	scanf("%d %d", &person2.age, &person2.salary);
	printf("The two human beings are ");
	if (!humansEqual(&person1, &person2))
		printf("not ");
	printf("the same");
}