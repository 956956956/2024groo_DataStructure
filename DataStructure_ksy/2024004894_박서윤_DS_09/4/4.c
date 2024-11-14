#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
} Term;

// 새로운 항 생성
Term* create_term(int coeff, int exp) {
    Term* new_term = (Term*)malloc(sizeof(Term));
    new_term->coefficient = coeff;
    new_term->exponent = exp;
    new_term->next = NULL;
    return new_term;
}

// 리스트의 끝에 항을 삽입 (내림차순)
void insert_at_end(Term** head, int coeff, int exp) {
    Term* new_term = create_term(coeff, exp);
    if (*head == NULL) {
        *head = new_term;
    }
    else {
        Term* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_term;
    }
}

void insert_at_beginning(Term** head, int coeff, int exp) {
    Term* new_term = create_term(coeff, exp);
    new_term->next = *head;
    *head = new_term;
}

void print_polynomial(Term* head) {
    while (head != NULL) {
        printf("(%p) +%d*x^%d : %p\n", head, head->coefficient, head->exponent, head->next);
        head = head->next;
    }
    printf("\n");
}

Term* add_polynomials(Term* a, Term* b) {
    Term* result = NULL;
    while (a != NULL && b != NULL) {
        if (a->exponent > b->exponent) {
            insert_at_end(&result, a->coefficient, a->exponent); 
            a = a->next;
        }
        else if (a->exponent < b->exponent) {
            insert_at_end(&result, b->coefficient, b->exponent);  
            b = b->next;
        }
        else {
            int sum_coeff = a->coefficient + b->coefficient;
            if (sum_coeff != 0) {
                insert_at_end(&result, sum_coeff, a->exponent);
            }
            a = a->next;
            b = b->next;
        }
    }
    while (a != NULL) {
        insert_at_end(&result, a->coefficient, a->exponent);
        a = a->next;
    }
    while (b != NULL) {
        insert_at_end(&result, b->coefficient, b->exponent);
        b = b->next;
    }
    return result;
}

void free_polynomial(Term* head) {
    while (head != NULL) {
        Term* temp = head;
        head = head->next;
        free(temp);
    }
}

void read_polynomial_from_file(const char* filename, Term** polynomial) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    char order;
    fscanf(file, " %c", &order);

    int coeff, exp;
    while (fscanf(file, "%d %d", &coeff, &exp) != EOF) {
        if (order == 'a') {
            insert_at_beginning(polynomial, coeff, exp); 
        }
        else if (order == 'd') {
            insert_at_end(polynomial, coeff, exp);
        }
    }

    fclose(file);
}

int main() {
    Term* poly_a = NULL;
    Term* poly_b = NULL;
    Term* poly_c = NULL;

    read_polynomial_from_file("a.txt", &poly_a);
    read_polynomial_from_file("b.txt", &poly_b);

    printf("a :\n");
    print_polynomial(poly_a);

    printf("b :\n");
    print_polynomial(poly_b);

    poly_c = add_polynomials(poly_a, poly_b);
    printf("a+b=c :\n");
    print_polynomial(poly_c);

    free_polynomial(poly_a);
    free_polynomial(poly_b);
    free_polynomial(poly_c);

    return 0;
}