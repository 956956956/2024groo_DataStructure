#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

// 환형 큐가 비어 있는지 확인
int is_empty() {
    return front == rear;
}

// 환형 큐가 가득 찼는지 확인
int is_full() {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

// 큐에 데이터를 추가하는 함수
void add(int id, char name[]) {
    if (is_full()) {
        printf("queue is full, not added.\n");
    }
    else {
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        queue[rear].id = id;
        strcpy(queue[rear].name, name);
    }
}

// 큐에서 데이터를 삭제하는 함수
void delete() {
    if (is_empty()) {
        printf("queue is empty\n");
    }
    else {
        front = (front + 1) % MAX_QUEUE_SIZE;
    }
}

// 큐의 내용을 출력하는 함수
void qprint() {
    if (is_empty()) {
        printf("queue is empty\n");
    }
    else {
        int i = (front + 1) % MAX_QUEUE_SIZE;
        while (i != (rear + 1) % MAX_QUEUE_SIZE) {
            printf("%d, %s\n", queue[i].id, queue[i].name);
            i = (i + 1) % MAX_QUEUE_SIZE;
        }
        printf("\n");
    }
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    char command[10];
    int id;
    char name[MAX_NAME_SIZE];

    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "add") == 0) {
            fscanf(file, "%d %s", &id, name);
            add(id, name);
        }
        else if (strcmp(command, "delete") == 0) {
            delete();
        }
        else if (strcmp(command, "qprint") == 0) {
            qprint();
        }
        else {
            printf("wrong command! try again!\n");
            // 잘못된 명령에 대해 추가로 처리하지 않고 넘어감
            fscanf(file, "%*[^\n]"); // 남은 부분을 무시하고 다음 줄로 이동
        }
    }

    fclose(file);
    return 0;
}
