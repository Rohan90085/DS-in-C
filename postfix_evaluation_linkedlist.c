#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<math.h>

typedef long long ll;

typedef struct Node {
    ll data;
    struct Node *next;
} Node;

Node *top = NULL;

void push(ll x) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->data = x;
    n->next = top;
    top = n;
}

ll pop() {
    if (!top) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    Node *t = top;
    ll v = t->data;
    top = t->next;
    free(t);
    return v;
}

int is_number(const char *s, ll *out) {
    if (s == NULL) return 0;
    char *endptr;
    errno = 0;
    long long val = strtoll(s, &endptr, 10);
    if (errno != 0) return 0;
    if (endptr == s) return 0; // no conversion
    // allow trailing spaces only (but strtok removes them)
    *out = val;
    return 1;
}

int main() {
    char line[1024];

    printf("Enter postfix expression (tokens separated by spaces):\n");
    if (!fgets(line, sizeof(line), stdin)) return 0;
    // remove newline
    line[strcspn(line, "\n")] = 0;

    char *token = strtok(line, " ");
    while (token != NULL) {
        ll val;
        if (is_number(token, &val)) {
            push(val);
        } else if (strlen(token) == 1) {
            char op = token[0];
            ll a, b, r;
            switch (op) {
                case '+':
                    a = pop(); b = pop(); push(b + a); break;
                case '-':
                    a = pop(); b = pop(); push(b - a); break;
                case '*':
                    a = pop(); b = pop(); push(b * a); break;
                case '/':
                    a = pop(); b = pop();
                    if (a == 0) { fprintf(stderr, "Division by zero\n"); exit(1); }
                    push(b / a); break;
                case '%':
                    a = pop(); b = pop();
                    if (a == 0) { fprintf(stderr, "Modulo by zero\n"); exit(1); }
                    push(b % a); break;
                case '^':
                    a = pop(); b = pop();
                    if (a < 0) { fprintf(stderr, "Negative exponent not supported\n"); exit(1); }
                    r = pow(b, a);
                    push(r);
                    break;
                default:
                    fprintf(stderr, "Unknown operator/token: %s\n", token);
                    exit(1);
            }
        } else {
            fprintf(stderr, "Invalid token: %s\n", token);
            exit(1);
        }

        token = strtok(NULL, " ");
    }

    // final result
    if (top == NULL) {
        fprintf(stderr, "No result on stack\n");
        return 1;
    }
    ll result = pop();
    if (top != NULL) {
        fprintf(stderr, "Warning: extra values remain on stack (invalid postfix?)\n");
    }

    printf("Result = %lld\n", result);
    return 0;
}
