#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 30

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

typedef struct {
	element* stack;
	int top;
	int stackSize;
} multStack;

multStack ary[10];
int aryIdx = 0;

void sprint(int stackId) {
	printf("\n");
	for (int i = ary[stackId].top; i >= 0; i--) {
		printf("%s\n", ary[stackId].stack[i].name);
	}
	printf("\n");
}

void add(int stackId, char name[]) {
	if (ary[stackId].top == ary[stackId].stackSize - 1) {
		printf("stack %d is full\n", stackId);
	}
	else {
		strcpy(ary[stackId].stack[++ary[stackId].top].name, name);
		printf("%s is Pushed in Stack No. %d\n", name, stackId);
	}
}

element delete(int stackId) {
	if (ary[stackId].top == -1) {
		printf("stack %d is empty\n", stackId);
	}
	else {
		printf("%s is popped from Stack No. %d\n",
			ary[stackId].stack[ary[stackId].top].name, stackId);
		return ary[stackId].stack[ary[stackId].top--];
	}
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	char com[5], tmpName[MAX_NAME_SIZE], trash[80];
	int stackId, S = 10, n, i = 0 , size;
	printf("How Many Stacks ? : ");
	scanf("%d", &n);
	size = S / n;
	while (S != 0) {
		if (S - size < size) {
			ary[aryIdx].stack = (element*)malloc(S * sizeof(element));
			ary[aryIdx].stackSize = S;
			ary[aryIdx++].top = -1;
			S = 0;
		}
		else {
			ary[aryIdx].stack = (element*)malloc(size * sizeof(element));
			ary[aryIdx].stackSize = size;
			ary[aryIdx++].top = -1;
			S -= size;
		}
	}
	printf("\n");


	while (!feof(fp)) {
		fscanf(fp, "%s", com);
		if (strcmp(com, "add") == 0) {
			fscanf(fp, "%d %s", &stackId, tmpName);
			if (stackId >= aryIdx)
				printf("stack number error, try again\n");
			else
				add(stackId, tmpName);
		}
		else if (strcmp(com, "delete") == 0) {
			fscanf(fp, "%d", &stackId);
			if (stackId >= aryIdx)
				printf("stack number error, try again\n");
			else
				delete(stackId);
		}
		else if (strcmp(com, "sprint") == 0) {
			fscanf(fp, "%d", &stackId);
			if (stackId >= aryIdx)
				printf("stack number error, try again\n");
			else
				sprint(stackId);
		}
		else if (strcmp(com, "quit") == 0) {
			printf("\nProgram end\n\n");
			for (int i = 0; i < n; i++) {
				printf("stack %d :", i);
				sprint(i);
			}
			exit(0);
		}
		else {
			printf("wrong command, try again!!\n\n");
			fgets(trash, 50, fp);
		}
	}
}