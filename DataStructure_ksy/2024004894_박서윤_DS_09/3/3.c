#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer first = NULL;

// 함수 선언
void insert(listPointer* first, int data);
void delete(listPointer* first, listPointer trail, listPointer x);
void printList(listPointer first);
void deleteAll(listPointer* first);

int main()
{
    FILE* f;
    listPointer search, trail;
    int data[12];

    fopen_s(&f, "input.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "cannot open the file\n");
        exit(EXIT_FAILURE);
    }

    // 파일에서 데이터 읽기
    fscanf_s(f, "%d %d %d %d %d %d\n", data, data + 1, data + 2, data + 3, data + 4, data + 5);
    fscanf_s(f, "%d %d %d %d %d %d\n", data + 6, data + 7, data + 8, data + 9, data + 10, data + 11);
    fclose(f);

    // 데이터를 리스트에 삽입
    for (int i = 0; i < 12; i++) {
        insert(&first, data[i]);
    }

    // Circularly Linked List 출력
    printf("The Circularly Linked List contains:\n");
    printList(first);

    // 성적이 홀수인 노드 삭제
    while (first != NULL && first->data % 2 != 0) {
        delete(&first, NULL, first);
    }

    trail = first;
    search = first ? first->link : NULL;
    while (search != NULL && search != first) {
        if (search->data % 2 != 0) {  // 홀수인 경우
            delete(&first, trail, search);
            search = trail->link;
        }
        else {
            trail = search;
            search = search->link;
        }
    }

    printf("\nAfter deleting nodes with odd value\n\n");
    printf("The Circularly Linked List contains:\n");
    printList(first);

    // 모든 노드 삭제
    deleteAll(&first);

    return 0;
}

void insert(listPointer* first, int data)
{
    listPointer temp = malloc(sizeof(*temp));
    temp->data = data;

    if (*first == NULL) {  // 리스트가 비어있는 경우
        temp->link = temp;
        *first = temp;
    }
    else {
        listPointer last = *first;
        while (last->link != *first)
            last = last->link;
        temp->link = *first;
        last->link = temp;
    }
}

void delete(listPointer* first, listPointer trail, listPointer x)
{
    if (*first == x) {
        listPointer last = *first;
        while (last->link != *first)
            last = last->link;
        if (last == *first) {  // 리스트에 하나의 노드만 있는 경우
            free(x);
            *first = NULL;
        }
        else {
            last->link = x->link;
            *first = x->link;
            free(x);
        }
    }
    else {
        trail->link = x->link;
        free(x);
    }
}

void printList(listPointer first)
{
    if (first == NULL) return;

    listPointer temp = first;
    do {
        printf("(%p, %4d, %p)\n", temp, temp->data, temp->link);
        temp = temp->link;
    } while (temp != first);
    printf("\n");
}

void deleteAll(listPointer* first)
{
    if (*first == NULL) return;

    listPointer temp = *first;
    listPointer next;
    do {
        next = temp->link;
        free(temp);
        temp = next;
    } while (temp != *first);

    *first = NULL;
}
