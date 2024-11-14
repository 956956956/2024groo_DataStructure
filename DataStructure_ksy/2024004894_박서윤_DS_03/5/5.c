#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 100 // size of terms array

typedef struct {
    float coef;
    int expon;
} term;

term terms[MAX_TERMS];

int avail = 0; // index of available term

void attach(float coef, int expon) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

void padd(int startA, int finishA, int startB, int finishB) {
    float coefficient;
    while (startA <= finishA && startB <= finishB) {
        if (terms[startA].expon > terms[startB].expon) {
            attach(terms[startA].coef, terms[startA].expon);
            startA++;
        }
        else if (terms[startA].expon == terms[startB].expon) {
            coefficient = terms[startA].coef + terms[startB].coef;
            if (coefficient) attach(coefficient, terms[startA].expon);
            startA++; startB++;
        }
        else {
            attach(terms[startB].coef, terms[startB].expon);
            startB++;
        }
    }

    // add remaining terms from A and B
    for (; startA <= finishA; startA++) attach(terms[startA].coef, terms[startA].expon);
    for (; startB <= finishB; startB++) attach(terms[startB].coef, terms[startB].expon);
}

void printPoly(int start, int finish) {
    for (int i = start; i <= finish; i++) {
        printf("%.1fx^%d", terms[i].coef, terms[i].expon);
        if (i != finish) printf(" + ");
    }
    printf("\n");
}

int main(void) {
    int numA, numB;
    printf("<< D(x) = A(x) + B(x) >>\n");
    printf("Input the number of items of A(x) : ");
    scanf("%d", &numA);
    printf("Input the number of items of B(x) : ");
    scanf("%d", &numB);

    printf("\ninput in descending order\n");
    printf("coefficient and exponent of A(x) = ");
    for (int i = 0; i < numA; i++) {
        float coef;
        int expon;
        scanf("%f %d", &coef, &expon);
        attach(coef, expon);
    }
    int finishA = avail - 1;
    printf("coefficient and exponent of B(x) = ");
    for (int i = 0; i < numB; i++) {
        float coef;
        int expon;
        scanf("%f %d", &coef, &expon);
        attach(coef, expon);
    }
    int finishB = avail - 1;

    printf("\nA(x) = "); printPoly(0, finishA);
    printf("B(x) = "); printPoly(numA, finishB);
    padd(0, finishA, numA, finishB);
    printf("D(x) = "); printPoly(numA + 1, avail - 1);

    return 0;
}