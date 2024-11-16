#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR 80
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
precedence stack[100];
int top = -1;

char expr[MAX_EXPR];
int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };
precedence getToken(char* symbol, int* n);
void push(precedence t);
void printToken(precedence t);
void postfix();

int main() {
	FILE* fp;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	fgets(expr, MAX_EXPR, fp);
	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("infix expression	: %s\n", expr);
	printf("postfix expression	: ");
	postfix();
	puts("");
	fclose(fp);

	return;
}

void push(precedence t) {
	if (top == 99) {
		fprintf(stderr, "stack is full\n");
		exit(1);
	}
	stack[++top] = t;
}
precedence pop() {
	if (top == -1) {
		fprintf(stderr, "stack is empty\n");
		exit(1);
	}
	return stack[top--];
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '%': return mod;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '\0': return eos;
	default: return operand;
	}
}
void printToken(precedence t) {
	switch (t) {
	case mod:
		printf("%% ");
		return;
	case plus:
		printf("+ ");
		return;
	case minus:
		printf("- ");
		return;
	case times:
		printf("* ");
		return;
	case divide:
		printf("/ ");
		return;
	default: return;
	}
}
void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	stack[++top] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (expr[n - 1] == ' ') continue;
		if (token == operand) {
			printf("%c", expr[n - 1]);
			if (!(expr[n] >= '0' && expr[n] <= '9')) printf(" ");
		}
		else if (token == rparen) {
			while (stack[top] != lparen) {
				printToken(pop());
			}
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token]) printToken(pop());
			push(token);
		}
	}
	while (stack[top] != eos) {
		printToken(pop());
	}
}
