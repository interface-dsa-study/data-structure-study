#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
  char *elements;
  int capacity;
  int topIndex;
} Stack;

Stack *createStack(int capacity) {
  Stack *stack = malloc(sizeof(*stack));

  if (stack == NULL) {
    fprintf(stderr, "stack 메모리 할당 실패\n");
    exit(EXIT_FAILURE);
  }

  stack->elements = malloc(sizeof(*stack->elements) * capacity);

  if (stack->elements == NULL) {
    fprintf(stderr, "stack elementss 메모리 할당 실패\n");
    free(stack);
    exit(EXIT_FAILURE);
  }

  stack->capacity = capacity;
  stack->topIndex = -1;

  return stack;
}

void destroyStack(Stack *stack) {
  if (stack == NULL) {
    return;
  }

  free(stack->elements);
  free(stack);
}

int size(Stack *stack) {
  return stack->topIndex + 1;
}

bool isEmpty(Stack *stack) {
  return stack->topIndex == -1;
}

bool isFull(Stack *stack) {
  return stack->topIndex + 1 == stack->capacity;
}

void push(Stack *stack, char element) {
  if (isFull(stack)) {
    printf("Stack FULL\n");
    return;
  }

  stack->topIndex++;
  stack->elements[stack->topIndex] = element;
}

char pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Empty\n");
    return '\0';
  }

  char poppedElement = stack->elements[stack->topIndex];
  stack->topIndex--;

  return poppedElement;
}

void peek(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Empty\n");
    return;
  }
  printf("%c\n", stack->elements[stack->topIndex]);
}

void duplicate(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Empty\n");
    return;
  }

  if (isFull(stack)) {
    printf("Stack FULL\n");
    return;
  }

  char poppedElement = pop(stack);
  push(stack, poppedElement);
  push(stack, poppedElement);
}

void upRotate(Stack *stack, int rotateCount) {
  if (rotateCount > size(stack)) {
    return;
  }

  if (rotateCount <= 1) {
    return;
  }
  int bottomIndex = stack->topIndex - rotateCount + 1;
  char topElement = stack->elements[stack->topIndex];

  for (int i = stack->topIndex; i > bottomIndex; i--) {
    stack->elements[i] = stack->elements[i - 1];
  }
  stack->elements[bottomIndex] = topElement;
}

// top D C B A => C B A D => ... => A D C B
void downRotate(Stack *stack, int rotateCount) {
  if (rotateCount > size(stack)) {
    return;
  }
  if (rotateCount <= 1) {
    return;
  }

  int bottomIndex = stack->topIndex - rotateCount + 1;
  char bottomElement = stack->elements[bottomIndex];

  for (int i = bottomIndex; i < stack->topIndex; i++) {
    stack->elements[i] = stack->elements[i + 1];
  }

  stack->elements[stack->topIndex] = bottomElement;
}

void print(Stack *stack) {
  for (int i = stack->topIndex; i >= 0; i--) {
    printf("%c", stack->elements[i]);
  }
  printf("\n");
}

int main(void) {
  int capacity, count;

  scanf("%d", &capacity);
  Stack *stack = createStack(capacity);

  scanf("%d", &count);
  char command[20];

  for (int i = 0; i < count; i++) {
    scanf("%s", command);

    if (strcmp(command, "PUSH") == 0) {
      char element;
      scanf(" %c", &element);
      push(stack, element);
    } else if (strcmp(command, "POP") == 0) {
      pop(stack);
    } else if (strcmp(command, "PEEK") == 0) {
      peek(stack);
    } else if (strcmp(command, "DUP") == 0) {
      duplicate(stack);
    } else if (strcmp(command, "UpR") == 0) {
      int rotateCount;
      scanf(" %d", &rotateCount);
      upRotate(stack, rotateCount);
    } else if (strcmp(command, "DownR") == 0) {
      int rotateCount;
      scanf(" %d", &rotateCount);
      downRotate(stack, rotateCount);
    } else if (strcmp(command, "PRINT") == 0) {
      print(stack);
    } else {
      fprintf(stderr, "잘못된 입력입니다.");
    }
  }
  destroyStack(stack);
  return 0;
}
