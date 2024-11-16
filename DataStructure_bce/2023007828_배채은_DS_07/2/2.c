#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_STACK_SIZE 80
#define MAX_EXPR_SIZE 82

typedef enum { lparen, rparen, plus, minus, mult, divide, mod, eos, operand } precedence;

char stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top = -1;
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence getToken(char symbol) {
	switch (symbol) {
	case '+': return plus;
	case '-': return minus;
	case '*': return mult;
	case '/': return divide;
	case '%': return mod;
	case '(': return lparen;
	case ')': return rparen;
	case '\0': return eos;
	default: return operand;
	}
}

void push(char symbol) {
	stack[++top] = symbol;
}

char pop() {
	return stack[top--];
}

void postfix() {
	FILE* fp2 = fopen("output.txt", "w");
	precedence token;
	int n = 0;
	char symbol = expr[n++];
	token = getToken(symbol);
	while (token != eos) {
		if (token == operand)
			fprintf(fp2, "%c ", symbol);
		else if (token == rparen) {
			while (1) {
				char tmp = pop();
				if (tmp == '(') break;
				fprintf(fp2, "%c ", tmp);
			}
		}
		else {
			while(isp[getToken(stack[top])]>=icp[token])
				fprintf(fp2, "%c ", pop());
			push(symbol);
		}
		symbol = expr[n++];
		token = getToken(symbol);
	}
	while((symbol = pop())!='\0')
		fprintf(fp2, "%c ", symbol);
	fclose(fp2);

	fp2 = fopen("output.txt", "r");
	char res[MAX_EXPR_SIZE];
	fgets(res, 80, fp2);
	fclose(fp2);

	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("infix expression : %s\n", expr);
	printf("postfix expression : %s\n", res);
}



int main() {
	FILE* fp1 = fopen("input.txt", "r");
	fgets(expr, 80, fp1);
	fclose(fp1);
	postfix();
}
