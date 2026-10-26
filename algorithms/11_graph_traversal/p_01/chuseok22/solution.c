#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_COUNT 100

typedef struct AdjacentNode {
  int vertex_number;
  struct AdjacentNode *next;
} AdjacentNode;

typedef struct Graph {
  AdjacentNode *adjacency_list[MAX_VERTEX_COUNT + 1];
  bool is_visited[MAX_VERTEX_COUNT + 1];
} Graph;

AdjacentNode *createAdjacentNode(int vertex_number) {
  AdjacentNode *new_adjacent_node = malloc(sizeof(*new_adjacent_node));
  if (new_adjacent_node == NULL) {
    exit(EXIT_FAILURE);
  }
  new_adjacent_node->vertex_number = vertex_number;
  new_adjacent_node->next = NULL;
  return new_adjacent_node;
}

// 인접 리스트에 정점을 오름차순으로 삽입
void insertAdjacentNode(Graph *graph, int vertex_number, int adjacent_vertex_number) {
  AdjacentNode *previous_node = NULL;
  AdjacentNode *current_node = graph->adjacency_list[vertex_number];

  while (current_node != NULL && adjacent_vertex_number > current_node->vertex_number) {
    // pass
    previous_node = current_node;
    current_node = current_node->next;
  }

  AdjacentNode *new_node = createAdjacentNode(adjacent_vertex_number);

  // 맨 앞인 경우
  if (previous_node == NULL) {
    graph->adjacency_list[vertex_number] = new_node;
    new_node->next = current_node;
    return;
  }

  previous_node->next = new_node;
  new_node->next = current_node;
}

// 무방향 간선 추가
void addEdge(Graph *graph, int first_vertex_number, int second_vertex_number) {
  insertAdjacentNode(graph, first_vertex_number, second_vertex_number);
  insertAdjacentNode(graph, second_vertex_number, first_vertex_number);
}

// DFS
void depthFirstSearch(Graph *graph, int vertex_number) {
  AdjacentNode *current_node = graph->adjacency_list[vertex_number];

  while (current_node != NULL) {
    if (!graph->adjacency_list[current_node->vertex_number]) {
    }
  }
}

int main(void) {
  int vertex_count, edge_count, vertex_start_number;
  int first_vertex_number, second_vertex_number;

  Graph graph;

  scanf("%d %d %d", &vertex_count, &edge_count, &vertex_start_number);

  for (int index = 0; index < edge_count; index++) {
    scanf("%d %d", &first_vertex_number, &second_vertex_number);
    addEdge(&graph, first_vertex_number, second_vertex_number);
  }
}
