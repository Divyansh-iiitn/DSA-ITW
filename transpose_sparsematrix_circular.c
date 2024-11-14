#include <stdio.h>
#include <stdlib.h>

struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
};

struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = newNode;  
    return newNode;
}

struct Node* insertElement(struct Node* head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
    if (!head) {
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    newNode->next = head;  
    return head;
}

struct Node* transposeSparseMatrix(struct Node* head) {
    struct Node* transposedHead = NULL;
    if (!head) return NULL;

    struct Node* temp = head;
    do {
        transposedHead = insertElement(transposedHead, temp->col, temp->row, temp->value);
        temp = temp->next;
    } while (temp != head);

    return transposedHead;
}

void printSparseMatrix(struct Node* head) {
    if (!head) {
        printf("Sparse matrix is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Row\tCol\tValue\n");
    do {
        printf("%d\t%d\t%d\n", temp->row, temp->col, temp->value);
        temp = temp->next;
    } while (temp != head);
}

int main() {
    struct Node* sparseMatrix = NULL;

    /* Example sparse matrix (3x3):
       0 0 3
       4 0 0
       0 5 0 */

    sparseMatrix = insertElement(sparseMatrix, 0, 2, 3);
    sparseMatrix = insertElement(sparseMatrix, 1, 0, 4);
    sparseMatrix = insertElement(sparseMatrix, 2, 1, 5);

    printf("Original Sparse Matrix:\n");
    printSparseMatrix(sparseMatrix);

    struct Node* transposedMatrix = transposeSparseMatrix(sparseMatrix);

    printf("\nTransposed Sparse Matrix:\n");
    printSparseMatrix(transposedMatrix);

    return 0;
}
