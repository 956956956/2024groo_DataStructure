#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 20


char stack[MAX_STACK_SIZE];
int top = -1;

typedef enum{lparen, rparen, mult, divide, mod, plus, minus, operator, eos} precedence;
int inStackPre[] = { 0, 19, 10, 10, 10, 5 ,5, 0 };
int inComingPre[] = { 20, 19, 10, 10, 10, 5 ,5, 0 };

char pop() {
	return stack[top--];
}

void push(char symbol) {
	stack[++top] = symbol;
	return;
}

precedence getToken(char symbol) {
	switch (symbol) {
	case '(':
		return lparen;
	case ')':
		return rparen;
	case '*':
		return mult;
	case '/':
		return divide;
	case '%':
		return mod;
	case '+':
		return plus;
	case '-':
		return minus;
	case '\0':
		return eos;
	default:
		return operator;
	}
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	char exp[82], tmp;
	int i = 0, end=0;
	fgets(exp, 80, fp);
	printf("%s\n", exp);
	fclose(fp);
	while(!end){
		precedence token = getToken(exp[i]);
		switch (token){
		case lparen:
			push('(');
			break;
		case rparen:
			tmp = pop();
			while (tmp != '(') {
				printf("%c ", tmp);
				tmp = pop();
			}
			break;
		case mult: case divide: case mod: case plus: case minus:
			while (top!=-1&&inStackPre[getToken(stack[top])] >= inComingPre[token])
				printf("%c ", pop());
			push(exp[i]);
			break;
		case eos:
			end = 1;
			break;
		case operator:
			printf("%c ", exp[i]);
		}
		i++;
	}
	while (top != -1) {
		printf("%c ", pop());
	}

	
}