#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERTEX_MAX_COUNT 6

typedef struct AdjacentNode {
  int vertex_number;
  int weight;
  struct AdjacentNode *next;
} AdjacentNode;

typedef struct Graph {
  AdjacentNode *adjacency_list[VERTEX_MAX_COUNT + 1];
} Graph;

AdjacentNode *createAdjacentNode(int vertex_number, int weight) {
  AdjacentNode *new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    exit(EXIT_FAILURE);
  }

  new_node->vertex_number = vertex_number;
  new_node->weight = weight;
  new_node->next = NULL;
  return new_node;
}

void upsertAdjacentNode(Graph *graph, int vertex_number, int adjacent_vertex_number, int weight) {
  AdjacentNode *previous_node = NULL;
  AdjacentNode *current_node = graph->adjacency_list[vertex_number];

  // 오름차순 정렬
  while (current_node != NULL && current_node->vertex_number < adjacent_vertex_number) {
    previous_node = current_node;
    current_node = current_node->next;
  }

  // 이미 존재하는경우
  if (current_node != NULL && current_node->vertex_number == adjacent_vertex_number) {
    current_node->weight = weight;
    return;
  }

  AdjacentNode *new_node = createAdjacentNode(adjacent_vertex_number, weight);
  new_node->next = current_node;

  // 맨 앞 삽입
  if (previous_node == NULL) {
    graph->adjacency_list[vertex_number] = new_node;
    return;
  }

  previous_node->next = new_node;
}

void printAdjacentNode(Graph graph, int vertex_number) {
}

int main(void) {
  char command;
  int vertex_number, edge, weight;

  while (true) {
    scanf(" %c", &command);
    if (command == 'a') {
      scanf("%d", &vertex_number);
    } else if (command == 'm') {
      scanf("%d %d %d", &vertex_number, &edge, &weight);
    } else if (command == 'q') {
      break;
    } else {
      printf("invalid command");
      exit(EXIT_FAILURE);
    }
  }
  return EXIT_SUCCESS;
}


