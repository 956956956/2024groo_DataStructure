#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 11
#define BUCKET 11

typedef struct HASH {
	int key;
	char item[10];
}HASH;

HASH table[MAX_SIZE];

int hash(int k, int b);
unsigned int stringToInt(char* key);
void search(int k);
void init();

int main() {
	FILE* fp;

	char tmp[10];
	int idx, num;
	init();

	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}

	printf("input strings : ");
	while (fscanf(fp, "%s", tmp) == 1) {
		printf("%s ", tmp);
		num = stringToInt(tmp);
		idx = hash(num, BUCKET);

		while (table[idx].key != 0) {
			idx = (idx + 1) % MAX_SIZE;
		}

		strcpy(table[idx].item, tmp);
		table[idx].key = num;
	}
	printf("\n\n	    item    key\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("ht[%2d] : ", i);
		if (table[i].key != 0)
			printf("%8s %5d", table[i].item, table[i].key);
		puts("");
	}

	printf("\nstring to search >> ");
	scanf("%s", tmp);
	search(stringToInt(tmp));

}


int hash(int k, int b) {
	return k % b;
}

void search(int k) {
	int homB, curB;
	int found = 0, count = 0;
	homB = hash(k, BUCKET);
	for (curB = homB; table[curB].key != k;) {
		curB = (curB)+1 % BUCKET;
		count++;
		if (curB == homB || count >= BUCKET)
			break;
	}
	if (table[curB].key != k)
		printf("it doesn't exist!\n");
	else
		printf("item: %s, key : %d, the number of comparisions : %d\n"
			, table[curB].item, table[curB].key, count);
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
	for (int i = 0; i < MAX_SIZE; i++)
		table[i].key = 0;
}