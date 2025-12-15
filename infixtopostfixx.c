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
//------------------------------------------------------------------------------------
//dynamically allocate stack memory
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX 100

// char infix[MAX], postfix[MAX];

// /* Stack structure */
// typedef struct {
//     char *arr;
//     int top;
//     int capacity;
// } Stack;

// /* Stack functions */
// void init(Stack *s, int size) {
//     s->capacity = size;
//     s->top = -1;
//     s->arr = (char *)malloc(sizeof(char) * size);
// }

// void push(Stack *s, char c) {
//     if (s->top == s->capacity - 1) {
//         printf("Stack Overflow\n");
//         return;
//     }
//     s->arr[++s->top] = c;
// }

// char pop(Stack *s) {
//     if (s->top == -1) {
//         printf("Stack Underflow\n");
//         exit(1);
//     }
//     return s->arr[s->top--];
// }

// int isEmpty(Stack *s) {
//     return s->top == -1;
// }

// char peek(Stack *s) {
//     return s->arr[s->top];
// }

// /* Utility functions */
// int space(char c) {
//     return (c == ' ' || c == '\t' || c == '\n');
// }

// int precedence(char c) {
//     switch (c) {
//         case '^': return 3;
//         case '*':
//         case '/':
//         case '%': return 2;
//         case '+':
//         case '-': return 1;
//         default: return 0;
//     }
// }

// /* Infix to Postfix */
// void intopost() {
//     Stack s;
//     init(&s, MAX);

//     int i, j = 0;
//     char symbol;

//     for (i = 0; infix[i] != '\0'; i++) {
//         symbol = infix[i];

//         if (!space(symbol)) {
//             if ((symbol >= 'a' && symbol <= 'z') ||
//                 (symbol >= 'A' && symbol <= 'Z') ||
//                 (symbol >= '0' && symbol <= '9')) {
//                 postfix[j++] = symbol;
//             }
//             else if (symbol == '(') {
//                 push(&s, symbol);
//             }
//             else if (symbol == ')') {
//                 while (!isEmpty(&s) && peek(&s) != '(')
//                     postfix[j++] = pop(&s);
//                 pop(&s);  // remove '('
//             }
//             else { // operator
//                 while (!isEmpty(&s) &&
//                        precedence(peek(&s)) >= precedence(symbol))
//                     postfix[j++] = pop(&s);
//                 push(&s, symbol);
//             }
//         }
//     }

//     while (!isEmpty(&s))
//         postfix[j++] = pop(&s);

//     postfix[j] = '\0';
// }

// /* Print */
// void print() {
//     printf("Postfix Expression: %s\n", postfix);
// }

// /* Main */
// int main() {
//     printf("Enter infix expression: ");
//     fgets(infix, MAX, stdin);

//     intopost();
//     print();

//     return 0;
// }
