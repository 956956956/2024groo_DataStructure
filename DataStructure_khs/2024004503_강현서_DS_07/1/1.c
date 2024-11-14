#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define MAX_EXPR_SIZE 80
#define MAX_STACK_SIZE 80

typedef enum {
	plus, minus, times, divide, mod, eos, operand
}precedence;

char expr[MAX_EXPR_SIZE];
int stack[MAX_STACK_SIZE];
int top = -1;

precedence getToken(char* symbol, int* n);
int eval();
bool isFULL();
bool isEMPTY();
void push(int item);
int pop();

bool isFULL() {
	return top >= MAX_STACK_SIZE - 1;
}

bool isEMPTY() {
	return top < 0;
}

void push(int item) {
	if (isFULL())
		return;

	stack[++top] = item;
}
int pop() {
	if (isEMPTY())
		return;
	return stack[top--];
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
		case '+': return plus;
		case '-': return minus;
		case '*': return times;
		case '/':  return divide;
		case '%': return mod;
		case '\0': return eos;
		default: return operand;
	}
}

int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);

	while (token != eos) {
		if (token == operand)
			push(symbol - '0');
		else {
			op2 = pop();
			op1 = pop();

			switch (token) {
			case plus: push(op1 + op2);
				break;
			case minus: push(op1 - op2);
				break;
			case times: push(op1 * op2);
				break;
			case divide: push(op1 / op2);
				break;
			case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

int main() {
	FILE* fp1;
	FILE* fp2;

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("ouput.txt", "w");

	char elm;
	int result;

	printf("postfix expression :");
	fprintf(fp2, "postfix expression :");

	int i = 0;
	while (true) {
		int ch = fscanf(fp1, "%c ", &elm);
		if (ch == EOF)
			break;
		expr[i] = elm;
		printf("%2c", expr[i]);
		fprintf(fp2, "%2c", expr[i]);
		i++;
	}
	
	result = eval();

	printf("\nthe evaluation value : %d", result);
	fprintf(fp2, "\nthe evaluation value : %d", result);

	fclose(fp1);
	fclose(fp2);
}