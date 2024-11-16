#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5

typedef struct data{
	int class;
	int score;
} element;

typedef struct stack* stackPointer;
typedef struct stack{
	element* data;
	stackPointer link;
};
stackPointer top[MAX_STACK_SIZE];


void push(int , element* );
element* pop(int );
void sprint(int );

int main() {
	FILE* fp = fopen("input.txt","r");
	int i, sNum;
	for (i = 0; i < MAX_STACK_SIZE; i++)
		top[i] = NULL;
	while (!feof(fp)) {
		element* item = (element*)malloc(sizeof(struct data));
		fscanf(fp, "%d %d %d", &sNum, &item->class, &item->score);
		push(sNum, item);
	}
	printf("과목번호, 학반, 성적\n");
	for (i = 0; i <= 2; i++)
		sprint(i);

}

void push(int i, element* item) {
	stackPointer tmp;
	tmp = (stackPointer)malloc(sizeof(struct stack));
	tmp->data = item;
	tmp->link = top[i];
	top[i] = tmp;
}


element* pop(int i) {
	stackPointer tmp;
	element* item;
	tmp = top[i];
	item = top[i]->data;
	top[i] = top[i]->link;
	free(tmp);
	return item;
}


void sprint(int i) {
	printf("**************************\n");
	stackPointer p = top[i];
	while (p != NULL) {
		printf("%5d%5d%5d\n", i, p->data->class, p->data->score);
		p = p->link;
	}
}


