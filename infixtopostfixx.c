#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX], infix[MAX], postfix[MAX];
int top = -1;

void push(char);
char pop();
int isempty();
void intopost();
int space(char);
int precedence(char);
void print();

int main() {
    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);     // safer than gets()

    intopost();
    print();

    return 0;
}

void intopost() {
    int i, j = 0;
    char symbol, next;

    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];

        if (!space(symbol)) {
            switch (symbol) {
                case '(':
                    push(symbol);
                    break;

                case ')':
                    while (!isempty() && (next = pop()) != '(')
                        postfix[j++] = next;
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                    while (!isempty() && precedence(stack[top]) >= precedence(symbol))
                        postfix[j++] = pop();

                    push(symbol);
                    break;

                default:
                    // operand
                    postfix[j++] = symbol;
            }
        }
    }

    while (!isempty())
        postfix[j++] = pop();

    postfix[j] = '\0';
}

int space(char c) {
    return (c == ' ' || c == '\t');
}

int precedence(char symbol) {
    switch (symbol) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

void print() {
    printf("Postfix Expression: %s\n", postfix);
}

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int isempty() {
    return (top == -1);
}
