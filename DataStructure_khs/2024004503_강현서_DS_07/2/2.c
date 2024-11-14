#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define MAX_EXPR_SIZE 80
#define MAX_STACK_SIZE 80

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

char expr[MAX_EXPR_SIZE];
int stack[MAX_STACK_SIZE];
int top = -1;

precedence getToken(char* symbol, int* n);
char token2char (int token);
void postfix(char result[]);
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
		return -1;
	return stack[top--];
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	// printf("\n%d : %c\n", *n, (*symbol));
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

char token2char(int token) {
	switch (token) {
	case 0: return '(';
	case 1: return ')';
	case 2: return '+';
	case 3: return '-';
	case 4: return '*';
	case 5: return '/';
	case 6: return '%';
	case 7: return '\0';
	default: return ' ';
	}
}

void postfix(char result[]) {
	char symbol;
	precedence token;
	int n = 0;
	stack[0] = eos;
	top = 0;
	
	int idx = 0;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)
		{
			result[idx++] = symbol;
			result[idx++] = ' ';
		}
		else if (token == rparen) {
			while (stack[top] != lparen)
			{
				result[idx++] = token2char(pop());
				result[idx++] = ' ';
			}
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token])
			{
				result[idx++] = token2char(pop());
				result[idx++] = ' ';
			}
			push(token);
		}
	}
	while ((token = pop()) != eos)
	{
		result[idx++] = token2char(token);
		result[idx++] = ' ';
	}
	result[idx - 1] = '\0';
}

int main() {
	FILE* fp1;
	FILE* fp2;

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	char elm;
	char result[MAX_EXPR_SIZE];

	int i = 0;
	while (true) {
		int ch = fscanf(fp1, "%c", &elm);
		if (ch == EOF)
			break;
		expr[i] = elm;
		i++;
	}
	expr[i] = '\0';

	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("%-20s", "infix expression");
	printf(": %s\n", expr);

	postfix(result);

	printf("%-20s", "postfix expression");
	printf(": %s", result);
	fprintf(fp2, "%s", result);

	fclose(fp1);
	fclose(fp2);
}