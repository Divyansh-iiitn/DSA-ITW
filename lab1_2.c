#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

struct Term* createTerm(int coefficient, int exponent) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;
    return newTerm;
}

void insertTerm(struct Term** poly, int coefficient, int exponent) {
    if (coefficient == 0) {
        return; 
    }
    
    struct Term* newTerm = createTerm(coefficient, exponent);
    if (*poly == NULL || (*poly)->exponent < exponent) {
        newTerm->next = *poly;
        *poly = newTerm;
    } else if ((*poly)->exponent == exponent) {
        (*poly)->coefficient += coefficient;
        if ((*poly)->coefficient == 0) {  
            struct Term* temp = *poly;
            *poly = (*poly)->next;
            free(temp);
        }
        free(newTerm);
    } else {
        struct Term* temp = *poly;
        while (temp->next != NULL && temp->next->exponent > exponent) {
            temp = temp->next;
        }
        if (temp->next != NULL && temp->next->exponent == exponent) {
            temp->next->coefficient += coefficient;
            if (temp->next->coefficient == 0) {  
                struct Term* toDelete = temp->next;
                 temp->next = temp->next->next;
                free(toDelete);
            }
            free(newTerm);
        } else {
            newTerm->next = temp->next;
            temp->next = newTerm;
        }
    }
}

void displayPolynomial(struct Term* poly) {
    struct Term* temp = poly;
    while (temp != NULL) {
        printf("%dx^%d", temp->coefficient, temp->exponent);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    int n1, n2, coefficient, exponent;
    struct Term* poly = NULL;

    printf("Enter the number of terms in polynomial A: ");
    scanf("%d", &n1);
    printf("Enter the terms (coefficient exponent) for polynomial A:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d %d", &coefficient, &exponent);
        insertTerm(&poly, coefficient, exponent);
    }

    printf("Enter the number of terms in polynomial B: ");
    scanf("%d", &n2);
    printf("Enter the terms (coefficient exponent) for polynomial B:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d %d", &coefficient, &exponent);
        insertTerm(&poly, coefficient, exponent);
    }

    printf("Resultant Polynomial: ");
    displayPolynomial(poly);

    while (poly != NULL) {
        struct Term* temp = poly;
        poly = poly->next;
        free(temp);
    }

    return 0;
}
