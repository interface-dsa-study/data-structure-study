
#define array_size 10000
#include <stdlib.h>

typedef struct {
    int X[array_size];//values array
    int value_amount;
} StockSpanner;


StockSpanner* stockSpannerCreate() {
    StockSpanner *obj=(StockSpanner*)malloc(sizeof(StockSpanner));
    obj->value_amount=0;
    return obj;
}

int stockSpannerNext(StockSpanner* obj, int price) {
    obj->X[obj->value_amount]=price;
    int span=1;
    for (int index=obj->value_amount-1 ; index>=0 && obj->X[index] <= price ; span++, index--);
    obj->value_amount++;
    return span;
}

void stockSpannerFree(StockSpanner* obj) {
    free(obj);
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);
 
 * stockSpannerFree(obj);
*/