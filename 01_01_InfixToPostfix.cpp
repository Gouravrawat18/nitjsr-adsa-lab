#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>   
#include <string.h>  

#define MAX 100


char stack[MAX];
int top = -1;


void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    } else {
        printf("Stack Overflow\n");
        exit(1);
    }
}

char pop() {
    if (top >= 0)
        return stack[top--];
    else
        return '\0';
}

char peek() {
    if (top >= 0)
        return stack[top];
    else
        return '\0';
}


int precedence(char op) {
    switch (op) {
         
        case '^': return 4;
        case '/': return 3;
        case '*': return 3;
        case '+': return 2;
        case '-': return 2;
        default:  return 0;
    }
}

int isOperator(char c) {
    return (c == '^')|| (c == '+') ||( c == '-' ) ||(c == '*') || (c == '/');
}

void infixToPostfix(char* infix, char* postfix) {
    int i, k = 0;
    for (i = 0; i < strlen(infix); i++) {
        char c = infix[i];

        
        if (isalnum(c)) {
            postfix[k++] = c;
        }
        
        else if (c == '(') {
            push(c);
        }
       
        else if (c == ')') {
            while (top >= 0 && peek() != '(') {
                postfix[k++] = pop();
            }
            pop(); 
        }
       
        else if (isOperator(c)) {
            while (top >= 0 && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    while (top >= 0) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; 
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);
  
    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}