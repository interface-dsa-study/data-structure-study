#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* graph[101]; // 인접 리스트의 헤드 포인터 배열
int visited[101]; // 방문 여부를 체크할 배열 (0: 미방문, 1: 방문)

// 인접 리스트에 간선 추가 (정점 번호가 작은 순서대로 조사해야 하므로 오름차순 삽입)
void insert_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;

    // 리스트가 비어있거나, 새 노드가 가장 작은 값일 경우 맨 앞에 삽입
    if (graph[u] == NULL || graph[u]->vertex > v) {
        newNode->next = graph[u];
        graph[u] = newNode;
    } else {
        // 오름차순 정렬 위치를 찾아 삽입
        Node* curr = graph[u];
        while (curr->next != NULL && curr->next->vertex < v) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

// 재귀를 이용한 DFS 함수
void dfs(int v) {
    visited[v] = 1;        // 현재 정점 방문 표시
    printf("%d\n", v);     // 방문한 정점 출력

    // 현재 정점과 연결된 인접 정점들 탐색
    Node* curr = graph[v];
    while (curr != NULL) {
        int w = curr->vertex;
        if (!visited[w]) { // 아직 방문하지 않은 정점이라면
            dfs(w);        // 재귀 호출
        }
        curr = curr->next;
    }
}

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    // 포인터 배열 및 방문 배열 초기화
    for (int i = 1; i <= n; i++) {
        graph[i] = NULL;
        visited[i] = 0;
    }

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        // 무방향 간선이므로 양방향으로 모두 추가해 주어야 함
        insert_edge(u, v);
        insert_edge(v, u);
    }

    // s 정점에서 DFS 시작
    dfs(s);

    return 0;
}