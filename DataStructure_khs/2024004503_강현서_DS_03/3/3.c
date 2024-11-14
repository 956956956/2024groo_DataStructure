#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char name[100];
int age;
float salary;
}human;

int humansEqual(human* person1, human* person2);

int humansEqual(human* person1, human* person2) {
	if (strcmp(person1, person2))
		return 0;
	
	if (person1->age != person2->age)
		return 0;
	
	if (person1->salary != person2->salary)
		return 0;

	return 1;
}

int main() {
	human person1, person2;

	printf("Input Person1's name, age, salary : \n");
	scanf_s("%[^\n]s", person1.name, sizeof(person1.name));
	scanf_s(" %d", &person1.age);
	scanf_s(" %f", &person1.salary);

	printf("Input Person2's name, age, salary : \n");
	scanf_s(" %[^\n]s", person2.name, sizeof(person2.name));
	scanf_s(" %d", &person2.age);
	scanf_s(" %f", &person2.salary);

	if (humansEqual(&person1, &person2))
		printf("The two human beings are the same");
	else
		printf("The tow human beings are not the same");
}