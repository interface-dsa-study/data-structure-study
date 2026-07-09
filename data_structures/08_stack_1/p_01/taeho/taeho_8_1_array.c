#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stack {
    char *element;
    int size;
    int top_index;
}Stack;
void push(Stack *stack,char element) {
    if (stack->top_index==stack->size-1) {
        printf("Stack Full");
        return;
    }
    stack->top_index+=1;
    *(stack->element+stack->top_index)=element;
}
char pop(Stack *stack) {
    if (stack->top_index==-1) {
        printf("Stack Empty");
        return '\0';
    }
    stack->top_index-=1;
    return *(stack->element+stack->top_index+1);
}
char peek(Stack *stack) {
    if (stack->top_index==-1) {
        printf("Stack Empty");
        return '\0';
    }
    return *(stack->element+stack->top_index);
}
void duplicate(Stack *stack) {
    char element=pop(stack);
    push(stack,element);
    push(stack,element);
}
void up_rotate(Stack *stack,int count) {
    if (count>stack->top_index+1) return;
    char tmp=*(stack->element+stack->top_index);
    for (char *pointer=stack->element+stack->top_index;pointer>=stack->element+stack->top_index-count+2;pointer--) *pointer=*(pointer-1);
    *(stack->element+stack->top_index-count+1)=tmp;
}
void down_rotate(Stack *stack,int count) {
    if (count>stack->top_index+1) return;
    char tmp=*(stack->element+stack->top_index-count+1);
    for (char *pointer=stack->element+stack->top_index-count+1;pointer<=stack->element+stack->top_index-1;pointer++) *pointer=*(pointer+1);
    *(stack->element+stack->top_index)=tmp;
}
void print(Stack *stack) {
    for (char *pointer=stack->element+stack->top_index;pointer>=stack->element;pointer--) {
        printf("%c",*pointer);
    }
}
int main() {
    setbuf(stdout,NULL);
    Stack stack;
    scanf("%d",&stack.size);
    stack.element=(char*)calloc(stack.size,sizeof(char));
    if (stack.element==NULL) {
        fprintf(stderr,"stack calloc failed");
        exit(-1);
    }
    stack.top_index=-1;

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
    return 0;
}