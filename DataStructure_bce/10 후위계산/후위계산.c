#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 20


int stack[MAX_STACK_SIZE];
int top = -1;

int pop() {
	return stack[top--];
}

void push(int num) {
	stack[++top] = num;
	return;
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	char exp[82], ch;
	fgets(exp, 80, fp);
	printf("%s\n", exp);
	fclose(fp);
	char* token;
	char* delimiter = " ";
	token = strtok(exp, delimiter);
	while (token != NULL) {
		ch = token[0];
		if (isdigit(ch))
			push(ch - '0');
		else {
			int op2 = pop();
			int op1 = pop();
			switch (ch) {
			case '+':
				push(op1 + op2); break;
			case '-':
				push(op1 - op2); break;
			case '*':
				push(op1 * op2); break;
			case '/':
				push(op1 / op2); break;
			case '%':
				push(op1 % op2); break;
			default:
				break;
			}
		}
		token = strtok(NULL, delimiter);
	}
	printf("%d", pop());
}