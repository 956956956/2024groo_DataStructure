#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 3

typedef struct {
	int sub;
	int cls;
	int score;
}element;

typedef struct stack* stackPointer;

typedef struct stack {
	element data;
	stackPointer link;
}stack;

stackPointer top[MAX_STACK];

void push(int i, element item);
element pop(int i);
void prints (int i);

void push(int i, element item) {
	stackPointer temp;
	temp = (stackPointer)malloc(sizeof(*temp));
	if (temp == NULL) return;

	temp->data = item;
	
	temp->link = top[i];
	top[i] = temp;
}

element pop(int i) {
	element item = { -1, -1, -1 };
	stackPointer temp = top[i];

	if (!temp)
		return item;
	
	item = temp->data;
	
	top[i] = temp->link;
	free(temp);

	return item;
}

void prints(int i) {
	element item;
	
	printf("********************\n");
	while (top[i])
	{
		item = pop(i);
		printf("%8d %5d %5d\n", item.sub, item.cls, item.score);
	}
}

int main() {
	element item;
	FILE* fp;
	fp = fopen("input.txt", "r");

	for (int i = 0; i < MAX_STACK; i++)
		top[i] = NULL;

	while (fscanf(fp, "%d %d %d", &item.sub, &item.cls, &item.score) != EOF)
		push(item.sub, item);
	
	fclose(fp);

	printf("과목번호, 학반, 성적\n");

	for (int i = 0; i < MAX_STACK; i++)
		prints(i);
}