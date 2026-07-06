#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Stack {
  char *elements;
  int topIndex;
  int capacity;
} Stack;

Stack *createStack(int capacity) {
  Stack *stack = malloc(sizeof(*stack));

  if (stack == NULL) {
    fprintf(stderr, "stack 메모리 할당 실패");
    exit(EXIT_FAILURE);
  }

  stack->elements = malloc(sizeof(*stack->elements) * capacity);
  if (stack->elements == NULL) {
    fprintf(stderr, "stack elements 메모리 할당 실패");
    free(stack);
    exit(EXIT_FAILURE);
  }

  stack->topIndex = -1;
  stack->capacity = capacity;

  return stack;
}

void destroyStack(Stack *stack) {
  free(stack->elements);
  free(stack);
}

bool isFull(Stack *stack) {
  return stack->topIndex + 1 == stack->capacity;
}

bool isEmpty(Stack *stack) {
  return stack->topIndex == -1;
}

void push(Stack *stack, char element) {
  if (isFull(stack)) {
    fprintf(stderr, "배열이 FULL 상태라 PUSH 불가");
    return;
  }
  stack->topIndex++;
  stack->elements[stack->topIndex] = element;
}

char pop(Stack *stack) {
  if (isEmpty(stack)) {
    fprintf(stderr, "배열이 비어있어 POP 불가");
    return '\0';
  }
  char targetElement = stack->elements[stack->topIndex];
  stack->topIndex--;
  return targetElement;
}

bool isLeftBracket(char input) {
  return input == '(' || input == '{' || input == '[';
}

bool isRightBracket(char input) {
  return input == ')' || input == '}' || input == ']';
}

bool isValidBracketSet(Stack *stack, char rightBracket) {
  if (rightBracket == ')') {
    if (pop(stack) != '(') {
      return false;
    }
  } else if (rightBracket == '}') {
    if (pop(stack) != '{') {
      return false;
    }
  } else if (rightBracket == ']') {
    if (pop(stack) != '[') {
      return false;
    }
  }
  return true;
}

int main(void) {
  Stack *stack = createStack(1000);
  char input[10001];
  int bracketCount = 0;
  bool isValid = true;

  // scanf("%s", input); 의 경우 공백, 탭, 개행에서 입력이 중단됨
  // 개행 문자의 경우 읽지 않고 입력 버퍼에 남김
  fgets(input, sizeof(input), stdin);

  for (int i = 0; input[i] != '\0'; i++) {
    if (isLeftBracket(input[i])) {
      push(stack, input[i]);
      bracketCount++;
    } else if (isRightBracket(input[i])) {
      bracketCount++;
      if (!isValidBracketSet(stack, input[i])) {
        isValid = false;
      }
    }
  }

  if (!isEmpty(stack)) {
    isValid = false;
  }

  if (isValid) {
    printf("OK_%d", bracketCount);
  } else {
    printf("Wrong_%d", bracketCount);
  }

  destroyStack(stack);
  return 0;
}
