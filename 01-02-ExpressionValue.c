#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char opStack[MAX];
int topOp = -1;
int valStack[MAX];
int topVal = -1;

void pushOp(char c) {
    opStack[++topOp] = c;
}
char popOp() {
    return opStack[topOp--];
}
char peekOp() {
    return opStack[topOp];
}
int precedence(char c) {
    if (c == '/' || c == '*') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void infixToPostfix(char* infix, char* postfix) {
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isdigit(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            pushOp(c);
        } else if (c == ')') {
            while (topOp != -1 && peekOp() != '(') {
                postfix[k++] = popOp();
            }
            if (topOp != -1) popOp();
        } else if (isOperator(c)) {
            while (topOp != -1 && precedence(peekOp()) >= precedence(c)) {
                postfix[k++] = popOp();
            }
            pushOp(c);
        }
    }
    while (topOp != -1) {
        postfix[k++] = popOp();
    }
    postfix[k] = '\0';
}

void pushVal(int v) {
    valStack[++topVal] = v;
}
int popVal() {
    return valStack[topVal--];
}

int evaluatePostfix(char* postfix) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            pushVal(c - '0');
        } else if (isOperator(c)) {
            int b = popVal();
            int a = popVal();
            int res;
            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            pushVal(res);
        }
    }
    return popVal();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }
    char postfix[MAX];
    infixToPostfix(argv[1], postfix);
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);
    return 0;
}
