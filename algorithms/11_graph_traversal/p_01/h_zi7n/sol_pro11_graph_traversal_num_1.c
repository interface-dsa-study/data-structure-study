#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
}Node;

Node* graph[101];
int visited[101];

void make_graph(int V_a, int V_b) {
    Node* newnode = malloc(sizeof(Node*));
    newnode->vertex = V_b;
    newnode->next = NULL;
    graph[V_a]->vertex = V_a;
    graph[V_b]->vertex = V_b;
    graph[V_a][V_b].next = graph[V_b];
    graph[V_b][V_a].next = graph[V_a];
}

void print(int n, int s) { // 시작점만 입력 받으면 됨.
    int score = 1;
    printf("%d\n", graph[s]->vertex);
    for (int i = 1; score <= n ;i++) {
        if (graph[s][i].next != NULL) {
            printf("%d\n", graph[s][i].next->vertex);
            // 한 방향씩만 연결 끊어도 prev로 이동할 일 X.
            graph[s][i].next = NULL; graph[i][s].next = NULL;
            s = i;
            i = 1;
            score++;
        }
    }
}

int main() {
    int n, m, s; // n은 정점 개수, m은 간선 개수, s는 시작점.
    scanf("%d%d%d", &n, &m, &s);
    int V_a, V_b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &V_a, &V_b);
        make_graph(V_a, V_b);
    }
    print(n, s);
}