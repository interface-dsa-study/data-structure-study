#include <stdlib.h>

#define STOCK_MAX_CALL_COUNT 10000

typedef struct StockPriceSpan {
  int price;
  int span;
} StockPriceSpan;

typedef struct StockSpanner {
  StockPriceSpan stack[STOCK_MAX_CALL_COUNT];
  int topIndex;
} StockSpanner;

StockSpanner *stockSpannerCreate(void) {
  StockSpanner *stockSpanner = (StockSpanner *) malloc(sizeof(StockSpanner));

  if (stockSpanner == NULL) {
    return NULL;
  }

  stockSpanner->topIndex = -1;

  return stockSpanner;
}

int stockSpannerNext(StockSpanner *obj, int price) {
  int currentSpan = 1;

  /*
   * 현재 price보다 작거나 같은 이전 가격들은
   * 현재 span에 포함될 수 있으므로 stack에서 제거하면서 span을 합친다.
   */
  while (obj->topIndex >= 0 && obj->stack[obj->topIndex].price <= price) {
    currentSpan += obj->stack[obj->topIndex].span;
    obj->topIndex--;
  }

  obj->topIndex++;
  obj->stack[obj->topIndex].price = price;
  obj->stack[obj->topIndex].span = currentSpan;

  return currentSpan;
}

void stockSpannerFree(StockSpanner *obj) {
  free(obj);
}
