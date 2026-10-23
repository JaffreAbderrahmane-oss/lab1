#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack s) {
    return s.top == NULL;
}

void push(Stack* s, char val) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) return;
    p->data = val;
    p->next = s->top;
    s->top = p;
}

char pop(Stack* s) {
    if (isEmpty(*s)) return '\0';
    Node* p = s->top;
    char x = p->data;
    s->top = s->top->next;
    free(p);
    return x;
}

char peek(Stack s) {
    if (isEmpty(s)) return '\0';
    return s.top->data;
}

void displayStack(Stack s) {
    Node* p = s.top;
    if (p == NULL) {
        printf("Stack empty\n");
        return;
    }
    printf("Stack: ");
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

int evaluatePostfix(char* expr) {
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' ') continue;

        if (expr[i] >= '0' && expr[i] <= '9') {
            push(&s, expr[i] - '0');
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            int b = pop(&s);
            int a = pop(&s);

            if (expr[i] == '+') push(&s, a + b);
            else if (expr[i] == '-') push(&s, a - b);
            else if (expr[i] == '*') push(&s, a * b);
            else if (expr[i] == '/') push(&s, a / b);
        }
    }
    return pop(&s);
}

int main() {
    Stack s;
    initStack(&s);
    int choice;
    char val;
    char str[100];
    char expr[100];

    do {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Evaluate Postfix\n5. Exit\nOption: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
    printf("Enter string: ");
    scanf(" %[^\n]s", str);
    for(int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }
    printf("String pushed successfully!\n");
    break;
            case 2:
                val = pop(&s);
                if (val != '\0') printf("Popped: %c\n", val);
                break;
            case 3:
                displayStack(s);
                break;
            case 4:
                printf("Enter postfix: ");
                scanf(" %[^\n]s", expr);
                printf("Result = %d\n", evaluatePostfix(expr));
                break;
        }
    } while (choice != 5);

    return 0;
}
