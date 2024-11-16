// 2023012565 김은정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bucketSize, keySize;
char*** hashTable;

int stringToInteger(char* key);

int main() {
    int i, j, homeBucket, currentBucket;
    FILE* fp = fopen("in.txt", "r");
    if (!fp) {
        printf("Cannot open the file");
        exit(1);
    }

    printf("Input bucket size:");
    scanf("%d", &bucketSize);

    hashTable = (char***)malloc(bucketSize * sizeof(char**));
    for (i = 0; i < bucketSize; i++) {
        hashTable[i] = (char**)malloc(3 * sizeof(char*));
        for (j = 0; j < 3; j++) {
            hashTable[i][j] = (char*)malloc(100 * sizeof(char));
            hashTable[i][j][0] = '\0';
        }
    }

    fscanf(fp, "%d", &keySize);

    /* hash table 채우기 */
    for (i = 0; i < keySize; i++) {
        int b;
        char input[100];
        fscanf(fp, "%s", input);
        homeBucket = stringToInteger(input) % bucketSize;

        for (currentBucket = homeBucket; ;) {
            b = 0;
            if (hashTable[currentBucket][b][0] == 0)
                break;
            b++;
            if (hashTable[currentBucket][b][0] == 0)
                break;
            b++;
            if (hashTable[currentBucket][b][0] == 0)
                break;
            currentBucket = (currentBucket + 1) % bucketSize;

            if (currentBucket == homeBucket) {
                printf("Hash table is full.\n");
                exit(1);
            }
        }
        strcpy(hashTable[currentBucket][b], input);
    }

    /* hash table 출력하기 */
    for (i = 0; i < bucketSize; i++) {
        printf("[%2d]:", i);
        for (j = 0; j < 3; j++) {
            if (hashTable[i][j][0] == '\0')
                break;
            printf("%13s", hashTable[i][j]);
        }
        printf("\n");
    }

    /* hash table에서 값 검색하기 */
    while (1) {
        char input[100] = { 0, };
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
            for (int b = 0; b < 3; b++) {
                if (strcmp(input, hashTable[currentBucket][b]) == 0) {
                    printf("Success\n");
                    found = 1;
                    break;
                }
            }

            currentBucket = (currentBucket + 1) % bucketSize;

        } while (!found && currentBucket != homeBucket);

        if (!found) {
            printf("Fail\n");
        }
    }

    fclose(fp);

    for (i = 0; i < bucketSize; i++) {
        for (j = 0; j < 3; j++) {
            free(hashTable[i][j]);
        }
        free(hashTable[i]);
    }
    free(hashTable);

    return 0;
}

int stringToInteger(char* key) {
    int number = 0;
    while (*key)
        number += *key++;
    return number;
}
