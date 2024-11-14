#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20
#define MAX_LEN 100

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

int front = -1;
int rear = -1;
element queue[MAX_QUEUE_SIZE];

int queueEmpty() {
    return front == rear;
}

int queueFull() {
    return rear == MAX_QUEUE_SIZE - 1;
}

void shiftQueue() {
    printf("data shift\n");
    int size = rear - front;
    for (int i = 0; i < size; i++) {
        queue[i] = queue[front + 1 + i];
    }
    front = -1;
    rear = size - 1;
}

void addq(element e) {
    if (queueFull()) {
        if (front == -1) {
            fprintf(stderr, "queue is full, not added\n");
            return;
        }
        else {
            shiftQueue();
        }
    }
    queue[++rear] = e;
}

element deleteq() {
    if (queueEmpty()) {
        fprintf(stderr, "queue is empty, cannot delete element.\n");
        element empty = { 0, "" };
        return empty;
    }
    return queue[++front];
}

void qprint() {
    if (queueEmpty()) {
        printf("queue is empty\n");
        return;
    }
    for (int i = front + 1; i <= rear; i++) {
        printf("%d %s\n", queue[i].id, queue[i].name);
    }
}

int main() {
    char* delimiter = " \n";  // delimiter for tokenizing
    char* context;
    char* op = NULL;  // push or pop
    element student;
    FILE* fp;
    char line[MAX_LEN];


    fopen_s(&fp, "input.txt", "r");
    if (fp == NULL) exit(1);

    while (fgets(line, MAX_LEN, fp)) {
        op = strtok_s(line, delimiter, &context);

        if (!strcmp(op, "add")) {
            sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));
            addq(student);
        }
        else if (!strcmp(op, "delete")) {
            student = deleteq();
        }
        else if (!strcmp(op, "qprint")) {
            qprint();
            printf("\n");
        }
        else {
            printf("wrong command! try again!\n\n");
        }
    }

    fclose(fp);

    return 0;
}
