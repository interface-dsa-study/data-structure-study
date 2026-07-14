#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 100
#define STRING_MAX_LENGTH 101

typedef struct Stack {
  int elements[STACK_CAPACITY + 1];
  int top_index;
} Stack;

Stack *createStack(void) {
  Stack *stack = malloc(sizeof(*stack));
  if (stack == NULL) {
    exit(EXIT_FAILURE);
  }
  stack->top_index = -1;
  return stack;
}

void destroyStack(Stack *stack) {
  if (stack == NULL) {
    return;
  }
  free(stack);
}

int size(Stack *stack) {
  return stack->top_index + 1;
}

bool isEmpty(Stack *stack) {
  return stack->top_index == -1;
}

bool isFull(Stack *stack) {
  return stack->top_index + 1 == STACK_CAPACITY;
}

void push(Stack *stack, int element) {
  if (isFull(stack)) {
    return;
  }

  stack->top_index++;
  stack->elements[stack->top_index] = element;
}

int pop(Stack *stack) {
  if (isEmpty(stack)) {
    return '\0';
  }

  int popped_element = stack->elements[stack->top_index];
  stack->top_index--;
  return popped_element;
}

int peek(Stack *stack) {
  if (isEmpty(stack)) {
    return '\0';
  }

  return stack->elements[stack->top_index];
}

bool isOperand(char input) {
  return input >= '0' && input <= '9';
}

int convertCharacterToNumber(char input) {
  if (!isOperand(input)) {
    return '\0';
  }
  return input - '0';
}

int calculate(int left_operand, int right_operand, char operator) {
  switch (operator) {
    case '+':
      return left_operand + right_operand;

    case '-':
      return left_operand - right_operand;

    case '*':
      return left_operand * right_operand;

    case '/':
      return left_operand / right_operand;

    default:
      return 0;
  }
}

int evalueatePostfixExpression(char *expression) {
  Stack *stack = createStack();
  int result = 0;

  for (int expression_index = 0; expression[expression_index] != '\0'; expression_index++) {
    char current_character = expression[expression_index];

    if (!isOperand(current_character)) {
      int operand = convertCharacterToNumber(current_character);
      push(stack, operand);
      continue;
    }
    int right_operand = pop(stack);
    int left_operand = pop(stack);
    result = calculate(left_operand, right_operand, current_character);
    push(stack, result);
  }

  result = pop(stack);
  destroyStack(stack);
  return result;
}

int main(void) {
  int n;
  char expression[STRING_MAX_LENGTH];

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", expression);
    int result = evalueatePostfixExpression(expression);
    printf("%d\n", result);
  }

  return 0;
}
