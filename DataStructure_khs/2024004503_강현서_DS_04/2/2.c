#include <stdio.h>

typedef struct {
	int col;
	int row;
	int value;
} term;

void TransTerm(term a[], term b[]);
void print_term(term a[]);

void TransTerm(term a[], term b[]) {
	int rowTerms[10] = { 0 }, startPos[10];
	int numCol = a[0].col, numTerm = a[0].value;

	b[0].row = numCol;
	b[0].col = a[0].row;
	b[0].value = numTerm;

	if (numTerm > 0) {
		for (int i = 1; i <= numTerm; i++)
			rowTerms[a[i].row]++;

		startPos[0] = 1;

		for (int i = 1; i < numCol; i++)
			startPos[i] = startPos[i - 1] + rowTerms[i - 1];

		int indx = 0;
		for (int i = 1; i <= numTerm; i++) {
			indx = startPos[a[i].row]++;
			b[indx].row = a[i].col;
			b[indx].col = a[i].row;
			b[indx].value = a[i].value;
		}
	}
}

void print_term(term a[]) {
	int indx = 1;
	for (int i = 0; i < a[0].col; i++) {
		for (int j = 0; j < a[0].row; j++) {
			if ((i == a[indx].col) && (j == a[indx].row)) {
				printf("%4d", a[indx].value);
				indx++;
			}
			else
				printf("%4d", 0);
		}
		printf("\n");
	}
}

int main() {
	term a[10];
	term b[10] = { 0 };

	FILE* fp1, * fp2;

	fopen_s(&fp1, "a.txt", "r");
	fopen_s(&fp2, "b.txt", "w");

	for (int i = 0; i < 9; i++) {
		fscanf_s(fp1, "%d", &a[i].col);
		fscanf_s(fp1, "%d", &a[i].row);
		fscanf_s(fp1, "%d", &a[i].value);
	}

	TransTerm(a, b);

	for (int i = 0; i < 9; i++) {
		fprintf(fp2, "%4d %4d %4d\n", b[i].col, b[i].row, b[i].value);
	}

	printf("A\n");
	print_term(a);
	
	printf("B\n");
	print_term(b);
}