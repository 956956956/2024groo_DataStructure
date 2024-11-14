#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nodeptr;
typedef struct node {
    int coef;
    int expon;
    nodeptr link;
} node;

nodeptr aPoly = NULL;
nodeptr bPoly = NULL;
nodeptr cPoly = NULL;
nodeptr avail = NULL;

void binsert(nodeptr* avail, int coef, int expon) {
    if (coef == 0) {
        return;
    }
    nodeptr p = (nodeptr)malloc(sizeof(node));
    p->coef = coef;
    p->expon = expon;
    p->link = NULL;
    if (*avail == NULL) {
        *avail = p;
        return;
    }
    else {
        nodeptr tmp = *avail;
        while (tmp->link != NULL) {
            tmp = tmp->link;
        }
        tmp->link = p;
        return;
    }
}

void insert_back(nodeptr* head, int coef, int expon) {
    nodeptr p = (nodeptr)malloc(sizeof(node));
    p->coef = coef;
    p->expon = expon;
    if (*head == NULL) {
        *head = p;
        p->link = *head;
        return;
    }
    else {
        nodeptr tmp = *head;
        p->link = tmp->link;
        tmp->link = p;
        *head = p;
        return;
    }
}

void insert_forward(nodeptr* head, int coef, int expon) {
    nodeptr p = (nodeptr)malloc(sizeof(node));
    p->coef = coef;
    p->expon = expon;
    if (*head == NULL) {
        *head = p;
        p->link = *head;
        return;
    }
    else {
        p->link = (*head)->link;
        (*head)->link = p;
        return;
    }
}

void Nprint(nodeptr* head) {
    nodeptr pre = *head;
    nodeptr cur = *head;
    do {
        cur = cur->link;
        if (cur->coef < 0) {
            printf("(%p : %5dx^%d :  %p)\n", cur, cur->coef, cur->expon, cur->link);
        }
        else if (cur->coef > 0) {
            printf("(%p :    +%dx^%d :  %p)\n", cur, cur->coef, cur->expon, cur->link);
        }
    } while (cur != pre);
    printf("\n");
}

void plus(nodeptr* a, nodeptr* b) {
    nodeptr eap = (*a)->link;
    nodeptr ebp = (*b)->link;
    nodeptr ap = (*a)->link->link;
    nodeptr bp = (*b)->link->link;
    insert_back(&cPoly, eap->coef, eap->expon);
    do {
        if (ap->expon == bp->expon) {
            insert_back(&cPoly, ap->coef + bp->coef, ap->expon);
            ap = ap->link;
            bp = bp->link;
        }
        else if (ap->expon > bp->expon) {
            insert_back(&cPoly, ap->coef, ap->expon);
            ap = ap->link;
        }
        else if (ap->expon < bp->expon) {
            insert_back(&cPoly, bp->coef, bp->expon);
            bp = bp->link;
        }
    } while ((ap != eap) && (bp != ebp));
}

void make_avail(nodeptr* head) {
    nodeptr p = (*head)->link->link;
    nodeptr tmp = (*head)->link->link;
    do {
        binsert(&avail, p->coef, p->expon);
        p = p->link;
    } while (p != tmp);
}

void Aprint(nodeptr* head) {
    nodeptr tmp = *head;
    while (tmp != NULL) {
        if (tmp->coef < 0) {
            printf("(%p : %5dx^%d :  %p)\n", tmp, tmp->coef, tmp->expon, tmp->link);
        }
        else {
            printf("(%p :    +%dx^%d :  %p)\n", tmp, tmp->coef, tmp->expon, tmp->link);
        }
        tmp = tmp->link;
    }
    printf("\n");
}

void delete_all(nodeptr* head) {
    nodeptr tmp = *head;
    while (tmp != NULL) {
        nodeptr next = tmp->link;
        free(tmp);
        tmp = next;
    }
    *head = NULL;
}

void all_Adelete(nodeptr* head) {
    nodeptr p = *head;
    while (p != NULL) {
        nodeptr tmp = p->link;
        free(p);
        p = tmp;
    }
    *head = NULL;
}

void all_delete(nodeptr* head) {
    nodeptr p = (*head)->link;
    while (p != *head) {
        nodeptr next = p->link;
        free(p);
        p = next;
    }
    free(*head);
    *head = NULL;
}

int main() {
    char astr[10];
    char bstr[10];
    int an1, an2 = -1;
    int bn1, bn2 = -1;
    char ac, bc;
    char trash[10];
    FILE* ain = fopen("a.txt", "r");
    FILE* bin = fopen("b.txt", "r");
    fscanf(ain, "%c", &ac);
    if (ac == 'a') {
        while (1) {
            if (!fgets(astr, 10, ain)) { break; }
            sscanf(astr, "%d %d", &an1, &an2);
            insert_forward(&aPoly, an1, an2);
        }
        nodeptr p = aPoly;
        while (p->link != aPoly) { p = p->link; }
        aPoly = p;
    }
    else if (ac == 'd') {
        while (1) {
            if (!fgets(astr, 10, ain)) { break; }
            sscanf(astr, "%d %d", &an1, &an2);
            insert_back(&aPoly, an1, an2);
        }
    }
    printf("    a :\n");
    Nprint(&aPoly);
    fscanf(bin, "%c", &bc);
    if (bc == 'a') {
        while (1) {
            if (!fgets(bstr, 10, bin)) { break; }
            sscanf(bstr, "%d %d", &bn1, &bn2);
            insert_forward(&bPoly, bn1, bn2);
        }
        nodeptr p = bPoly;
        while (p->link != bPoly) { p = p->link; }
        bPoly = p;
    }
    else if (bc == 'd') {
        while (1) {
            if (!fgets(bstr, 10, bin)) { break; }
            sscanf(bstr, "%d %d", &bn1, &bn2);
            insert_back(&bPoly, bn1, bn2);
        }
    }
    printf("    b :\n");
    Nprint(&bPoly);
    plus(&aPoly, &bPoly);
    printf("a+b=c :\n");
    Nprint(&cPoly);
    make_avail(&cPoly);
    make_avail(&bPoly);
    make_avail(&aPoly);
    printf("avail :\n");
    Aprint(&avail);
    all_delete(&cPoly);
    all_delete(&aPoly);
    all_delete(&bPoly);
    all_Adelete(&avail);
    fclose(ain);
    fclose(bin);
}
