/*3. [구조체] 두개의 구조체(human) 변수를 사용하여, 두 구조체 값이 같은지 비교하는 함수(int hmansEqual)를
다음과 같이 정의하여 실행의 예와 같이 프로그램을 작성 하시오.
int hmansEqual(humanBing *person1, humanBeing *person2);
두개의 구조체값이 같으면 1, 다르면 0을 return*/

#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct humanBing{
    char name[50];
	int age;
	float salary;
}humanBing;

int humansEqual(humanBing* person1, humanBing* person2);

int main() {
    humanBing person1, person2;

    printf("Input person1's name, age, salary:\n");
    gets_s(person1.name, sizeof(person1.name));
    scanf_s("%d %f", &person1.age, &person1.salary);

    getchar();
    
    printf("Input person2's name, age, salary:\n");
    gets_s(person2.name, sizeof(person2.name));
    scanf_s("%d %f", &person2.age, &person2.salary);

    getchar();

    if (humansEqual(&person1, &person2))
        printf("The two human beings are the same\n");
    else
        printf("The two human beings are not the same\n");
    return 0;
}

int humansEqual(humanBing* person1, humanBing* person2) {
    if (strcmp(person1->name, person2->name) != 0)
        return FALSE;

    if (person1->age != person2->age)
        return FALSE;

    if (person1->salary != person2->salary)
        return FALSE;

    return TRUE;
}