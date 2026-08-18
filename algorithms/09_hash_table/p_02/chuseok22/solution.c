

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int getHashKey(int input, int table_size) {
  return input % table_size;
}

void insertItem(int *hash_table, int input, int table_size) {
  int hash_key = getHashKey(input, table_size);
  int collision_count = 0;
  while (hash_table[hash_key] != 0) {
    hash_key++;
    collision_count++;
    hash_key = getHashKey(hash_key, table_size);
  }
  hash_table[hash_key] = input;
  for (int index = 0; index < collision_count; index++) {
    printf("C");
  }
  printf("%d\n", hash_key);
}

void getItem(int *hash_table, int input, int table_size) {
  int hash_key = getHashKey(input, table_size);
  while (hash_table[hash_key] != input && hash_table[hash_key] != 0) {
    hash_key++;
    hash_key = getHashKey(hash_key, table_size);
  }
  if (hash_table[hash_key] == 0) {
    printf("-1\n");
    return;
  }
  printf("%d %d\n", hash_key, hash_table[hash_key]);
}

int main(void) {
  int table_size, key_count, student_number, current_input_count = 0;
  char command;
  scanf("%d %d", &table_size, &key_count);

  int *hash_table = calloc(table_size, sizeof(*hash_table));
  if (hash_table == NULL) {
    exit(EXIT_FAILURE);
  }

  while (true) {
    scanf(" %c", &command);
    if (command == 'i') {
      if (current_input_count >= key_count) {
        printf("입력 횟수 초과");
        exit(EXIT_FAILURE);
      }
      scanf(" %d", &student_number);
      insertItem(hash_table, student_number, table_size);
      current_input_count++;
    } else if (command == 's') {
      scanf(" %d", &student_number);
      getItem(hash_table, student_number, table_size);
    } else if (command == 'e') {
      break;
    }
  }

  free(hash_table);
  return EXIT_SUCCESS;
}
