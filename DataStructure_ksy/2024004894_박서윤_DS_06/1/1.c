#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100

// 학생 정보를 담는 구조체
typedef struct {
    int id; // unique id
    char name[MAX_NAME_SIZE];
} element;

// 환형 큐 구조체
typedef struct {
    element* queue; // 동적 할당된 배열
    int capacity;   // 큐의 최대 크기
    int front;      // 첫 번째 요소의 인덱스
    int rear;       // 마지막 요소의 인덱스
    int size;       // 큐에 있는 요소의 개수
} CircularQueue;

// 큐 초기화 함수
void initQueue(CircularQueue* q, int capacity) {
    q->queue = (element*)malloc(capacity * sizeof(element));
    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

// 큐 메모리 해제 함수
void freeQueue(CircularQueue* q) {
    free(q->queue);
}

// 큐가 비어 있는지 확인하는 함수
int isEmpty(CircularQueue* q) {
    return q->size == 0;
}

// 큐가 가득 찼는지 확인하는 함수
int isFull(CircularQueue* q) {
    return q->size == q->capacity;
}

// 큐 확장 함수 (크기를 두 배로 늘림)
void expandQueue(CircularQueue* q) {
    int newCapacity = q->capacity * 2;
    element* newQueue = (element*)malloc(newCapacity * sizeof(element));

    // 기존 큐의 요소들을 새 큐로 복사
    for (int i = 0; i < q->size; i++) {
        newQueue[i] = q->queue[(q->front + i) % q->capacity];
    }

    free(q->queue);
    q->queue = newQueue;
    q->capacity = newCapacity;
    q->front = 0;
    q->rear = q->size;

    // 큐 확장 메시지 출력
    printf("queue capacity is doubled, current queue capacity is %d.\n", q->capacity);
}

// 큐에 요소 추가 (add)
void enqueue(CircularQueue* q, int id, char* name) {
    if (isFull(q)) {
        expandQueue(q);
    }
    q->queue[q->rear].id = id;
    strncpy(q->queue[q->rear].name, name, MAX_NAME_SIZE - 1);
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

// 큐에서 요소 제거 (delete)
void dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue empty\n");
        return;
    }
    q->front = (q->front + 1) % q->capacity;
    q->size--;
}

// 큐의 내용을 출력하는 함수 (qprint)
void printQueue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % q->capacity;
        printf("%d, %s", q->queue[idx].id, q->queue[idx].name);
        if (i < q->size - 1) {
            printf("\n"); // 마지막 요소가 아니라면 줄바꿈 추가
        }
    }
    printf("\n");
}

// 명령어 처리 함수
void processCommands(CircularQueue* q, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char command[20];
    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "add") == 0) {
            int id;
            char name[MAX_NAME_SIZE];
            fscanf(file, "%d %s", &id, name);
            enqueue(q, id, name);
        }
        else if (strcmp(command, "delete") == 0) {
            dequeue(q);
        }
        else if (strcmp(command, "qprint") == 0) {
            printQueue(q);
            printf("\n");  // qprint 호출 후 두 줄 띄움
        }
        else if (strcmp(command, "quit") == 0) {
            printf("end of program!\n");
            break;
        }
        else {
            printf("wrong command! try again!\n");
            fscanf(file, "%*[^\n]"); // 현재 줄의 나머지를 무시하고 넘어감
        }
    }

    fclose(file);
}

int main() {
    CircularQueue q;
    initQueue(&q, 2); // 초기 크기를 2로 설정

    processCommands(&q, "input.txt");

    freeQueue(&q); // 메모리 해제
    return 0;
}
