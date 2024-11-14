#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int expo;
    struct Node* next;
};

struct Node* createNode(int coeff, int expo) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = newNode;  
    return newNode;
}

struct Node* insertTerm(struct Node* head, int coeff, int expo) {
    struct Node* newNode = createNode(coeff, expo);
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

struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node *p1 = poly1, *p2 = poly2;

    
    do {
        result = insertTerm(result, p1->coeff, p1->expo);
        p1 = p1->next;
    } while (p1 != poly1);

    do {
        struct Node *temp = result, *prev = NULL;
        int added = 0;
        do {
            if (temp->expo == p2->expo) {
                temp->coeff += p2->coeff;
                added = 1;
                break;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != result);

        if (!added) {
            result = insertTerm(result, p2->coeff, p2->expo);
        }
        p2 = p2->next;
    } while (p2 != poly2);

    return result;
}

void printPolynomial(struct Node* head) {
    if (!head) return;

    struct Node* temp = head;
    do {
        printf("%dx^%d", temp->coeff, temp->expo);
        temp = temp->next;
        if (temp != head) printf(" + ");
    } while (temp != head);
    printf("\n");
}

int main() {
    struct Node *poly1 = NULL, *poly2 = NULL;

    poly1 = insertTerm(poly1, 3, 3);
    poly1 = insertTerm(poly1, 2, 2);
    poly1 = insertTerm(poly1, 5, 0);

    poly2 = insertTerm(poly2, 4, 3);
    poly2 = insertTerm(poly2, 3, 1);
    poly2 = insertTerm(poly2, 6, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);

    printf("Polynomial 2: ");
    printPolynomial(poly2);

    struct Node* result = addPolynomials(poly1, poly2);

    printf("Sum of polynomials: ");
    printPolynomial(result);

    return 0;
}
