#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    char value;
    struct node *next;
}Node;
typedef struct stack {
    Node *top;
}Stack;
void push(Stack *stack, char value) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    new_node->value=value;
    new_node->next=stack->top;
    stack->top=new_node;
}
char pop(Stack *stack) {
    Node *target=stack->top;
    char value=target->value;
    stack->top=target->next;
    free(target);
    return value;
}
void print_pop_operator(Stack *stack) {
    if (stack->top->value=='p') {
        printf("+");
        pop(stack);
    }
    else if (stack->top->value=='m') {
        printf("-");
        pop(stack);
    }
    else if (stack->top->value=='&'||stack->top->value=='|') {
        printf("%c%c",stack->top->value,pop(stack));
    }
    else printf("%c",pop(stack));
}
int priority(char value) {
    switch (value) {
        case '!':
        case 'p':
        case 'm':
            return 6;
        case '*':
        case '/':
            return 5;
        case '+':
        case '-':
            return 4;
        case '<':
        case '>':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
    }
}
int is_operator(char value) {
    return value=='!'||
        value=='p'||
        value=='m'||
        value=='*'||
        value=='/'||
        value=='+'||
        value=='-'||
        value=='<'||
        value=='>'||
        value=='&'||
        value=='|';
}
char is_unary(char *string,int index) {
    if (!index) {
        if (string[index]=='+')return 'p';
        else if (string[index]=='-')return 'm';
        else return string[index];
    }
    if (string[index]=='!')return string[index];
    else if (string[index]=='+'&&(is_operator(string[index-1])||string[index-1]=='('))return 'p';
    else if (string[index]=='-'&&(is_operator(string[index-1])||string[index-1]=='('))return 'm';
}
void change(char *string) {
    Stack stack;
    stack.top=NULL;
    for (int index=0;index<strlen(string);index++) {
        char value=string[index];
        if (value>='A'&&value<='Z') printf("%c",value);
        else if (value=='(') push(&stack,value);
        else if (value==')') {
            while (stack.top&&stack.top->value!='(') print_pop_operator(&stack);
            pop(&stack);
        }
        else {
            if ((value=='&'||value=='|')&&string[index+1]==value) index++;
            if (value=='+'||value=='-')value=is_unary(string,index);
            while (stack.top&&
                   stack.top->value!='('&&
                   priority(stack.top->value)>=priority(value))
                print_pop_operator(&stack);
        }
        push(&stack,value);
    }
    while (stack.top) {
        print_pop_operator(&stack);
    }
    printf("\n");
}
int main() {
    int count;
    scanf("%d",&count);
    for (int i=0;i<count;i++) {
        char string[101]={0};
        scanf("%s",string);
        change(string);
    }
}