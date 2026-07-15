#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char value;
    struct node *next;
}Node;
typedef struct stack {
    Node *top;
}Stack;
void push(Stack *stack,char value) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    new_node->value=value;
    new_node->next=stack->top;
    stack->top=new_node;
}
char pop(Stack *stack) {
    if(stack->top==NULL)return 0;
    Node *temp=stack->top;
    char value=temp->value;
    stack->top=temp->next;
    free(temp);
    return value;
}
char peek(Stack *stack) {
    if(stack->top==NULL)return '\0';
    return stack->top->value;
}
int is_operator(char value) {
    return value=='!'||
            value=='+'||
            value=='-'||
            value=='*'||
            value=='/'||
            value=='&'||
            value=='|'||
            value=='<'||
            value=='>';
}
char is_unary(char *string,int index){
    if (index==0) return string[index];
    else if (string[index]=='!') return string[index];
    else if (string[index]=='+'||string[index]=='-') {
        if (is_operator(string[index-1])||string[index-1]=='(')return string[index]=='+'?'p':'m';
    }return string[index];
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
        case '>':
        case '<':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}
void convert() {
    char string[101]={0};
    scanf("%s",string);
    Stack stack;
    stack.top=NULL;
    for (int index=0;string[index]!='\0';index++) {
        if (string[index]>='A'&&string[index]<='Z') printf("%c",string[index]);
        else if (string[index]=='(') push(&stack,string[index]);
        else if (string[index]==')') {
            while (peek(&stack)!='(') {
                if (peek(&stack)=='&'||peek(&stack)=='|')printf("%c",peek(&stack));
                if (peek(&stack)!='p'||peek(&stack)!='m')printf("%c",pop(&stack));
                else {
                    printf("%c",pop(&stack)=='p'?'+':'-');
                }
            }
            pop(&stack);
        }
        else {
            char value=string[index];
            if ((value=='&'||value=='|')&&string[index+1]==value)index++;
            if (value=='+'||value=='-')value=is_unary(string,index);
            while (stack.top&&
                peek(&stack)!='('&&
                priority(stack.top->value)>=priority(value)) {

                if (peek(&stack)=='&'||peek(&stack)=='|')printf("%c",peek(&stack));
                if (peek(&stack)!='p'||peek(&stack)!='m')printf("%c",pop(&stack));
                else {
                    printf("%c",pop(&stack)=='p'?'+':'-');
                }
            }
            push(&stack,value);
        }
    }
    while (stack.top) {
        if (peek(&stack)=='&'||peek(&stack)=='|')printf("%c",peek(&stack));
        if (peek(&stack)!='p'||peek(&stack)!='m')printf("%c",pop(&stack));
        else {
            printf("%c",pop(&stack)=='p'?'+':'-');
        }
    }
    printf("\n");
}
int main() {
    int n;
    scanf("%d",&n);
    getchar();
    for (int i=0;i<n;i++) {
        convert();
    }
}