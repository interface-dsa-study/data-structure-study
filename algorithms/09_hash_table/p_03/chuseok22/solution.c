#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int getFirstHashKey(int key, int table_size) {
  return key % table_size;
}

int getSecondHashKey(int key, int salt) {
  return salt - (key % salt);
}

int calculateHashKey(int first_hash_key, int second_hash_key, int collision_count, int table_size) {
  return (first_hash_key + collision_count * second_hash_key) % table_size;
}

void insertItem(int *hash_table, int key, int table_size, int salt) {
  int first_hash_key = getFirstHashKey(key, table_size);
  int second_hash_key = getSecondHashKey(key, salt);
  int collision_count = 0;
  int hash_key = calculateHashKey(first_hash_key, second_hash_key, collision_count, table_size);

  while (hash_table[hash_key] != 0) {
    collision_count++;
    hash_key = calculateHashKey(first_hash_key, second_hash_key, collision_count, table_size);
  }
  hash_table[hash_key] = key;
  for (int index = 0; index < collision_count; index++) {
    printf("C");
  }
  printf("%d\n", hash_key);
}

void getItem(int *hash_table, int key, int table_size, int salt) {
  int first_hash_key = getFirstHashKey(key, table_size);
  int second_hash_key = getSecondHashKey(key, salt);
  int collision_count = 0;
  int hash_key = calculateHashKey(first_hash_key, second_hash_key, collision_count, table_size);

  while (hash_table[hash_key] != key && hash_table[hash_key] != 0) {
    collision_count++;
    hash_key = calculateHashKey(first_hash_key, second_hash_key, collision_count, table_size);
  }
  // 타겟이 없는 경우
  if (hash_table[hash_key] == 0) {
    printf("-1\n");
    return;
  }
  printf("%d %d\n", hash_key, hash_table[hash_key]);
}

void printHashTable(int *hash_table, int table_size) {
  for (int index = 0; index < table_size; index++) {
    printf(" %d", hash_table[index]);
  }
  printf("\n");
}

int main(void) {
  int table_size, max_input_count, salt;
  scanf("%d %d %d", &table_size, &max_input_count, &salt);

  int *hash_table = calloc(table_size, sizeof(*hash_table));
  if (hash_table == NULL) {
    exit(EXIT_FAILURE);
  }

  while (true) {
    char command;
    int key;
    scanf(" %c", &command);
    if (command == 'i') {
      scanf("%d", &key);
      insertItem(hash_table, key, table_size, salt);
    } else if (command == 's') {
      scanf("%d", &key);
      getItem(hash_table, key, table_size, salt);
    } else if (command == 'p') {
      printHashTable(hash_table, table_size);
    } else if (command == 'e') {
      printHashTable(hash_table, table_size);
      break;
    }
  }

  free(hash_table);
  return EXIT_SUCCESS;
}
