#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_SIZE 20
#define MAX_STACK_SIZE 10

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element m_stack[MAX_STACK_SIZE];
int top[MAX_STACK_SIZE];
int bottom[MAX_STACK_SIZE];
int s_num;
int size;

void sprint(int no) {
	printf("\n");
	for (int i = bottom[no]; i >= top[no] + 1; i--)
		printf("%s\n", m_stack[i].name);
	printf("\n");
}

void push(int no, element tmp) {
	if (bottom[no] == top[no + 1])
		printf("Stack %d is Full\n", no);
	else {
		m_stack[++bottom[no]] = tmp;
		printf("%s is Pushed in Stack No. %d\n", tmp.name, no);
	}

	return;
}

void pop(int no) {
	if (bottom[no] == top[no]) {
		printf("Stack %d is Empty\n", no);
		exit(0);
	}
	else {
		printf("%s is popped in Stack No. %d\n", m_stack[bottom[no]].name, no);
		bottom[no]--;
	}
}

int main() {
	int s_num, i, id;
	char com[10];
	FILE* fp = fopen("input.txt", "r");
	printf("How Many Stacks ? : ");
	scanf("%d", &s_num);
	printf("\n");
	size = 10 / s_num;
	for (i = 0; i < s_num; i++) {
		top[i] = bottom[i] = -1;
	}
	for (i = 0; i < s_num; i++) {
		top[i] += i * size;
		bottom[i] = top[i];
	}
	top[i] = MAX_STACK_SIZE;

	while (!feof(fp)) {
		fscanf(fp, "%s", com);
		if (strcmp(com, "add") == 0){
			element tmp;
			fscanf(fp, "%d %s", &tmp.id, tmp.name);
			if (tmp.id >= s_num) {
				printf("stack number error, try again\n");
				continue;
			}
			push(tmp.id, tmp);
		}
		else if (strcmp(com, "sprint") == 0) {
			fscanf(fp, "%d", &id);
			if (id >= s_num) {
				printf("stack number error, try again\n");
				continue;
			}
			sprint(id);
		}
		else if (strcmp(com, "delete") == 0) {
			fscanf(fp, "%d", &id);
			if (id >= s_num) {
				printf("stack number error, try again\n");
				continue;
			}
			pop(id);
		}
		else if (strcmp(com, "quit") == 0) {
			printf("Program end\n\n");
			for (i = 0; i < s_num; i++) {
				printf("stack %d :", i);
				sprint(i);
				printf("\n");
			}
			exit(0);

		}
		else {
			printf("command error, try again\n");
		}
	}
}