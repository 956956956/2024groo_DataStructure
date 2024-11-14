#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MEMORY_SIZE 10
#define MAX_STACK_SIZE 10
#define MAX_NAME_SIZE 10

typedef struct {
	char name[MAX_NAME_SIZE];
}element;

element memory[MEMORY_SIZE];
int top[MAX_STACK_SIZE];
int boundary[MAX_STACK_SIZE];
int n;


bool isFULL(int i);
bool isEMPTY(int i);
void push(int i, element item);
element pop(int i);
void sprint(int i);

bool isFULL(int i) {
	return top[i] == boundary[i + 1];
}

bool isEMPTY(int i) {
	return top[i] == boundary[i];
}

void push(int i, element item) {
	if (isFULL(i)) {
		printf("Stack %d is Full\n", i);
		return;
	}
	strcpy(memory[++top[i]].name, item.name);
	printf("%s is Pushed in Stack No. %d\n", item.name, i);
}

element pop(int i) {
	if (isEMPTY(i)) {
		printf("Stack %d is Empty\n", i);
		return;
	}
	printf("%s is popped from Stack No. %d\n", memory[top[i]].name, i);
	return memory[top[i]--];
}

void sprint(int i) {
	for (int j = top[i]; j > boundary[i]; j--)
		printf("%s\n", memory[j].name);
}

int main() {
	top[0] = -1;
	boundary[0] = -1;
	element item;
	int idx = 0;
	char order[MAX_NAME_SIZE];

	FILE* fp;

	fp = fopen("input.txt", "r");

	printf("How Manu Stacks ? : ");
	scanf_s("%d", &n);
	printf("\n");

	for (int j = 1; j < n; j++)
		top[j] = boundary[j] = (MEMORY_SIZE / n) * j -1;
	boundary[n] = MEMORY_SIZE - 1;

	while (true) {
		fscanf(fp, "%s %d", order, &idx);

		if (idx >= n)
		{
			printf("stack number error, try again\n");
			fgets(order, sizeof(order), fp);
			continue;
		}
		else if (strcmp(order, "add") == 0) {
			fscanf(fp, "%s", item.name);
			push(idx, item);
		}
		else if (strcmp(order, "delete") == 0) {
			item = pop(idx);
		}
		else if (strcmp(order, "sprint") == 0) {
			printf("\n");
			sprint(idx);
			printf("\n");
		}
		else if (strcmp(order, "quit") == 0) {
			printf("\nProgram end\n");
			for (int j = 0; j < n; j++) {
				printf("\nstack %d :\n", j);
				sprint(j);
				printf("\n");
			}

			break;
		}
		else
			printf("wrong command, try again!!\n");
	}
}