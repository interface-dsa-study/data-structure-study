#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // 헤더와 트레일러 사이의 노드
    struct Node* prev;
    struct Node* next;
    char data;
} Node;

typedef struct List { //헤더와 트레일러
    struct Node* head;
    struct Node* trail;
}List;

void link(List* list) {
    list->head = (Node*)malloc(sizeof(Node)); // 헤더와 트레일러 생성하고 서로 연결
    list->trail = (Node*)malloc(sizeof(Node));

    list->head->prev = NULL;
    list->trail->next = NULL;
    list->head->next = list->trail;
    list->trail->prev = list->head;

}

void add_node(List* list, char ma, int n) { // 헤더와 트레일러 사이의 추가할 노드 생성
    Node* node = (Node*)malloc(sizeof(Node));
    Node* temp;
    int i = 0;
    node->data = ma;
    temp = list->head;
    for (i = 1; i < n ; i++) {
        temp = temp->next;
        if (temp == list->trail) { // 추가할 위치가 유효한지 검사
            printf("invalid position\n");
            return; // 유효하지 않으면 종료
        }
    }
    node->next = temp->next; // 유효하면 노드 생성하고 추가
    node->prev = temp;
    temp->next->prev = node;
    temp->next = node;
}

void delete_node(List* list, int r) { //노드 삭제
    int i;
    Node* temp = list->head->next;
    for (i = 1; i < r && temp != list->trail; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) { // 삭제할 위치가 유효한지 검사
        printf("invalid position\n");
        return;
    }
    else { // 유효하면 삭제할 노드의 앞과 뒤를 연결
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        free(temp); // 삭제할 노드 메모리 할당 해제
    }
}

void get_node(List* list, int r) { // 노드 원소 출력
    int i;
    Node* temp = list->head->next;
    for (i = 1; i < r && temp != list->trail; i++) {
        temp = temp->next;
    }
    if (temp == list->trail) { // 출력할 노드의 위치가 유효한지 검사
        printf("invalid position");
        return;
    }
    else {
        printf("%c", temp->data); // 유효하면 출력
    }
}
void print(List* list) { // 추가한 순서대로 출력
    Node* node = list->head->next;
    while (node != list->trail) {
        printf("%c", node->data);
        node = node->next;
    }
}
void free_list(Node* node) { // 할당 해제
    if (node) {
        free_list(node->next);
        free(node);
    }
}

int main() {
    List li = { NULL };
    int N, r, i;
    char ma1, ma2;

    link(&li); // 헤더와 트레일러 생성

    scanf("%d", &N); // 연산 횟수

    for (i = 0; i < N; i++) {
        scanf(" %c", &ma1); // 연산의 종류 입력

        if (ma1 == 'A') {
            scanf("%d %c", &r, &ma2); // 어떤 위치에 추가할 건지 입력
            add_node(&li, ma2, r); // 추가 함수 실행
        }
        else if (ma1 == 'D') {
            scanf("%d", &r); // 어떤 위치의 노드를 삭제할 건지 입력
            delete_node(&li, r); // 삭제 함수 실행
        }
        else if (ma1 == 'G') {
            scanf("%d", &r); // 출력할 노드 순서 입력
            get_node(&li, r); // 출력 함수 실행
            printf("\n");
        }
        else {
            print(&li); // 순서대로 출력
            printf("\n");
        }
    }

    free_list(li.head); // 메모리 해제 함수 실행

    return 0;
}