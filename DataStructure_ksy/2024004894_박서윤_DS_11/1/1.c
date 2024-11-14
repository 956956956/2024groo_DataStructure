#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;
treePointer root = NULL;

treePointer createNode(char data);
treePointer createBinTree();

void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main(void) {
    printf("Creating a binary tree\n\n");
    root = createBinTree();

    printf("Three binary tree traversals\n");

    printf("%20s: \n", "Inorder traversal");
    inorder(root);
    printf("\n");

    printf("%20s: \n", "Preorder traversal");
    preorder(root);
    printf("\n");

    printf("%20s: \n", "Postorder traversal");
    postorder(root);
    printf("\n");

    return 0;
}

treePointer createNode(char data) {
    treePointer pNode = (treePointer)malloc(sizeof(node)); // Correcting malloc usage
    if (pNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    pNode->data = data;
    pNode->leftChild = NULL;
    pNode->rightChild = NULL;

    return pNode;
}

treePointer createBinTree() {
    treePointer pNodeA, pNodeB, pNodeC, pNodeD, pNodeE;
    pNodeA = createNode('A');
    pNodeB = createNode('B');
    pNodeC = createNode('C');
    pNodeD = createNode('D');
    pNodeE = createNode('E');

    pNodeA->leftChild = pNodeB;
    pNodeA->rightChild = pNodeC;
    pNodeB->leftChild = pNodeD;
    pNodeB->rightChild = pNodeE;

    return pNodeA;
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%p : %p %c %p)\n", ptr->data, (void*)ptr->leftChild, ptr->data, (void*)ptr->rightChild);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr) {
    if (ptr) {
        printf("%p : %p %c %p)\n", ptr->data, (void*)ptr->leftChild, ptr->data, (void*)ptr->rightChild);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%p : %p %c %p)\n", ptr->data, (void*)ptr->leftChild, ptr->data, (void*)ptr->rightChild);
    }
}
