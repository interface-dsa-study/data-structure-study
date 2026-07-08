#include <stdbool.h>
#include <stdlib.h>
#define STOCK_MAX_PRICE 100000
#define STOCK_MAX_COUNT 10000

typedef struct {
  int *stock_indexes;
  int top_index;
} StockSpanner;


StockSpanner *stockSpannerCreate() {
  StockSpanner *stock_spanner = malloc(sizeof(*stock_spanner));
  if (stock_spanner == NULL) {
    exit(EXIT_FAILURE);
  }

  stock_spanner->stock_indexes = malloc(sizeof(*stock_spanner->stock_indexes) * STOCK_MAX_COUNT);
  if (stock_spanner->stock_indexes == NULL) {
    free(stock_spanner);
    exit(EXIT_FAILURE);
  }

  stock_spanner->top_index = -1;

  return stock_spanner;
}

int size(StockSpanner *stock_spanner) {
  return stock_spanner->top_index + 1;
}

void push(StockSpanner *stock_spanner, int value) {
  stock_spanner->top_index++;
  stock_spanner->stock_indexes[stock_spanner->top_index] = value;
}

bool isEmpty(StockSpanner *stock_spanner) {
  return stock_spanner->top_index == -1;
}

int pop(StockSpanner *stock_spanner) {
  if (isEmpty(stock_spanner)) {
    return -1;
  }
  int popped_value = stock_spanner->stock_indexes[stock_spanner->top_index];
  stock_spanner->top_index--;
  return popped_value;
}

/**
 * - current value 보다 작은 앞의 값들은 모두 pop
 * - stack이 비어있는경우 -> (index + 1) push
 * - stack이 비어있지 않은 경우 -> index - stack.top
 * - stack에 index push
 */
int stockSpannerNext(StockSpanner *obj, int price) {
  for (int i = 0; i < size(obj); i++) {
    while (!isEmpty(obj) && obj->stock_indexes[i] <= price) {
      pop(obj);
    }
  }
}

void stockSpannerFree(StockSpanner *obj) {
  free(obj->stock_indexes);
  free(obj);
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);

 * stockSpannerFree(obj);
*/
