#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 중위수식 -> 후위수식 변환 로직
 * - 피연산자는 바로 출력, 연산자는 스택에 보관했다가 우선순위에 맞게 출력
 *
 * 1. 피연산자는 바로 출력
 * 2. 연산자는 스택에 넣음
 * 3. 현재 연산자보다 스택 top 연산자의 우선순위가 높거나 같으면 먼저 꺼냄
 * 4. 여는 괄호 '(' 는 무조건 스택에 push
 * 5. 닫는 괄호 ')'를 만나면 '('가 나올 때까지 pop
 * 6. 단항연산자 '!', '+', '-'는 피연산자 앞에 붙는 연산자
 * 7. 단항연산자가 들어오면 바로 스택에 넣음
 */
#define STACK_CAPACITY 100
#define MAX_POSTFIX_EXPRESSION 201

typedef struct Stack {
  char elements[STACK_CAPACITY];
  int top_index;
} Stack;

// 피연산자 여부
bool isOperand(char input) {
  return input >= 'A' && input <= 'Z';
}

// 연산자 시작 여부
bool isOperatorStart(char input) {
  return input == '!' ||
         input == '+' ||
         input == '-' ||
         input == '*' ||
         input == '/' ||
         input == '>' ||
         input == '<' ||
         input == '&' ||
         input == '|';
}

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

void push(Stack *stack, char element) {
  if (isFull(stack)) {
    return;
  }

  stack->top_index++;
  stack->elements[stack->top_index] = element;
}

char pop(Stack *stack) {
  if (isEmpty(stack)) {
    return '\0';
  }

  char popped_element = stack->elements[stack->top_index];
  stack->top_index--;
  return popped_element;
}

char peek(Stack *stack) {
  if (isEmpty(stack)) {
    return '\0';
  }

  return stack->elements[stack->top_index];
}

int getPriority(char input) {
  /**
   * '!': 단항 NOT
   * '@': 단항 +
   * '~': 단항 -
   * '&': &&
   * '|': ||
  */
  if (input == '!' || input == '@' || input == '~') {
    return 6;
  }

  if (input == '*' || input == '/') {
    return 5;
  }

  if (input == '+' || input == '-') {
    return 4;
  }

  if (input == '>' || input == '<') {
    return 3;
  }

  if (input == '&') {
    return 2;
  }

  if (input == '|') {
    return 1;
  }

  return 0;
}

bool isUnaryOperator(char input) {
  return input == '!' || input == '@' || input == '~';
}

// 후위수식에 연산자 추가
void appendOperator(char expression[], int *expression_index, char operator) {
  // 단일연산자 +
  if (operator == '@') {
    expression[*expression_index] = '+';
    *expression_index = *expression_index + 1;
    return;
  }

  // 단일연산자 -
  if (operator == '~') {
    expression[*expression_index] = '-';
    *expression_index = *expression_index + 1;
    return;
  }

  // &&
  if (operator == '&') {
    expression[*expression_index] = '&';
    *expression_index = *expression_index + 1;
    expression[*expression_index] = '&';
    *expression_index = *expression_index + 1;
    return;
  }

  // ||
  if (operator == '|') {
    expression[*expression_index] = '|';
    *expression_index = *expression_index + 1;
    expression[*expression_index] = '|';
    *expression_index = *expression_index + 1;
    return;
  }

  expression[*expression_index] = operator;
  *expression_index = *expression_index + 1;
}

// 현재 위치의 연산자를 읽고 내부 저장 문자로 변환
char readOperator(char expression[], int *expression_index, bool is_waiting_operand) {
  char current_character = expression[*expression_index];

  // '&&'
  if (current_character == '&') {
    *expression_index = *expression_index + 2;
    return '&';
  }

  // '||'
  if (current_character == '|') {
    *expression_index = *expression_index + 2;
    return '|';
  }

  // '+'
  if (current_character == '+') {
    *expression_index = *expression_index + 1;

    if (is_waiting_operand) {
      return '@';
    }
    return '+';
  }

  // '-'
  if (current_character == '-') {
    *expression_index = *expression_index + 1;

    if (is_waiting_operand) {
      return '~';
    }
    return '-';
  }

  *expression_index = *expression_index + 1;
  return current_character;
}

// 현재 연산자보다 우선순위가 높거나 같은 연산자를 먼저 출력
void popHigherOrSamePriorityOperators(
  Stack *stack,
  char expression[],
  int *expression_index,
  char current_operator
) {
  // 현재 연산자가 단항연산자인경우 무조건 push
  if (isUnaryOperator(current_operator)) {
    return;
  }

  while (!isEmpty(stack)) {
    char top_operator = peek(stack);

    if (top_operator == '(') {
      break;
    }

    if (getPriority(top_operator) >= getPriority(current_operator)) {
      appendOperator(expression, expression_index, pop(stack));
    } else {
      break;
    }
  }
}

// 중위수식 -> 후위수식
void convertInfixToPostfix(char expression[], char postfix_expression[]) {
  Stack *stack = createStack();

  int expression_index = 0;
  int postfix_expression_index = 0;

  /**
   * 피연산자를 기다리는 상태
   *
   * - 수식 시작 직후
   * - '(' 직후
   * - 연산자 직후
   *
   * -> true 에서 연산자가 나오면 단항연산자
   */
  bool is_waiting_operand = true;

  while (expression[expression_index] != '\0') {
    char current_character = expression[expression_index];

    // 피연산자인경우 postfix_expression 에 바로 추가
    if (isOperand(current_character)) {
      postfix_expression[postfix_expression_index] = current_character;
      postfix_expression_index++;
      expression_index++;

      is_waiting_operand = false;
    } else if (current_character == '(') {
      // '(' 인 경우 스택에 push
      push(stack, current_character);
      expression_index++;

      is_waiting_operand = true;
    } else if (current_character == ')') {
      while (!isEmpty(stack) && peek(stack) != '(') {
        appendOperator(postfix_expression, &postfix_expression_index, pop(stack));
      }

      if (!isEmpty(stack) && peek(stack) == '(') {
        pop(stack);
      }

      expression_index++;

      // 괄호로 묶인 수식 처리 완료
      is_waiting_operand = false;
    } else if (isOperatorStart(current_character)) {
      // 연산자 처리
      char current_operator = readOperator(expression, &expression_index, is_waiting_operand);

      // 연산자 우선순위 처리
      popHigherOrSamePriorityOperators(stack, postfix_expression, &postfix_expression_index, current_operator);

      // 스택 push
      push(stack, current_operator);

      // 연산자 뒤에는 피연산자 위치해야됨
      is_waiting_operand = true;
    } else {
      expression_index++;
    }
  }

  while (!isEmpty(stack)) {
    // 스택이 비어있을 때까지 연산자 출력
    appendOperator(postfix_expression, &postfix_expression_index, pop(stack));
  }

  postfix_expression[postfix_expression_index] = '\0';

  destroyStack(stack);
}

int main(void) {
  int n;
  char expression[STACK_CAPACITY + 1];
  char postfix_expression[MAX_POSTFIX_EXPRESSION];

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", expression);
    convertInfixToPostfix(expression, postfix_expression);
    printf("%s\n", postfix_expression);
  }
  return 0;
}
