// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
    char key[100];
    struct element* next;
} element;

int bucketSize, keySize;
element** nodeChain;

int stringToInteger(char* key);

int main() {
    int i, j, homeBucket, currentBucket;
    element* curr;
    FILE* fp = fopen("in.txt", "r");
    if (!fp) {
        printf("Cannot open the file");
        exit(1);
    }

    printf("Input bucket size:");
    scanf("%d", &bucketSize);

    nodeChain = (element**)calloc(bucketSize, sizeof(element*));

    fscanf(fp, "%d", &keySize);

    /* hash table 채우기 */
    for (i = 0; i < keySize; i++) {
        int b;
        char input[100];
        fscanf(fp, "%s", input);

        homeBucket = stringToInteger(input) % bucketSize;

        curr = (element*)calloc(1, sizeof(element));
        strcpy(curr->key, input);
        curr->next = nodeChain[homeBucket];
        nodeChain[homeBucket] = curr;
    }

    /* hash table 출력하기 */
    for (i = 0; i < bucketSize; i++) {
        element* p = nodeChain[i];
        printf("[%2d]:", i);
        while (p != NULL) {
            printf(" [%10s] ", p->key);
            p = p->next;
        }
        printf("\n");
    }

    /* hash table에서 값 검색하기 */
    while (1) {
        char input[100] = { 0, };
        element* p;

        printf("Input string(Q for quit):");
        scanf("%s", input);

        if (strcmp(input, "Q") == 0) {
            printf("Exit\n");
            break;
        }

        homeBucket = stringToInteger(input) % bucketSize;
        int found = 0;
        currentBucket = homeBucket;

        do {
            p = nodeChain[homeBucket];

            while (p != NULL) {
                if (strcmp(p->key, input) == 0) {
                    printf("Success\n");
                    found = 1;
                    break;
                }
                p = p->next;
            }

            currentBucket = (currentBucket + 1) % bucketSize;

        } while (!found && currentBucket != homeBucket);

        if (!found) {
            printf("Fail\n");
        }
    }

    fclose(fp);

    for (i = 0; i < bucketSize; i++) {
        element* p = nodeChain[i];
        while (p != NULL) {
            element* temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(nodeChain);

    return 0;
}

int stringToInteger(char* key) {
    int number = 0;
    while (*key)
        number += *key++;
    return number;
}
