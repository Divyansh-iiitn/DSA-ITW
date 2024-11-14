#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;       
    int expo_x;      
    int expo_y;      
    struct Node* next;
};

struct Node* createNode(int coeff, int expo_x, int expo_y) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->expo_x = expo_x;
    newNode->expo_y = expo_y;
    newNode->next = newNode;  
    return newNode;
}

struct Node* insertTerm(struct Node* head, int coeff, int expo_x, int expo_y) {
    struct Node* newNode = createNode(coeff, expo_x, expo_y);
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
        result = insertTerm(result, p1->coeff, p1->expo_x, p1->expo_y);
        p1 = p1->next;
    } while (p1 != poly1);

    do {
        struct Node *temp = result, *prev = NULL;
        int added = 0;
        do {
            if (temp->expo_x == p2->expo_x && temp->expo_y == p2->expo_y) {
                temp->coeff += p2->coeff;
                added = 1;
                break;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != result);

        if (!added) {
            result = insertTerm(result, p2->coeff, p2->expo_x, p2->expo_y);
        }
        p2 = p2->next;
    } while (p2 != poly2);

    return result;
}

void printPolynomial(struct Node* head) {
    if (!head) return;

    struct Node* temp = head;
    do {
        printf("%dx^%dy^%d", temp->coeff, temp->expo_x, temp->expo_y);
        temp = temp->next;
        if (temp != head) printf(" + ");
    } while (temp != head);
    printf("\n");
}

int main() {
    struct Node *poly1 = NULL, *poly2 = NULL;

    // Polynomial 1: 3x^2y + 2xy^2 + 4
    poly1 = insertTerm(poly1, 3, 2, 1);
    poly1 = insertTerm(poly1, 2, 1, 2);
    poly1 = insertTerm(poly1, 4, 0, 0);

    // Polynomial 2: 5x^2y + 2xy + 3
    poly2 = insertTerm(poly2, 5, 2, 1);
    poly2 = insertTerm(poly2, 2, 1, 1);
    poly2 = insertTerm(poly2, 3, 0, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);

    printf("Polynomial 2: ");
    printPolynomial(poly2);

    struct Node* result = addPolynomials(poly1, poly2);

    printf("Sum of polynomials: ");
    printPolynomial(result);

    return 0;
}
