#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20


typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
top = -1;

void sprint() {
	for (int i = top; i >= 0; i--) {
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
	printf("\n\n");
}

void push(int id, char name[]) {
	if (top == MAX_STACK_SIZE-1) {
		printf("stack is full, cannot add element\n");
		printf("current stack elements : \n");
		sprint();
		exit(0);
	}
	stack[++top].id = id;
	strcpy(stack[top].name, name);
}

element pop() {
	if (top == -1) {
		printf("stack is empty, cannot delete element\n");
		exit(0);
	}
	return stack[top--];
}


int main() {
	FILE* fp = fopen("input.txt", "r");
	char com[5], tmpName[MAX_NAME_SIZE], trash[80];
	int tmpId;
	while (!feof(fp)) {
		fscanf(fp, "%s", com);
		if (strcmp(com, "push") == 0) {
			fscanf(fp, "%d %s", &tmpId, tmpName);
			push(tmpId, tmpName);
		}
		else if (strcmp(com, "pop") == 0) {
			pop();
		}
		else if (strcmp(com, "sprint") == 0) {
			sprint();
		}
		else if (strcmp(com, "quit") == 0) {
			exit(0);
		}
		else {
			printf("wrong command! try again!\n\n");
			fgets(trash, 50, fp); 
		}
	}
}