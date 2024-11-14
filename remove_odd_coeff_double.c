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
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    return head;
}

struct Node* removeOddCoeffTerms(struct Node* head) {
    struct Node* temp = head;

    while (temp != NULL) {
        struct Node* nextNode = temp->next;
        if (temp->coeff % 2 != 0) { 
            
            if (temp->prev) {
                temp->prev->next = temp->next;
            } else { 
                
                head = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            free(temp);
        }
        temp = nextNode;
    }
    return head;
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

    // Example polynomial: 3x^3 + 2x^2 + 5x + 4
    poly = insertTerm(poly, 3, 3);
    poly = insertTerm(poly, 2, 2);
    poly = insertTerm(poly, 5, 1);
    poly = insertTerm(poly, 4, 0);

    printf("Original Polynomial: ");
    printPolynomial(poly);

    poly = removeOddCoeffTerms(poly);

    printf("Polynomial after removing odd coefficient terms: ");
    printPolynomial(poly);

    return 0;
}
