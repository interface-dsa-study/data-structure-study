#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct ListNode{
    char data;
    struct ListNode *next;
}ListNode;

void insertStack(ListNode **phead, char data){
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

// 연산자 우선순위를 반환하는 함수
int returnPriority(char operand){
    switch(operand){
        case '!' : case 'P' : case 'M' : return 6; // 단항 연산자 (!, +, -) -> 우선순위 6
        case '*' : case '/' : return 5;             // 곱셈, 나눗셈 -> 우선순위 5
        case '+' : case '-' : return 4;             // 이항 연산자 (+, -) -> 우선순위 4
        case '>' : case '<' : return 3;             // 관계 연산자 -> 우선순위 3
        case '&' : return 2;                        // 논리 AND (&&) -> 우선순위 2
        case '|' : return 1;                        // 논리 OR (||) -> 우선순위 1
        case '(' : return 0;                        // 여는 괄호 -> 우선순위 0
    }
    return -1;
}

int main(){
    int n;
    char tmp[101];
    char **str = NULL;
    
    if (scanf("%d", &n) != 1) return 0;
    
    str = (char **)malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++){ 
        scanf(" %s", tmp);
        str[i] = (char *)malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(str[i], tmp);
    }
    
    for (int i = 0; i < n; i++){
        ListNode *head = NULL; // 매 수식마다 스택 초기화
        int len = strlen(str[i]);
        
        for (int j = 0; j < len; j++){
            // 1. 여는 괄호 처리
            if (str[i][j] == '('){ 
                insertStack(&head, str[i][j]);
            }
            // 2. 닫는 괄호 처리
            else if (str[i][j] == ')'){ 
                while(head != NULL && head->data != '('){
                    // 스택에 있던 임시 단항 연산자 기호를 본래 기호로 복원하여 출력
                    if (head->data == 'P') printf("+");
                    else if (head->data == 'M') printf("-");
                    else if (head->data == '&') printf("&&");
                    else if (head->data == '|') printf("||");
                    else printf("%c", head->data);
                    
                    removeStack(&head);
                }
                removeStack(&head); // 스택에 남아있는 '(' 제거
            }
            // 3. 연산자 처리
            else if (str[i][j] == '!' || str[i][j] == '*' || str[i][j] == '/' || 
                     str[i][j] == '+' || str[i][j] == '-' || str[i][j] == '>' || 
                     str[i][j] == '<' || str[i][j] == '&' || str[i][j] == '|'){
                
                char currentOp = str[i][j];
                
                // 두 글자 연산자 (&&, ||) 예외 처리 및 인덱스 건너뛰기
                if (currentOp == '&' && j + 1 < len && str[i][j+1] == '&') { j++; }
                else if (currentOp == '|' && j + 1 < len && str[i][j+1] == '|') { j++; }
                
                // 단항 연산자 (+, -) 판별 로직
                if (currentOp == '+' || currentOp == '-') {
                    // 수식의 맨 처음이거나, 직전 문자가 피연산자(알파벳)나 닫는 괄호')'가 아니면 단항 연산자임
                    if (j == 0 || (str[i][j-1] != ')' && (str[i][j-1] < 'A' || str[i][j-1] > 'Z'))) {
                        if (currentOp == '+') currentOp = 'P'; // 단항 +는 임시로 'P'로 저장
                        else currentOp = 'M';                  // 단항 -는 임시로 'M'로 저장
                    }
                }
                
                int priorityOfOperand = returnPriority(currentOp);
                
                // 중요: if문 대신 while문을 사용하여 자신보다 우선순위가 높거나 같은 연산자를 모두 꺼냄
                while (head != NULL && returnPriority(head->data) >= priorityOfOperand){
                    if (head->data == 'P') printf("+");
                    else if (head->data == 'M') printf("-");
                    else if (head->data == '&') printf("&&");
                    else if (head->data == '|') printf("||");
                    else printf("%c", head->data);
                    
                    removeStack(&head);
                }
                insertStack(&head, currentOp); // 현재 연산자를 스택에 삽입
            }
            // 4. 피연산자(대문자 알파벳) 처리
            else{ 
                printf("%c", str[i][j]);
            }
        }
        
        // 수식을 다 읽은 후 스택에 남아있는 연산자들 모두 출력
        while (head != NULL){
            if (head->data == 'P') printf("+");
            else if (head->data == 'M') printf("-");
            else if (head->data == '&') printf("&&");
            else if (head->data == '|') printf("||");
            else printf("%c", head->data);
            
            removeStack(&head);
        }
        printf("\n");
    }

    // 동적 할당 해제
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }
    free(str);

    return 0;
}