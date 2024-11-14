#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 50

typedef struct {
    int id;
    char name[MAX_NAME_SIZE]; // last name
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

void push(int id, const char* name) {
    if (top >= MAX_STACK_SIZE - 1) {
        // Stack is full
        printf("stack is full, cannot element.\ncurrent elements:\n");
        for (int i = top; i >= 0; i--) {  // 역순으로 출력
            printf("%d %s\n", stack[i].id, stack[i].name);
        }
        return;
    }
    top++;
    stack[top].id = id;
    strncpy(stack[top].name, name, MAX_NAME_SIZE);
}

void pop() {
    if (top < 0) {
        // Stack is empty
        printf("Wrong command! try again!\n");
        return;
    }
    top--;
}

void sprint() {
    if (top < 0) {
        printf("Stack is empty.\n");
        return;
    }
    for (int i = top; i >= 0; i--) {
        printf("%d %s\n", stack[i].id, stack[i].name);
    }
    printf("\n"); // 출력 뒤에 빈 줄 추가
}

int main() {
    FILE* file;
    fopen_s(&file, "input.txt", "r");
    if (!file) {
        perror("Failed to open input.txt");
        return 1;
    }

    char command[10];
    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "push") == 0) {
            int id;
            char name[MAX_NAME_SIZE];
            fscanf(file, "%d %s", &id, name);
            push(id, name);
        }
        else if (strcmp(command, "pop") == 0) {
            pop();
        }
        else if (strcmp(command, "sprint") == 0) {
            sprint();
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }
        else {
            printf("Wrong command! try again!\n\n");
            // Consume the rest of the line if the command is wrong
            char buffer[100];
            fgets(buffer, sizeof(buffer), file);
        }
    }

    fclose(file);
    return 0;
}
