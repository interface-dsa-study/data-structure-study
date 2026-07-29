#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPERATION_MAX_LENGTH 100

bool is_operand(char input) {
  return input >= '0' && input <= '9';
}

bool is_operator(char input) {
  return input == 'p' ||
         input == 'm' ||
         input == '!' ||
         input == '*' ||
         input == '%' ||
         input == '/' ||
         input == '+' ||
         input == '-' ||
         input == '<' ||
         input == '>' ||
         input == '=' ||
         input == '&' ||
         input == '|';
}

bool is_unary_operator(char input) {
  return input == 'p' || input == 'm' || input == '!';
}

int get_priority(char input) {
  if (input == 'p' || input == 'm' || input == '!') {
    return 7;
  } else if (input == '*' || input == '%' || input == '/') {
    return 6;
  } else if (input == '+' || input == '-') {
    return 5;
  } else if (input == '<' || input == '>') {
    return 4;
  } else if (input == '=') {
    return 3;
  } else if (input == '&') {
    return 2;
  } else if (input == '|') {
    return 1;
  } else {
    exit(EXIT_FAILURE);
  }
}

int convert_char_to_int(char input) {
  if (!is_operand(input)) {
    return '\0';
  }
  return input - '0';
}

int calculate_unary_expression(int operand, char operator) {
  switch (operator) {
    case 'p':
      return operand;
    case 'm':
      return -operand;
    case '!':
      return operand == 0;
    default:
      exit(EXIT_FAILURE);
  }
}

int calculate_binary_expression(int left_operand, int right_operand, char operator) {
  switch (operator) {
    case '*':
      return left_operand * right_operand;
    case '%':
      return left_operand % right_operand;
    case '/':
      return left_operand / right_operand;
    case '+':
      return left_operand + right_operand;
    case '-':
      return left_operand - right_operand;
    case '<':
      return left_operand < right_operand;
    case '>':
      return left_operand > right_operand;
    case '=':
      return left_operand == right_operand;
    case '&':
      return left_operand && right_operand;
    case '|':
      return left_operand || right_operand;
    default:
      exit(EXIT_FAILURE);
  }
}

int execute_prefix_expression(char *prefix_expression, int *index) {
  /**
   * 1. 연산자: 재귀호출
   * 2. 이항연산자 뒤 피연산자 1개: 재귀호출
   * 3. 이항연산자 뒤 피연산자 2개: 계산
   * 4. 단항연산자 뒤 피연산자: 계산
   */

  char current_character = prefix_expression[*index];
  (*index)++;

  // 재귀 종료: 피연산자를 만나는 경우
  if (is_operand(current_character)) {
    return convert_char_to_int(current_character);
  }

  // 단항연산자인경우 피연산자 1개 소비
  if (is_unary_operator(current_character)) {
    int operand = execute_prefix_expression(prefix_expression, index);
    return calculate_unary_expression(operand, current_character);
  }

  // 이항연산자인경우 피연산자 2개 소비
  int left_operand = execute_prefix_expression(prefix_expression, index);
  int right_operand = execute_prefix_expression(prefix_expression, index);
  return calculate_binary_expression(left_operand, right_operand, current_character);
}

int main(void) {
  int operation_count = 0, index = 0;
  char operation[OPERATION_MAX_LENGTH + 1];

  scanf("%d", &operation_count);
  for (int i = 0; i < operation_count; i++) {
    scanf("%s", operation);
    index = 0;
    int result = execute_prefix_expression(operation, &index);
    printf("%d\n", result);
  }
}
