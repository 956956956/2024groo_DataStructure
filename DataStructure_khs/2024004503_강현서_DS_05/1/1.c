#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 50

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

void empty(int top);
void full(int top, element stack[]);
void push(int id, char name[], int *top, element stack[]);
void pop(int *top);
void sprint(int top, element stack[]);
void wrong();

void empty(int top) {
	printf("stack is empty, cannot delete element\n");
	exit(0);
}

void full(int top, element stack[]) {
	printf("stack is full, cannot add element\n");
	printf("current stack elements :\n");
	sprint(top, stack);
	exit(0);
}

void push(int id, char name[], int *top, element stack[]) {
	if ((*top) >= MAX_STACK_SIZE - 1)
		full(*top, stack);

	stack[++(*top)].id = id;
	strncpy(stack[*top].name, name, MAX_NAME_SIZE - 1);
}

void pop(int* top) {
	if ((*top) < 0)
		empty(*top);

	(*top) -= 1;
}

void sprint(int top, element stack[]) {
	for (int i = top; i >= 0; i--)
		printf("%d %s\n", stack[i].id, stack[i].name);
	printf("\n");
}

void wrong() {
	printf("wrong command! try again!\n");
}

int main() {
	element stack[MAX_STACK_SIZE];
	int top = -1;
	int bottom = -1;

	FILE* fp;
	fp = fopen("input.txt", "r");

	char order[MAX_NAME_SIZE];
	int nid;
	char nname[MAX_NAME_SIZE] = { 0 };

	while (1) {
		fscanf(fp, "%s", order);

		if (strcmp(order, "push") == 0) {
			fscanf(fp, "%d", &nid);
			fscanf(fp, "%s", nname);

			push(nid, nname, &top, stack);
		}
		else if (strcmp(order, "pop") == 0) {
			pop(&top);
		}
		else if (strcmp(order, "sprint") == 0) {
			printf("\n");
			sprint(top, stack);
		}
		else if (strcmp(order, "quit") == 0) {
			printf("end of program!!");
			break;
		}
		else {
			wrong();
		}
	}

	fclose(fp);
}