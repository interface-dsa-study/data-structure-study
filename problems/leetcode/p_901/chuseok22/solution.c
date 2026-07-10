#include <stdbool.h>
#include <stdlib.h>
#define STOCK_MAX_PRICE 100000
#define STOCK_MAX_COUNT 10000

/**
 * 스택의 각 원소가 저장할 정보
 *
 * - price: 해당 날짜의 주식 가격
 * - span: 해당 가격의 연속 날짜 수
 */
typedef struct {
  int price;
  int span;
} StockSpanElement;

/**
 * 스택
 */
typedef struct {
  StockSpanElement element_array[STOCK_MAX_COUNT];
  int capacity;
  int top_index;
} StockSpanner;


StockSpanner *stockSpannerCreate() {
  StockSpanner *stock_spanner = malloc(sizeof(*stock_spanner));
  if (stock_spanner == NULL) {
    exit(EXIT_FAILURE);
  }

  stock_spanner->capacity = STOCK_MAX_COUNT;
  stock_spanner->top_index = -1;

  return stock_spanner;
}

int size(StockSpanner *stock_spanner) {
  return stock_spanner->top_index + 1;
}

bool isEmpty(StockSpanner *stock_spanner) {
  return stock_spanner->top_index == -1;
}

bool isFull(StockSpanner *stock_spanner) {
  return stock_spanner->top_index + 1 == stock_spanner->capacity;
}

void push(StockSpanner *stock_spanner, StockSpanElement stock_span_element) {
  if (isFull(stock_spanner)) {
    exit(EXIT_FAILURE);
  }

  stock_spanner->top_index++;
  stock_spanner->element_array[stock_spanner->top_index] = stock_span_element;
}

StockSpanElement pop(StockSpanner *stock_spanner) {
  if (isEmpty(stock_spanner)) {
    exit(EXIT_FAILURE);
  }

  StockSpanElement popped_element = stock_spanner->element_array[stock_spanner->top_index];
  stock_spanner->top_index--;
  return popped_element;
}

StockSpanElement peek(StockSpanner *stock_spanner) {
  if (isEmpty(stock_spanner)) {
    exit(EXIT_FAILURE);
  }
  return stock_spanner->element_array[stock_spanner->top_index];;
}

/**
 * 현재 가격의 span 계산
 *
 * 1. span = 1 시작
 * 2. "오늘 가격 >= 스택 최상단 가격" 인 경우 pop
 * 3. pop한 원소의 span 은 오늘 span 에 누적
 * 4. 오늘 가격과 계산된 span 을 스택에 push
 * 5. 계산된 span 반환
 */
int stockSpannerNext(StockSpanner *obj, int price) {
  int current_span = 1;

  while (!isEmpty(obj) && peek(obj).price <= price) {
    current_span += pop(obj).span;
  }

  StockSpanElement stock_span_element;
  stock_span_element.price = price;
  stock_span_element.span = current_span;

  push(obj, stock_span_element);

  return current_span;
}

void stockSpannerFree(StockSpanner *obj) {
  if (obj == NULL) {
    return;
  }
  free(obj);
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);

 * stockSpannerFree(obj);
*/
