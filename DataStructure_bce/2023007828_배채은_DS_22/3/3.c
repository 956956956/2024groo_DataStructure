#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 11
#define BUCKET 11

typedef struct HASH* hashPointer;
typedef struct HASH {
	int key;
	char item[10];
	hashPointer link;
}HASH;

hashPointer table[MAX_SIZE];

int hash(int k, int b);
unsigned int stringToInt(char* key);
void search(int k);
void insert(int idx, char* tmp, int num);

int main() {
	FILE* fp;
	char tmp[10];
	int idx, num;

	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}

	printf("input strings : ");
	while (fscanf(fp, "%s", tmp) == 1) {
		printf("%s ", tmp);
		num = stringToInt(tmp);
		idx = hash(num, BUCKET);
		insert(idx, tmp, num);
	}
	printf("\n\n	   item   key\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("ht[%2d] : ", i);
		hashPointer p = table[i];
		while (p != NULL) {
			printf(" (%s %d) ", p->item, p->key);
			p = p->link;
		}
		puts("");
	}
	
	while (1) {
		printf("input \"quit\" to quit");
		printf("\nstring to search >> ");
		scanf("%s", tmp);
		if (strcmp(tmp, "quit") == 0) break;
		search(stringToInt(tmp));
		puts("");
	}

}

void insert(int idx, char* tmp, int num) {
	hashPointer p = table[idx];
	hashPointer new = malloc(sizeof(HASH));
	strcpy(new->item, tmp);
	new->key = num;
	new->link = NULL;
	if (p == NULL)
		table[idx] = new;
	else {
		while (p->link != NULL)
			p = p->link;
		p->link = new;
	}
}

int hash(int k, int b) {
	return k % b;
}

void search(int k) {
	int homB = hash(k, BUCKET);
	int curB = homB;
	int count = 0;
	hashPointer p;

	while (table[curB] != NULL) {
		for (p = table[curB]; p != NULL; p = p->link) {
			count++;
			if (p->key == k) {
				printf("item: %s, key : %d, the number of comparisons : %d\n"
					, p->item, p->key, count);
				return;
			}
		}
		curB = (curB + 1) % BUCKET;
		if (curB == homB) break;
	}
	printf("it doesn't exist!\n");
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
	for (int i = 0; i < MAX_SIZE; i++) {
		table[i]->key = 0;
		table[i] = NULL;
	}
}