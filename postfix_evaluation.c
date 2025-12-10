//implementation of postfix expression evaluation using stack in array
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

char infix[MAX], postfix[MAX];
int stack[MAX], top = -1;

void push(int c){
    if(top == MAX - 1){
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

int pop(){
    if(top == -1){
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int isempty(){
    return (top == -1);
}

int space(char c){
    return (c == ' ' || c == '\t');
}

int precedence(char symbol){
    switch(symbol){
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}

void intopost(){
    int i, j = 0;
    char symbol, next;

    for(i = 0; i < strlen(infix); i++){
        symbol = infix[i];

        if(!space(symbol)){
            switch(symbol){

                case '(':
                    push(symbol);
                    break;

                case ')':
                    while(!isempty() && (next = pop()) != '(')
                        postfix[j++] = next;
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                    while(!isempty() && precedence(stack[top]) >= precedence(symbol))
                        postfix[j++] = pop();
                    push(symbol);
                    break;

                default:
                    postfix[j++] = symbol;
            }
        }
    }

    while(!isempty())
        postfix[j++] = pop();

    postfix[j] = '\0';
}

void print(){
    printf("Postfix Expression: %s\n", postfix);
}

int post_eval(){
    int i, a, b;

    for(i = 0; i < strlen(postfix); i++){

        if(postfix[i] >= '0' && postfix[i] <= '9'){
            push(postfix[i] - '0');
        }
        else{
            a = pop();
            b = pop();

            switch(postfix[i]){
                case '+': push(b + a); break;
                case '-': push(b - a); break;
                case '*': push(b * a); break;
                case '/': push(b / a); break;
                case '%': push(b % a); break;
                case '^': push(pow(b, a)); break;
            }
        }
    }

    return pop();
}

int main(){
    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);

    // Remove newline from input
    infix[strcspn(infix, "\n")] = 0;

    intopost();
    print();

    int res = post_eval();
    printf("The result obtained after evaluation >> %d\n", res);

    return 0;
}
