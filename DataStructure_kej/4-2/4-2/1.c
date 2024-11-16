// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>

/* 스택의 자료구조 */
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

precedence stack[MAX_STACK_SIZE];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
int top = 0;
char expr[100];

/* postfix 관련 함수*/
void postfix(void);
precedence getToken(char* symbol, int* n);
void printToken(precedence token);

/* stack을 다루는 함수 */
void push(precedence item);
precedence pop();
void stackFull();
int isEmpty();

int main() {
	FILE* fp = fopen("infix.txt", "r");

	if (!fp) {
		puts("Cannot open the file.");
		exit(1);
	}

	fscanf(fp, "%s", expr);

	while (!feof(fp)) {
		printf("Infix: %s\n", expr);
		printf("Postfix: ");
		postfix();
		printf("\n");
		fscanf(fp, "%s", expr);
	}
	
	fclose(fp);
	return 0;
}

/* postfix 관련 함수 */
void postfix(void) {
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)	// token이 피연산자일 때
			printf("%c", symbol);
		else if (token == rparen) {		// token이 연산자 중 오른쪽 괄호일 때
			while (stack[top] != lparen) {
				printToken(pop());
				if (top == 0 && stack[top] != lparen) {
					printf("\n괄호 오류");
					break;
				}
			}
			if (top == 0 && stack[top] != lparen)
				break;
			pop();
		}
		else {		// token이 연산자일 때
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos) {
		printToken(token);
		if (token == lparen) {
			printf("\n괄호 오류");
			break;
		}
	}
	printf("\n");
}

precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
		case '(': return lparen; break;
		case ')': return rparen; break;
		case '+': return plus; break;
		case '-': return minus; break;
		case '/': return divide; break;
		case '*': return times; break;
		case '%': return mod; break;
		case '\0': return eos; break;
		default: return operand; break;
	}
}

void printToken(precedence token) {
	switch (token) {
		case lparen: printf("("); break;
		case rparen: printf(")"); break;
		case plus: printf("+"); break;
		case minus: printf("-"); break;
		case times: printf("*"); break;
		case divide: printf("/"); break;
		case mod: printf("%%"); break;
		default: break;
	}
}

/* stack 처리 함수들 */
void push(precedence item) {	// stack에 값 집어넣기
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

precedence pop() {		// stack에서 값 빼오기
	if (!isEmpty())
		return stack[top--];
	else
		return eos;
}

void stackFull() {		// stack이 꽉 찼는가?
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

int isEmpty() {		// stack이 비었는가?
	if (top == -1) {
		printf("Error : Stack is empty!\n");
		return 1;
	}
	return 0;
}