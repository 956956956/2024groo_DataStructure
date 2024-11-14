#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Score {
    int classNum;
    int score;
    struct Score* next;
} Score;

typedef struct {
    Score* top;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, int classNum, int score) {
    Score* newScore = (Score*)malloc(sizeof(Score));
    newScore->classNum = classNum;
    newScore->score = score;
    newScore->next = stack->top;
    stack->top = newScore;
}

void printStack(Stack* stack, int subjectNum) {
    Score* current = stack->top;
    while (current != NULL) {
        printf("%d       %d       %d\n", subjectNum, current->classNum, current->score);
        current = current->next;
    }
    printf("**************************\n");
}

void readDataFromFile(Stack stacks[], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    int subjectNum, classNum, score;
    while (fscanf(file, "%d %d %d", &subjectNum, &classNum, &score) != EOF) {
        push(&stacks[subjectNum], classNum, score);
    }

    fclose(file);
}

int main() {
  
    Stack stacks[3];
    for (int i = 0; i < 3; i++) {
        initStack(&stacks[i]);
    }

    readDataFromFile(stacks, "input.txt");

    printf("과목번호, 학반, 성적\n");
    printf("**************************\n");
    for (int i = 0; i < 3; i++) {
        printStack(&stacks[i], i);
    }

    return 0;
}