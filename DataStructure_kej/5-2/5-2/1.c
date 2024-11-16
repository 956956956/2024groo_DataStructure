// 2023012565 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int QueueSize, Crear = 0, Cfront = 0, Lrear = -1, Lfront = -1;
int* CQueue, * LQueue;	// Circular Queue, List Queue 

/* Circular Queue �Լ��� */
void addCQ(int num);
void deleteCQ();
void printCQ();

/* List Queue �Լ��� */
void addLQ(int num);
void deleteLQ();
void printLQ();

int main() {
	FILE* fp = fopen("in1.txt", "r");
	int num;
	char sign;

	if (!fp) {
		puts("Cannot open the file.");
		exit(1);
	}

	/* Queue ���� �Ҵ� */
	fscanf(fp, "%d", &QueueSize);
	CQueue = (int*)malloc(sizeof(int) * QueueSize);
	LQueue = (int*)malloc(sizeof(int) * QueueSize);
	printf("Queue size: %d\n", QueueSize);

	while (!feof(fp)) {
		fscanf(fp, "%c ", &sign);
		fscanf(fp, "%c", &sign);

		if (sign == 'a') {				/* Queue - Add */
			fscanf(fp, "%d", &num);
			printf("\nadd %d...", num);
			printf("\n[Circular queue] ");
			addCQ(num);
			printf("\n[List queue] ");
			addLQ(num);

		}
		else if (sign == 'd') { 		/* Queue - Delete */
			printf("\ndelete...");

			printf("\n[Circular queue] ");
			deleteCQ();
			printf("\n[List queue] ");
			deleteLQ();
		}
	}

	fclose(fp);
	free(CQueue);
	free(LQueue);
	return 0;
}

/* Circular Queue - add �Լ� */
void addCQ(int num) {
	if ((Crear + 1) % QueueSize == Cfront)	// ���� ����....
		printf("Full.");
	else {
		Crear = (Crear + 1) % QueueSize;
		CQueue[Crear] = num;
		printCQ();
	}
		
}
/* Circular Queue - delete �Լ� */
void deleteCQ() {
	if (Cfront == Crear)
		printf("Empty.");
	else {
		Cfront = (Cfront + 1) % QueueSize;
		printCQ();
	}
}
/* Circular Queue - print �Լ� */
void printCQ() {
	int start = (Cfront) % QueueSize;

	if (Cfront == Crear) {
		printf("Empty.");
		return;
	}
	
	do {
		start = (start + 1) % QueueSize;
		printf("%d ", CQueue[start]);
		if (start == Crear)
			break;
	} while (start != Cfront);
}

/* List Queue - add �Լ� */
void addLQ(int num) {
	if (Lrear == (QueueSize - 1))
		printf("Full.");
	else {
		LQueue[++Lrear] = num;
		printLQ();
	}
}
/* List Queue - delete �Լ� */
void deleteLQ() {
	if (Lfront == Lrear)
		printf("Empty.");
	else {
		Lfront++;
		printLQ();
	}
}
/* List Queue - print �Լ� */
void printLQ() {
	int start = Lfront+1;

	if (Lfront == Lrear) {
		printf("Empty.");
		return;
	}

	while (start <= Lrear)
		printf("%d ", LQueue[start++]);
}