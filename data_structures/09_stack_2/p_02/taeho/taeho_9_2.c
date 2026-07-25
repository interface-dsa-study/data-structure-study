///계산하는거
///후위수식-> 계산
///메인-> 자료에 있는거 그대로
///교안-> 피연산자-> 스택에 저장
///연산자-> 스택 두개 꺼내서 계산
///근데? insert, remove 어려움
///진우형: 스택 구조 없이 함
///insert_stack: 헤드-> 스택 구조 없으므로 이중 포인터 사용
///remove: 아는대로
///calc: 받은 값 반환
///main: 각각 문자 받고 피연-> 저장, 연-> 피연 두개 꺼내서 계산(with calc()) till end
///
///
///민우형:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    int value;
    struct node *next;
}Node;
typedef struct stack {
    Node *top;
}Stack;
void push(Stack *stack,int value) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->value=value;
    new_node->next=stack->top;
    stack->top=new_node;
}
int pop(Stack *stack) {
    if (stack->top==NULL) {
        fprintf(stderr,"stack is empty");
        return '\0';
    }
    Node *target=stack->top;
    int value=target->value;
    stack->top=target->next;
    free(target);
    return value;
}
int calculate(int left, int right, char calculator) {
    switch (calculator) {
        case '*':
            return left*right;
        case '/':
            return left/right;
        case '+':
            return left+right;
        case '-':
            return left-right;
    }
}
void string_calculate() {
    Stack stack;
    stack.top=NULL;
    char string[101]={0};
    scanf("%s",string);
    for (int i=0;i<strlen(string);i++) {
        if (string[i]>='0'&&string[i]<='9') {//피연산자->스택에 바로 푸시
            push(&stack,string[i]-'0');
        }
        else if (string[i]=='*'||//연산자->스택에서 오른쪽, 왼쪽 피연산자 꺼내서 계산
            string[i]=='/'||
            string[i]=='+'||
            string[i]=='-') {
            if (stack.top==NULL) {
                fprintf(stderr,"stack is empty");
                return;
            }//StackEmptyException
            int right=pop(&stack);
            if (stack.top==NULL) {
                fprintf(stderr,"stack is empty");
                return;
            }//StackEmptyException
            int left=pop(&stack);
            push(&stack,calculate(left,right,string[i]));//연산한거 스택에 저장
        }
    }
    printf("%d\n",pop(&stack));
    if (stack.top) {
        fprintf(stderr,"stqack is not empty");
        exit(1);
    }
}
int main() {
    int time;
    scanf("%d",&time);
    for (int i=0;i<time;i++) {
        string_calculate();
    }
}