#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_STACK_SIZE 80
#define MAX_EXPR_SIZE 80

typedef enum{plus, minus, mult, divide, mod, eos, operand } precedence;

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;

void push(int num) {
	stack[++top] = num;
}

int pop() {
	return stack[top--];
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	precedence tmp;
	switch (*symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return mult;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	case ' ': tmp = getToken(symbol, n); return tmp;
	default: return operand;
	}
}

int main() {
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	precedence token;
	char symbol;
	int n = 0;
	fgets(expr, 82, fp1);
	fclose(fp1);

	token = getToken(&symbol, &n);
	while (token!=eos) {
		if (token == operand)
			push(symbol - '0');
		else {
			int op2 = pop();
			int op1 = pop();
			switch (token) {
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case mult: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1 % op2); break;
			}
		}
		token = getToken(&symbol, &n);
	}

	int res = pop();
	fprintf(fp2, "postfix expression : %s\n", expr);
	fprintf(fp2, "the evaluation value : %d", res);
	fclose(fp2);

	printf("postfix expression : %s\n", expr);
	printf("the evaluation value : %d", res);
}