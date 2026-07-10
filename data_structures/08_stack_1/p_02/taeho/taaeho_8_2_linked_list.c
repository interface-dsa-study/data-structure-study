#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char element;
    struct node *next;
}Node;
typedef struct stack {
    Node *top;
    int size;
    int capacity;
}Stack;
void push(Stack *stack,char element) {
    if (stack->size==stack->capacity){
        printf("Stack Full");
        return;
    }
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(-1);
    }
    new_node->element=element;
    new_node->next=stack->top;
    stack->top=new_node;
    stack->size++;
}
char pop(Stack *stack) {
    if (stack->size==0) {
        printf("Stack Empty");
        return '\0';
    }
    Node *tmp=stack->top;
    char element=tmp->element;
    stack->top=stack->top->next;
    free(tmp);
    stack->size--;
    return element;
}
void free_node(Node *node) {
    if (node) {
        free_node(node->next);
        free(node);
    }
}
void check(char *string) {
    char *string_pointer=string;
    int count=0;
    int flag=2;
    Stack stack;
    stack.top=NULL;
    stack.capacity=strlen(string);
    stack.size=0;

    for (;string_pointer<string+1000&&*string_pointer!='\n';string_pointer++) {
        switch (*string_pointer) {
            case '(':
            case '{':
            case '[':
                push(&stack,*string_pointer);
                count++;
                break;
            case ')':
            case '}':
            case ']':
                count++;
                if (stack.size==0&&flag==2) {
                    flag=0;
                    continue;
                }
                if (stack.top->element=='('&&*string_pointer==')'
                  ||stack.top->element=='{'&&*string_pointer=='}'
                  ||stack.top->element=='['&&*string_pointer==']') {
                    pop(&stack);
                  }
                else flag=0;
                break;
        }
    }
    if (stack.size==0&&flag==2)flag=1;
    switch (flag) {
        case 0:
            printf("Wrong");
            break;
        case 1:
            printf("OK");
            break;
        case 2:
            printf("problem");
            break;
    }
    printf("_%d",count);
    free(stack.top);
}
int main() {
    char string[1001]={0};
    gets(string);
    check(string);
    return 0;
}