#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct ListNode{
    char data;
    struct ListNode *next;
}ListNode;

void insertStack(ListNode **phead, int data){
    ListNode *newnode = (ListNode*)malloc(sizeof(ListNode));
    newnode->data = data;
    newnode->next = *phead;
    *phead = newnode;
}

void removeStack(ListNode **phead){
    if (*phead == NULL) return;
    ListNode *removeNode = *phead;
    *phead = (*phead)->next;
    free(removeNode);
}

int calculate(int a, int b, char operand){
    switch(operand){
        case '*' : return a * b;
        case '/' : return a / b;
        case '-' : return a - b;
        case '+' : return a + b;
    }
}

int main(){
    ListNode *head = NULL;
    int n;
    char tmp[101];
    char tmpelement;
    int first, second;
    int conclusion;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf(" %s", tmp);
        for (int j = 0; j < strlen(tmp); j++){
            tmpelement = tmp[j];
            //피연산자일 경우 - 스택에 저장
            if (!(tmpelement == '*' || tmpelement == '/' || tmpelement == '+' || tmpelement == '-')){
                insertStack(&head, tmpelement - '0'); //스택에는 정수 형태로 저장
            }
            else{ //연산자일 경우 - 스택에서 가장 위 2개 빼와서 '스택의 2번째 피연산자' '연산자' '스택의 1번째 피연산자' 위와 같은 식으로 계산. 계산한 값은 다시 스택으로
                first = head->data;
                removeStack(&head);
                second = head->data;
                removeStack(&head);
                conclusion = calculate(second, first, tmpelement);
                insertStack(&head, conclusion);
            }
        }
        printf("%d\n", conclusion);
    }
    return 0;
}