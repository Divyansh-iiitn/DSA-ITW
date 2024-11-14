#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    newNode->next = newNode;  
    newNode->prev = newNode;  
    return newNode;
}

struct Node* insertTerm(struct Node* head, int coeff, int expo) {
    struct Node* newNode = createNode(coeff, expo);
    if (!head) {
        head = newNode;
    } else {
        struct Node* last = head->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = head;
        head->prev = newNode;
    }
    return head;
}

double evaluatePolynomial(struct Node* head, double x) {
    double result = 0.0;
    struct Node* temp = head;
    if (!head) return result;

    do {
        result += temp->coeff * pow(x, temp->expo);
        temp = temp->next;
    } while (temp != head);

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
    struct Node* poly = NULL;

    poly = insertTerm(poly, 3, 3);
    poly = insertTerm(poly, 2, 2);
    poly = insertTerm(poly, 5, 1);
    poly = insertTerm(poly, 6, 0);

    printf("Polynomial: ");
    printPolynomial(poly);

    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);

    double result = evaluatePolynomial(poly, x);
    printf("Value of polynomial at x = %.2f: %.2f\n", x, result);

    return 0;
}
