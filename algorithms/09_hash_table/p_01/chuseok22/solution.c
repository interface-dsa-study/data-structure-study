#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;
  struct Node *next;
} Node;

typedef struct HashTable {
  Node *head;
} HashTable;

Node *createNode(int key) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->key = key;
  node->next = NULL;
  return node;
}

int hashFunction(int key, int size) {
  return key % size;
}

void insertItem(HashTable *hash_table, int key, int size) {
  int hash_key = hashFunction(key, size);

  Node *new_node = createNode(key);
  // 버킷 리스트 맨 앞 삽입
  new_node->next = hash_table[hash_key].head;
  hash_table[hash_key].head = new_node;
}

int getItem(HashTable *hash_table, int key, int size) {
  int hash_key = hashFunction(key, size);
  int rank = 1;

  Node *current_node = hash_table[hash_key].head;
  while (current_node != NULL) {
    if (current_node->key == key) {
      return rank;
    }
    rank++;
    current_node = current_node->next;
  }

  return 0;
}

int removeItem(HashTable *hash_table, int key, int size) {
  int hash_key = hashFunction(key, size);
  int rank = getItem(hash_table, key, size);

  if (rank == 0) {
    return rank;
  }

  Node *target_node = hash_table[hash_key].head;
  Node *previous_node = NULL;
  for (int index = 1; index < rank; index++) {
    previous_node = target_node;
    target_node = target_node->next;
  }

  // 헤더인경우
  if (target_node == hash_table[hash_key].head) {
    hash_table[hash_key].head = target_node->next;
    free(target_node);
    return rank;
  }
  previous_node->next = target_node->next;
  free(target_node);
  return rank;
}

void destroyNode(Node *node) {
  if (node == NULL) {
    return;
  }
  Node *current_node = node;
  while (current_node != NULL) {
    Node *next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
}

void destroyHashTable(HashTable *hash_table, int size) {
  for (int index = 0; index < size; index++) {
    destroyNode(hash_table[index].head);
  }
  free(hash_table);
}

void printHashTable(HashTable *hash_table, int size) {
  for (int index = 0; index < size; index++) {
    Node *current_node = hash_table[index].head;
    while (current_node != NULL) {
      printf(" %d", current_node->key);
      current_node = current_node->next;
    }
  }
  printf("\n");
}

int main(void) {
  int size;
  scanf("%d", &size);

  HashTable *hash_table = calloc(size, sizeof(*hash_table));
  if (hash_table == NULL) {
    exit(EXIT_FAILURE);
  }

  char operator;
  int key;
  while (true) {
    scanf(" %c", &operator);
    if (operator == 'i') {
      scanf("%d", &key);
      insertItem(hash_table, key, size);
    } else if (operator == 's') {
      scanf("%d", &key);
      printf("%d\n", getItem(hash_table, key, size));
    } else if (operator == 'd') {
      scanf("%d", &key);
      printf("%d\n", removeItem(hash_table, key, size));
    } else if (operator == 'p') {
      printHashTable(hash_table, size);
    } else if (operator == 'e') {
      break;
    } else {
      exit(EXIT_FAILURE);
    }
  }
  destroyHashTable(hash_table, size);
  return EXIT_SUCCESS;
}
