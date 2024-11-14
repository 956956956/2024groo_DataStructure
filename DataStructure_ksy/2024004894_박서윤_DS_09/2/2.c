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
    Score* front;
    Score* rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, int classNum, int score) {
    Score* newScore = (Score*)malloc(sizeof(Score));
    newScore->classNum = classNum;
    newScore->score = score;
    newScore->next = NULL;  // 새 노드는 큐의 끝이므로 next는 NULL이어야 함

    if (queue->rear == NULL) {  // 큐가 비어 있으면 front와 rear가 모두 새 노드를 가리킴
        queue->front = queue->rear = newScore;
    }
    else {  // rear가 가리키는 노드 뒤에 새 노드를 추가
        queue->rear->next = newScore;
        queue->rear = newScore;  // rear를 새 노드로 갱신
    }
}

void dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty, nothing to dequeue.\n");
        return;
    }

    Score* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {  // 큐가 비었을 경우 rear도 NULL로 설정
        queue->rear = NULL;
    }

    free(temp);
}

void printQueue(Queue* queue, int subjectNum) {
    Score* current = queue->front;
    while (current != NULL) {
        printf("%d       %d       %d\n", subjectNum, current->classNum, current->score);
        current = current->next;
    }
    printf("**************************\n");
}

void readData(Queue queues[], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    int subjectNum, classNum, score;
    while (fscanf(file, "%d %d %d", &subjectNum, &classNum, &score) != EOF) {
        enqueue(&queues[subjectNum], classNum, score);  // enqueue로 데이터 추가
    }
    fclose(file);
}

int main() {
    Queue queues[3];  // 3개의 큐
    for (int i = 0; i < 3; i++) {
        initQueue(&queues[i]);
    }

    readData(queues, "input.txt");

    printf("과목번호, 학반, 성적\n");
    printf("**************************\n");
    for (int i = 0; i < 3; i++) {
        printQueue(&queues[i], i);
    }

    return 0;
}
