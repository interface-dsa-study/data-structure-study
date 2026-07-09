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
    if (stack->size==stack->capacity) {
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
char peek(Stack *stack) {
    if (stack->size==0) {
        printf("Stack Empty");
        return '\0';
    }
    return stack->top->element;
}
void duplicate(Stack *stack) {
    char element=pop(stack);
    push(stack,element);
    push(stack,element);
}
Node *node_nexts(Node *current_node,int time) {
    Node *node=current_node;
    for (int i=0;i<time;i++,node=node->next);
    return node;
}
void up_rotate(Stack *stack,int count) {
    if (count>stack->size) return;
    Node *A=stack->top;
    Node *B=node_nexts(stack->top,1);
    Node *C=node_nexts(stack->top,count-1);
    Node *D=node_nexts(stack->top,count);
    C->next=A;
    A->next=D;
    stack->top=B;
}
void down_rotate(Stack *stack,int count) {
    if (count>stack->size) return;
    Node *A=stack->top;
    Node *B=node_nexts(stack->top,count-2);
    Node *C=node_nexts(stack->top,count-1);
    Node *D=node_nexts(stack->top,count);
    C->next=A;
    B->next=D;
    stack->top=C;
}
void print(Stack *stack) {
    for (Node *pointer=stack->top;pointer;pointer=pointer->next) {
        printf("%c",pointer->element);
    }
}
void free_stack(Node *node) {
    if (node) {
        free_stack(node->next);
        free(node);
    }
}
int main() {
    Stack stack;
    scanf("%d",&stack.capacity);
    stack.size=0;
    stack.top=NULL;

    int calc_time;
    scanf("%d",&calc_time);
    getchar();
    for (int i=0;i<calc_time;i++) {
        char input[6]={0};
        scanf("%s",input);
        getchar();
        if (!strcmp(input,"PUSH")) {
            char element;
            scanf("%c",&element);
            push(&stack,element);
        }
        else if (!strcmp(input,"POP")) {
            char result=pop(&stack);
            if (result)printf("%c",result);
        }
        else if (!strcmp(input,"PEEK")) {
            char result=peek(&stack);
            if (result)printf("%c",result);
        }
        else if (!strcmp(input,"DUP")) {
            duplicate(&stack);
        }
        else if (!strcmp(input,"UpR")) {
            int n;
            scanf("%d",&n);
            getchar();
            up_rotate(&stack,n);
        }
        else if (!strcmp(input,"DownR")) {
            int n;
            scanf("%d",&n);
            getchar();
            down_rotate(&stack,n);
        }
        else if (!strcmp(input,"PRINT")) {
            print(&stack);
        }
        printf("\n");
    }
    free_stack(stack.top);
    return 0;
}