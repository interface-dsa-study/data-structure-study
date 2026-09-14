#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  char element;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct List {
  Node *header;
  Node *trailer;
  int size;
} List;

Node *createNode(char element) {
  // 새로운 노드 동적할당
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->element = element;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

List *createList(void) {
  // 새로운 리스트 동적할당
  List *list = malloc(sizeof(*list));
  if (list == NULL) {
    exit(EXIT_FAILURE);
  }

  // header, trailer 초기화
  list->header = createNode('\0');
  list->trailer = createNode('\0');

  list->header->next = list->trailer;
  list->trailer->prev = list->header;

  list->size = 0;
  return list;
}

Node *getNode(List *list, int rank) {
  Node *current_node = list->header;

  // 리스트에서 입력 rank 만큼 뒤로 이동
  for (int index = 0; index < rank; index++) {
    current_node = current_node->next;
  }
  return current_node;
}

void get(List *list, int rank) {
  Node *target_node = getNode(list, rank);

  // 잘못된 rank 입력 시
  if (target_node == list->header || target_node == list->trailer) {
    printf("invalid position\n");
    return;
  }
  printf("%c\n", target_node->element);
}

void add(List *list, int rank, char element) {
  // 입력 rank 가 잘못된 경우
  if (rank > list->size + 1) {
    printf("invalid position\n");
    return;
  }

  Node *new_node = createNode(element); // 새로운 노드 생성
  Node *target_node = getNode(list, rank); // 현 위치 노드 반환

  // 가장 앞에 삽입하는경우
  if (rank == 1) {
    // 이중 연결 리스트 노드 연결
    new_node->prev = list->header;
    new_node->next = target_node;

    list->header->next = new_node;
    target_node->prev = new_node;

    list->size++;
    return;
  }
  // 이중 연결 리스트 노드 언결
  new_node->prev = target_node->prev;
  new_node->next = target_node;

  target_node->prev->next = new_node;
  target_node->prev = new_node;

  // 리스트 size 증가
  list->size++;
}

void deleteNode(List *list, int rank) {
  // 잘못된 rank 입력 시
  if (rank > list->size) {
    printf("invalid position\n");
    return;
  }

  // target_node 연결 제거
  Node *target_node = getNode(list, rank);
  Node *previous_node = target_node->prev;
  Node *next_node = target_node->next;

  previous_node->next = next_node;
  next_node->prev = previous_node;

  // target_node 메모리 해제
  free(target_node);
  list->size--;
}

void print(List *list) {
  if (list == NULL) {
    return;
  }

  Node *current_node = list->header->next;

  // 리스트 순회 및 출력
  while (current_node != NULL && current_node != list->trailer) {
    printf("%c", current_node->element);
    current_node = current_node->next;
  }
  printf("\n");
}

void destroyList(List *list) {
  if (list == NULL) {
    return;
  }
  Node *current_node = list->header;

  // 리스트 순회 동적할당 제거
  while (current_node != NULL) {
    Node *next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  free(list);
}

int main(void) {
  int count, rank;
  char operator, element;
  List *list = createList();

  scanf("%d", &count);
  for (int i = 0; i < count; i++) {
    scanf(" %c", &operator);

    if (operator == 'A') {
      scanf("%d %c", &rank, &element);
      add(list, rank, element);
    } else if (operator == 'D') {
      scanf("%d", &rank);
      deleteNode(list, rank);
    } else if (operator == 'G') {
      scanf("%d", &rank);
      get(list, rank);
    } else if (operator == 'P') {
      print(list);
    } else {
      exit(EXIT_FAILURE);
    }
  }
  destroyList(list);
  return EXIT_SUCCESS;
}
