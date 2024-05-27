
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100

char stack[N];
int top = -1;

int intStack[N];
int intTop = -1;

void push(char ch) {
    if (top >= N - 1) {
        printf("Stack overflow\n");
    } else {
        stack[++top] = ch;
    }
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    } else {
        return stack[top--];
    }
}

char peek() {
    if (top == -1) {
        printf("Stack is empty\n");
        return -1;
    } else {
        return stack[top];
    }
}

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
            return -1;
    }
}

int isOperand(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isOperand(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // pop '('
        } else {
            while (top != -1 && precedence(peek()) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

void intPush(int a) {
    if (intTop >= N - 1) {
        printf("Stack overflow\n");
    } else {
        intStack[++intTop] = a;
    }
}

int intPop() {
    if (intTop == -1) {
        printf("Stack underflow\n");
        return -1;
    } else {
        return intStack[intTop--];
    }
}

int evaluatePostfix(char postfix[]) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isOperand(ch) && ch >= '0' && ch <= '9') {
            intPush(ch - '0');
        } else {
            int op2 = intPop();
            int op1 = intPop();
            int result;

            switch (ch) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = pow(op1, op2); break;
                default: printf("Invalid operator\n"); return -1;
            }
            intPush(result);
        }
    }
    return intPop();
}

int main() {
    char infix[N], postfix[N];

    printf("Enter Infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);

    printf("Evaluation result: %d\n", result);

    return 0;
}
