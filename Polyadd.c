#include <stdio.h>
#include <stdlib.h>

struct poly {
    int exponent;
    int coefficient;
    struct poly *next;
};

int getNumberOfTerms() {
    int n = 0;
    printf("\nEnter the number of terms in the polynomial\n");
    scanf("%d", &n);
    return n;
}

struct poly* getTerm() {
    int coefficient = 0, exponent = 0;
    printf("Enter the coefficient\n");
    scanf("%d", &coefficient);
    printf("Enter the exponent\n");
    scanf("%d", &exponent);
    struct poly *temp = (struct poly *)malloc(sizeof(struct poly));
    temp->coefficient = coefficient;
    temp->exponent = exponent;
    temp->next = NULL;
    return temp;
}

struct poly* createPolynomial(int numberOfTerms) {
    struct poly *term = NULL;
    struct poly *head = NULL;
    term = getTerm();
    if (head == NULL) {
        head = term;
    }
    for (int i = 0; i < numberOfTerms - 1; i++) {
        term->next = getTerm();
        if (head == NULL) {
            head = term;
        } else {
            term = term->next;
        }
    }
    return head;
}

void printPolynomial(struct poly *polynomial) {
    while (polynomial != NULL) {
        printf("%d x^%d + ", polynomial->coefficient, polynomial->exponent);
        polynomial = polynomial->next;
    }
}

struct poly* createTerm() {
    struct poly* temp = (struct poly*)malloc(sizeof(struct poly));
    temp->next = NULL;
    return temp;
}

struct poly* addPolynomials(struct poly *poly1, struct poly *poly2) {
    struct poly *result = NULL;
    struct poly *head = NULL;
    
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent == poly2->exponent) {       
            if (head == NULL) {
                result = createTerm();
                result->exponent = poly1->exponent;
                result->coefficient = poly1->coefficient + poly2->coefficient;
                head = result;
            } else {
                result->next = createTerm();
                result = result->next;
                result->exponent = poly1->exponent;
                result->coefficient = poly1->coefficient + poly2->coefficient;
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exponent > poly2->exponent) {
            if (head == NULL) {
                result = createTerm();
                result->exponent = poly1->exponent;
                result->coefficient = poly1->coefficient;
                head = result;
            } else {
                result->next = createTerm();
                result = result->next;
                result->exponent = poly1->exponent;
                result->coefficient = poly1->coefficient;
            }
            poly1 = poly1->next;
        } else {
            if (head == NULL) {
                result = createTerm();
                result->exponent = poly2->exponent;
                result->coefficient = poly2->coefficient;
                head = result;
            } else {
                result->next = createTerm();
                result = result->next;
                result->exponent = poly2->exponent;
                result->coefficient = poly2->coefficient;
            }
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        if (head == NULL) {
            result = createTerm();
            result->exponent = poly1->exponent;
            result->coefficient = poly1->coefficient;
            head = result;
        } else {
            result->next = createTerm();
            result = result->next;
            result->exponent = poly1->exponent;
            result->coefficient = poly1->coefficient;
        }
        poly1 = poly1->next;
    }
    
    while (poly2 != NULL) {
        if (head == NULL) {
            result = createTerm();
            result->exponent = poly2->exponent;
            result->coefficient = poly2->coefficient;
            head = result;
        } else {
            result->next = createTerm();
            result = result->next;
            result->exponent = poly2->exponent;
            result->coefficient = poly2->coefficient;
        }
        poly2 = poly2->next;
    }
    return head;    
}

int main(int argc, char *argv[]) {
    int numTerms1 = 0;
    int numTerms2 = 0;
    
    numTerms1 = getNumberOfTerms();
    struct poly* polynomial1 = createPolynomial(numTerms1);
    printPolynomial(polynomial1);
    
    numTerms2 = getNumberOfTerms();    
    struct poly* polynomial2 = createPolynomial(numTerms2);
    
    struct poly *result = addPolynomials(polynomial1, polynomial2);
    
    printPolynomial(result);
    free(polynomial1);
    free(polynomial2);
    free(result);
    
    return 0;
}

