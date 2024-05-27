#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure for characters
typedef struct Stack {
    char arr[MAX];
    int top;
} Stack;

// Stack structure for strings
typedef struct StringStack {
    char *arr[MAX];
    int top;
} StringStack;

// Function to initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Function to check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Function to check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Function to push an element to stack
void push(Stack *s, char val) {
    if (!isFull(s)) {
        s->arr[++(s->top)] = val;
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop an element from stack
char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[(s->top)--];
    } else {
        printf("Stack underflow\n");
        return '\0';
    }
}

// Function to peek the top element of stack
char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[s->top];
    } else {
        return '\0';
    }
}

// Function to initialize string stack
void initStringStack(StringStack *s) {
    s->top = -1;
}

// Function to push a string to string stack
void pushString(StringStack *s, char *val) {
    if (s->top < MAX - 1) {
        s->arr[++(s->top)] = val;
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop a string from string stack
char* popString(StringStack *s) {
    if (s->top >= 0) {
        return s->arr[(s->top)--];
    } else {
        printf("Stack underflow\n");
        return NULL;
    }
}

// Function to check if character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to get precedence of operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to reverse a string
void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char *infix, char *prefix) {
    Stack operators;
    StringStack operands;
    initStack(&operators);
    initStringStack(&operands);
    
    reverse(infix);
    int len = strlen(infix);
    for (int i = 0; i < len; i++) {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            char *operand = (char*)malloc(2 * sizeof(char));
            operand[0] = infix[i];
            operand[1] = '\0';
            pushString(&operands, operand);
        } else if (infix[i] == ')') {
            push(&operators, infix[i]);
        } else if (infix[i] == '(') {
            while (!isEmpty(&operators) && peek(&operators) != ')') {
                char op = pop(&operators);
                char *op1 = popString(&operands);
                char *op2 = popString(&operands);
                char *expr = (char*)malloc(strlen(op1) + strlen(op2) + 2);
                sprintf(expr, "%c%s%s", op, op1, op2);
                pushString(&operands, expr);
            }
            pop(&operators); // Remove ')'
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&operators) && precedence(peek(&operators)) > precedence(infix[i])) {
                char op = pop(&operators);
                char *op1 = popString(&operands);
                char *op2 = popString(&operands);
                char *expr = (char*)malloc(strlen(op1) + strlen(op2) + 2);
                sprintf(expr, "%c%s%s", op, op1, op2);
                pushString(&operands, expr);
            }
            push(&operators, infix[i]);
        }
    }
    
    while (!isEmpty(&operators)) {
        char op = pop(&operators);
        char *op1 = popString(&operands);
        char *op2 = popString(&operands);
        char *expr = (char*)malloc(strlen(op1) + strlen(op2) + 2);
        sprintf(expr, "%c%s%s", op, op1, op2);
        pushString(&operands, expr);
    }
    
    strcpy(prefix, popString(&operands));
    reverse(prefix);
}

int main() {
    char infix[MAX], prefix[MAX];
    int choice;
    
    do {
        printf("\nMenu:\n");
        printf("1. Convert Infix to Prefix\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 2);
    
    return 0;
}
