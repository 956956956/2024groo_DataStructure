#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_EMPTY(first)(! (first)) // NULL이면 1 NULL이 아니면 0

typedef struct listNode* listPointer;
typedef struct listNode {
    char name[30];
    char company[50];
    char gender[30];
    listPointer link;
} listNode;
listPointer first = NULL;
listPointer first_male = NULL;
listPointer first_female = NULL;

void insert(listPointer* first, listPointer x, listNode data);
void delete(listPointer* first, listPointer trail, listPointer x);
void printList(listPointer first);
listPointer reverseList(listPointer head);
listPointer mergeLists(listPointer male, listPointer female);

int main()
{
    FILE* f;
    listPointer search, search_male = NULL, search_female = NULL;
    listNode data;

    fopen_s(&f, "input.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "cannot open the file\n");
        exit(EXIT_FAILURE);
    }

    fscanf_s(f, "%s %s %s\n", data.name, 30, data.company, 50, data.gender, 30);
    insert(&first, NULL, data);
    search = first;

    while (!feof(f)) {
        fscanf_s(f, "%s %s %s\n", data.name, 30, data.company, 50, data.gender, 30);
        insert(&first, search, data);
        search = search->link;
    }

    fclose(f);

    printf("전체 리스트\n");
    printList(first);
    puts("");


    do {
        strcpy_s(data.name, 30, first->name);
        strcpy_s(data.company, 50, first->company);
        strcpy_s(data.gender, 30, first->gender);

        if (!strcmp(data.gender, "남자\0")) {
            if (first_male == NULL) {
                insert(&first_male, NULL, data);
                search_male = first_male;
            }
            else {
                insert(&first_male, search_male, data);
                search_male = search_male->link;
            }

        }

        else {
            if (first_female == NULL) {
                insert(&first_female, NULL, data);
                search_female = first_female;
            }
            else {
                insert(&first_female, search_female, data);
                search_female = search_female->link;
            }
        }
        delete(&first, NULL, first);
    } while (first != NULL);

    printf("남자 리스트\n");
    printList(first_male);
    puts("");

    printf("여자 리스트\n");
    printList(first_female);

    // 합친 리스트 만들기 및 출력
    listPointer mergedList = mergeLists(first_male, first_female);
    printf("합친 리스트\n");
    printList(mergedList);

    // 역순 리스트 만들기 및 출력
    listPointer reversed = reverseList(mergedList);
    printf("합친 리스트 역순 출력\n");
    printList(reversed);

    return 0;
}

void insert(listPointer* first, listPointer x, listNode data)
{
    listPointer temp;
    temp = malloc(sizeof(*temp));
    strcpy_s(temp->name, 30, data.name);
    strcpy_s(temp->company, 50, data.company);
    strcpy_s(temp->gender, 30, data.gender);

    if (*first == NULL) {
        temp->link = NULL;
        *first = temp;
    }
    else {
        if (x == NULL)
        {
            temp->link = *first;
            *first = temp;
        }
        else {
            temp->link = x->link;
            x->link = temp;
        }
    }
}

void delete(listPointer* first, listPointer trail, listPointer x)
{
    if (trail)
        trail->link = x->link;
    else
        *first = (*first)->link;
    free(x);
}

void printList(listPointer first)
{
    for (; first; first = first->link)
        printf("(%p, %s, %s, %s, %p)\n", first, first->name, first->company, first->gender, first->link);
    printf("\n");
}

// 두 리스트를 합치는 함수
listPointer mergeLists(listPointer male, listPointer female) {
    listPointer merged = NULL, last = NULL;

    // 여성을 먼저 추가
    while (female != NULL) {
        if (merged == NULL) {
            merged = female;
            last = female;
        }
        else {
            last->link = female;
            last = female;
        }
        female = female->link;
    }

    // 남성을 그 다음에 추가
    while (male != NULL) {
        if (merged == NULL) {
            merged = male;
            last = male;
        }
        else {
            last->link = male;
            last = male;
        }
        male = male->link;
    }

    return merged; // 합쳐진 리스트 반환
}

// 리스트를 역순으로 만드는 함수
listPointer reverseList(listPointer head) {
    listPointer prev = NULL;
    listPointer curr = head;
    listPointer next = NULL;

    while (curr != NULL) {
        next = curr->link;
        curr->link = prev;
        prev = curr;
        curr = next;
    }

    return prev; // 역순된 리스트의 첫 번째 노드 반환
}