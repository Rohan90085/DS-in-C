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
//another method
// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>

// #define MAX 100

// typedef struct {
//     char arr[MAX];
//     int top;
// } Stack;

// void push(Stack *s, char c) { s->arr[++s->top] = c; }
// char pop(Stack *s)          { return s->arr[s->top--]; }
// char peek(Stack *s)         { return (s->top == -1) ? '\0' : s->arr[s->top]; }

// int prec(char op) {
//     if (op=='+'||op=='-') return 1;
//     if (op=='*'||op=='/'||op=='%') return 2;
//     if (op=='^') return 3;
//     return 0;
// }

// int rightAssoc(char op) { return op=='^'; }

// void infixToPostfix(char *in, char *post) {
//     Stack s = {.top = -1};
//     int i, j = 0;

//     for (i = 0; in[i]; i++) {
//         char c = in[i];

//         if (isspace(c)) continue;
//         if (isalnum(c)) post[j++] = c;

//         else if (c == '(') push(&s, c);

//         else if (c == ')') {
//             while (peek(&s) != '(') post[j++] = pop(&s);
//             pop(&s); // remove '('
//         }

//         else { // operator
//             while (s.top != -1 &&
//                   (( !rightAssoc(c) && prec(peek(&s)) >= prec(c)) ||
//                    ( rightAssoc(c) && prec(peek(&s)) >  prec(c))))
//                 post[j++] = pop(&s);
//             push(&s, c);
//         }
//     }

//     while (s.top != -1) post[j++] = pop(&s);
//     post[j] = '\0';
// }

// int main() {
//     char in[MAX], post[MAX];

//     printf("Enter infix: ");
//     fgets(in, MAX, stdin);

//     infixToPostfix(in, post);
//     printf("Postfix: %s\n", post);

//     return 0;
// }