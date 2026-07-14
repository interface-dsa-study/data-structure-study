#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
  int *values;
  int capacity;
  int front;
  int rear;
} Queue;

Queue *createQueue(int capacity) {
  Queue *queue = malloc(sizeof(*queue));
  if (queue == NULL) {
    exit(EXIT_FAILURE);
  }

  queue->values = calloc((size_t) capacity, sizeof(int));
  if (queue->values == NULL) {
    free(queue);
    exit(EXIT_FAILURE);
  }

  queue->capacity = capacity;
  queue->front = 0;
  queue->rear = 0;

  return queue;
}

void destroyQueue(Queue *queue) {
  if (queue == NULL) {
    return;
  }

  free(queue->values);
  free(queue);
}

bool isEmpty(Queue *queue) {
  return queue->front == queue->rear;
}

bool isFull(Queue *queue) {
  return (queue->rear + 1) % queue->capacity == queue->front;
}

bool enqueue(Queue *queue, int value) {
  if (isFull(queue)) {
    return false;
  }

  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->values[queue->rear] = value;
  return true;
}

bool dequeue(Queue *queue) {
  if (isEmpty(queue)) {
    return false;
  }

  queue->front = (queue->front + 1) % queue->capacity;
  queue->values[queue->front] = 0;
  return true;
}

void printArray(Queue *queue) {
  for (int i = 0; i < queue->capacity; i++) {
    printf(" %d", queue->values[i]);
  }
  printf("\n");
}

int main(void) {
  int queueSize = 0, operationCount = 0;
  scanf("%d", &queueSize);
  scanf("%d", &operationCount);

  Queue *queue = createQueue(queueSize);

  for (int i = 0; i < operationCount; i++) {
    char operationType;
    scanf(" %c", &operationType);

    if (operationType == 'I') {
      int value;
      scanf("%d", &value);

      if (!enqueue(queue, value)) {
        printf("overflow");
        printArray(queue);
        destroyQueue(queue);
        exit(EXIT_SUCCESS);
      }
    } else if (operationType == 'D') {
      if (dequeue(queue)) {
        printf("underflow");
        destroyQueue(queue);
        exit(EXIT_SUCCESS);
      }
    } else if (operationType == 'P') {
      printArray(queue);
    }
  }
  destroyQueue(queue);
  return EXIT_SUCCESS;
}
