#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;        // 연결된 정점 번호
    int weight;        // 가중치
    struct Node* next; // 다음 인접 노드를 가리키는 포인터
} Node;

Node* graph[7] = {NULL, };

// 단방향 간선을 삽입하고, 수정하고, 삭제를 동시에 진행하는 녀석.
void update_directed_edge(int u, int v, int w) {
    Node* prev = NULL;
    Node* curr = graph[u];
    while (curr != NULL && curr->vertex < v) {
        prev = curr;
        curr = curr->next;
    }
    // 1. 이미 간선이 존재하는 경우.
    if (curr != NULL && curr->vertex == v) {
        // 1. w = 0이면 삭제 진행.
        if (w == 0) { // 문제 조건에 따라 w = 0 이면 간선 삭제.
            if (prev == NULL) graph[u] = curr->next;
            else prev->next = curr->next;
            free(curr);
        }
        // 2. w != 0 이면 그냥 가중치 새로 덮어 씌우면 됨.
        else {
            curr->weight = w;
        }
    }
    // 간선이 존재하지 않는 경우.
    else {
        if (w != 0) {
            Node* newnode = malloc(sizeof(Node*));
            newnode->vertex = v;
            newnode->weight = w;
            newnode->next = curr;
            if (prev == NULL) graph[u] = newnode;
            else prev->next = newnode;
        }
    }
}

void modify_edge(int a, int b, int w) {
    if (a < 1 || a > 6 || b < 1 || b > 6) {
        printf("-1\n");
        return;
    }
    // a -> b 로 가는 간선 방향 업데이트.
    update_directed_edge(a, b, w);
    if (a != b) update_directed_edge(b, a, w);
}

void init_graph() {
    modify_edge(1,2,1);
    modify_edge(1,3,1);
    modify_edge(1,4,1);
    modify_edge(1,6,2);
    modify_edge(2,3,1);
    modify_edge(3,5,4);
    modify_edge(5,5,4);
    modify_edge(5,6,3);
}

void print(int a) {
    if (a < 1 || a > 6) {
        printf("-1\n");
        return;
    }
    Node* curr = graph[a];
    while (curr != NULL) {
        printf(" %d %d", curr->vertex, curr->weight);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    init_graph();
    Node* node = malloc(sizeof(Node*));
    char order; int a, b, w, node_number;
    for (;;) {
        scanf(" %c", &order);
        if (order == 'a') {
            scanf("%d", &node_number);
            print(node_number);
        }
        else if (order == 'm') {
            scanf("%d%d%d", &a, &b, &w);
            modify_edge(a, b, w);
        }
        else if (order == 'q') {
            break;
        }
    }
    return 0;
}