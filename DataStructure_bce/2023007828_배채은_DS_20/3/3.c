#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int cnt = 0, n;
int* list;
void merge_sort(int list[], int left, int right);
void merge(int list[], int left, int mid, int right);
void printList(int a[], int n);

int main() {
	FILE* fp;
	int i;
	if ((fp = fopen("input.txt", "r")) == NULL) {
		fprintf(stderr, "file open error");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &n);
	list = malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		fscanf(fp, "%d", &list[i]);
	fclose(fp);

	printf("<<<<<<<<<<<< Input List >>>>>>>>>>>>\n");
	for (i = 0; i < n; i++)
		fprintf(stdout, "%3d ", list[i]);

	printf("\n\n<<<<< execution itterative merge sort >>>>>");
	merge_sort(list, 0, n - 1);

	printf("\n\n<<<<<<<<<<<< Sorted List >>>>>>>>>>>>\n");
	for (i = 0; i < n; i++)
		fprintf(stdout, "%3d ", list[i]);
	free(list);
}


/*void merge_sort(int list[], int left, int right) {
	int middle;
	if (left < right) {
		middle = (left + right) / 2;
		merge_sort(list, left, middle);
		merge_sort(list, middle + 1, right);
		merge(list, left, middle, right);
	}
}*/

void merge_sort(int list[], int left, int right) {
	int k;
	for (int i = 1; i < n; i *= 2) {
		printf("\n\n%12s : %d\n", "segment size", i);
		printf("%12s : ", "a");
		printList(list, n);
		for (int j = left; j <= right; j += i * 2) {
			merge(list, j, j + i - 1, (j + i * 2 - 1 < right ? j + i * 2 - 1 : right));
			//세그먼트의 시작, 첫번째 세그먼트의 마지막, 두번째 세그먼트의 마지막 또는 배열 마지막		
		}

		printf("\n%12s : ", "temp");
		printList(list, n);

	}
}

void merge(int list[], int left, int mid, int right) {
	int sorted[MAX_SIZE];
	int i, j, k, t;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	
	for (t = j; t <= right; t++)
		sorted[k++] = list[t];
	for (t = i; t <= mid; t++)
		sorted[k++] = list[t];

	for (t = left; t <= right; t++)
		list[t] = sorted[t];

}

void printList(int a[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%4d", a[i]);
	}
}