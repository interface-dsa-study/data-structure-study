#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *element;
    int top;
    int Size;
}Stack;

void initStack(Stack *stack, int N) {
    stack->element = (char*)malloc(sizeof(char) * N);
    stack->top = -1;
    stack->Size = N;
}

void FullStackException() {
    printf("Stack FULL\n");
    return;
}

void EmptyStackException() {
    printf("Stack Empty\n");
    return;
}

void push(Stack* stack, char e) {
    if (stack->top > stack->Size) {
        FullStackException();
    }
    else stack->element[++(stack->top)] = e;
}

char pop(Stack *stack) {
    if (stack->top == -1) {
        EmptyStackException();
    }
    else return stack->element[(stack->top)--];
}

void peek(Stack *stack) {
    if (stack->top == -1) {
        EmptyStackException();
    }
    else printf("%c\n", stack->element[stack->top]);
}

void duplicate(Stack *stack) {
    if (stack->top > stack->Size) {
        FullStackException(); return;
    }
    if (stack->top == -1) {
        EmptyStackException(); return;
    }
    char tmp = stack->element[stack->top];
    push(stack, tmp);
}

void upRotate(Stack *stack, int n) {
    int count = stack->top + 1;
    if (n > count) return;
    char tmp = stack->element[stack->top];
    for (int i = stack->top;i > stack->top - n + 1; i--) {
        stack->element[i] = stack->element[i - 1];
    }
    stack->element[stack->top - n + 1] = tmp;
}

void downRotate(Stack *stack, int n) {
    int count = stack->top + 1;
    if (n > count) return;
    char tmp = stack->element[stack->top - n + 1];
    for (int i = stack->top - n + 1; i < stack->top;i++) {
        stack->element[i] = stack->element[i + 1];
    }
    stack->element[stack->top] = tmp;
}

void printStack(Stack *stack) {
    for (int i = stack->top;i >= 0;i--) {
        printf("%c", stack->element[i]);
    }
    printf("\n");
}

int main() {
    int N, order_N; scanf("%d%d", &N, &order_N);
    Stack stack;
    initStack(&stack, N);
    char order[6], word; int turn;
    for (int i = 0; i < order_N; i++) {
        scanf("%s", order);
        if (strcmp(order, "PUSH") == 0) {
            scanf(" %c", &word);
            push(&stack, word);
        }
        else if (strcmp(order, "POP") == 0) {
            pop(&stack);
        }
        else if (strcmp(order, "PEEK") == 0) {
            peek(&stack);
        }
        else if (strcmp(order, "DUP") == 0) {
            duplicate(&stack);
        }
        else if (strcmp(order, "UpR") == 0) {
            scanf(" %d", &turn);
            upRotate(&stack, turn);
        }
        else if (strcmp(order, "DownR") == 0) {
            scanf(" %d", &turn);
            downRotate(&stack, turn);
        }
        else if (strcmp(order, "PRINT") == 0) {
            printStack(&stack);
        }
        else {
            printf("none\n");
        }
    }
}