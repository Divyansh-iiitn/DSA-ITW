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
    while (temp->next != NULL && temp->expo > expo) {
        temp = temp->next;
    }

    if (temp->expo == expo) {
        temp->coeff += coeff;
    } else {
        newNode->next = temp;
        newNode->prev = temp->prev;
        if (temp->prev) {
            temp->prev->next = newNode;
        } else {
            head = newNode;
        }
        temp->prev = newNode;
    }
    return head;
}

struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2;

    while (p1 != NULL) {
        p2 = poly2;
        while (p2 != NULL) {
            int coeff = p1->coeff * p2->coeff;
            int expo = p1->expo + p2->expo;
            result = insertTerm(result, coeff, expo);
            p2 = p2->next;
        }
        p1 = p1->next;
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
    struct Node *poly1 = NULL, *poly2 = NULL;

    // Example polynomials
    // Polynomial 1: 3x^3 + 2x^1 + 1
    poly1 = insertTerm(poly1, 3, 3);
    poly1 = insertTerm(poly1, 2, 1);
    poly1 = insertTerm(poly1, 1, 0);

    // Polynomial 2: 4x^2 + 3x^1 + 5
    poly2 = insertTerm(poly2, 4, 2);
    poly2 = insertTerm(poly2, 3, 1);
    poly2 = insertTerm(poly2, 5, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);

    printf("Polynomial 2: ");
    printPolynomial(poly2);

    struct Node* result = multiplyPolynomials(poly1, poly2);

    printf("Resultant Polynomial after multiplication: ");
    printPolynomial(result);

    return 0;
}
