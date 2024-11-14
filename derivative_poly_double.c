#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int expo;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int coeff, int expo) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct Node* insertTerm(struct Node* head, int coeff, int expo) {
    struct Node* newNode = createNode(coeff, expo);
    if (!head) {
        return newNode;
    }
    
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

struct Node* derivative(struct Node* head) {
    struct Node* result = NULL;
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->expo != 0) { 
            int newCoeff = temp->coeff * temp->expo;
            int newExpo = temp->expo - 1;
            result = insertTerm(result, newCoeff, newExpo);
        }
        temp = temp->next;
    }
    return result;
}

void printPolynomial(struct Node* head) {
    if (!head) {
        printf("0\n");
        return;
    }

    struct Node* temp = head;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->expo);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial: 3x^4 + 2x^3 + 5x + 7
    poly = insertTerm(poly, 3, 4);
    poly = insertTerm(poly, 2, 3);
    poly = insertTerm(poly, 5, 1);
    poly = insertTerm(poly, 7, 0);

    printf("Original Polynomial: ");
    printPolynomial(poly);

    struct Node* derivativePoly = derivative(poly);

    printf("Derivative of the Polynomial: ");
    printPolynomial(derivativePoly);

    return 0;
}
