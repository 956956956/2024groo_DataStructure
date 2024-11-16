#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKET 8

typedef struct HASH {
	int key;
}HASH;

HASH table[BUCKET];
int randNum[BUCKET];
int temp[BUCKET];

int hash(int k, int b);
unsigned int stringToInt(char* key);
void search(int k);
void init();

int main() {
	FILE* fp;

	int tmp, seed;
	int idx, num, i = 0;
	init();

	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}


	printf("key sequence from file : ");
	while (fscanf(fp, "%d", &temp[i]) == 1) {
		printf("%5d", temp[i++]);
	}
	printf("\ninput seed >> ");
	scanf("%d", &seed);
	srand(seed);
	printf("\n");
	for (int k = 1; k < BUCKET; k++) {
		randNum[k] = rand() % (BUCKET - 1) + 1;
		for (int j = 1; j < k; j++) {
			if (randNum[k] == randNum[j]) k--;
		}
	}
	for (int j = 1; j < BUCKET; j++) printf("randNum[%d] : %3d\n", j, randNum[j]);


	for(int j=0;j<i;j++){
		int tmp = temp[j];
		idx = hash(tmp, BUCKET);
		int n = 1, org = idx;
		while (table[idx].key != 0) {
			idx = (org + randNum[n++]) % BUCKET;
		}

		table[idx].key = tmp;
	}

	printf("\n\n	    key\n");
	for (int i = 0; i < BUCKET; i++) {
		printf("ht[%2d] : ", i);
		if (table[i].key != 0)
			printf("%5d", table[i].key);
		puts("");
	}

	while (1) {
		printf("\ninput 0 to quit");
		printf("\nkey to search >> ");
		scanf("%d", &tmp);
		if (tmp == 0) break;
		search(tmp);
		puts("");
	}

}


int hash(int k, int b) {
	return k % b;
}


void search(int k) {
	int homB = hash(k, BUCKET);
	int curB = hash(homB, BUCKET);
	int i = 1;
	while (table[curB].key && table[curB].key != k) {
		curB = hash(homB + randNum[i++], BUCKET);
	}
	if (table[curB].key != k)
		printf("it doesn't exist!\n");
	else
		printf("key : %d, the number of comparisions : %d\n"
			, table[curB].key, i);
}

unsigned int stringToInt(char* key)
{/* simple additive approach to create a natural number
that is within the integer range */
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

void init() {
	for (int i = 0; i < BUCKET; i++)
		table[i].key = 0;
}