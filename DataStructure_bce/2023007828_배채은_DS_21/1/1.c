#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* list;
void adjust(int list[], int root, int n); //�θ� �ڽ� ���ؼ� max heap ����(������ root ���)
void printList(int list[], int n);
void firstheap(int list[], int n); //max heap�� ���� �� ó����
void heapSort(int list[], int n); //����Ʈ 
//max heap���� ��Ʈ�� �迭 ������ �̵��ϰ� �� ũ�� �ϳ� ���̰� ���� �κ��� ����

int main() {
	FILE* fp;
	FILE* fpo;
	int i, n;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &n);
	list = malloc(sizeof(int) * (n+1));
	for (i = 1; i <= n; i++)
		fscanf(fp, "%d", &list[i]);

	printf("<<<<<<<<<<<< Input List >>>>>>>>>>>>\n");
	printList(list, n);

	printf("\n\n<<<<<<< executing heap sort >>>>>>>\n");
	firstheap(list, n);

	printf("after initialization of max heap...\n");
	printList(list, n);
	printf("\n\n");

	heapSort(list, n);
	printf("\n<<<<<<<<<<< Sorted List >>>>>>>>>>>\n");
	printList(list, n);

	fpo = fopen("output.txt", "w");
	for (i = 1; i <= n; i++)
		fprintf(fpo, "%d ", list[i]);
	fclose(fpo);

	free(list);
}


void adjust(int list[], int root, int n) {
	int child = 2 * root;
	int temp = list[root];
	while (child <= n) {
		if (child < n && list[child] < list[child + 1])
			child++;
		if (list[child] > temp) {
			list[child/2] = list[child];
			child *= 2;
		}
		else {
			break;
		}
	}
	list[child / 2] = temp;
}


void firstheap(int list[], int n) {
	for (int i = n / 2; i > 0; i--)
		adjust(list, i, n);
} 

void heapSort(int list[], int n) {
	int tmp;
	for (int i =n; i > 1; i--) {
		tmp = list[1];
		list[1] = list[i];
		list[i] = tmp;
		adjust(list, 1, i - 1); // �� ũ�� �ϳ� ���̱�

		printf("\nstep  %d: ��� %d : ", n - i + 1, tmp);
		for (int j = 1; j <= i - 1; j++)
			fprintf(stdout, "%3d ", list[j]);
	}
}

void printList(int list[], int n) {
	for (int i = 1; i <= n; i++)
		fprintf(stdout, "%d ", list[i]);
}