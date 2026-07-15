#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct StockSpanner{
    int spidx;
    int index;
    int Top;
    int arr[10000];
    int stack[10000];
    int span[10000];
} StockSpanner;


StockSpanner* stockSpannerCreate() {
    StockSpanner* StS = (StockSpanner*)malloc(sizeof(StockSpanner));
    StS->Top = -1;
    StS->index = 0;
    StS->spidx = 0;
    StS->span[0] = 1;
    return StS;
}

void push(StockSpanner* obj) {
    obj->Top++;
    obj->stack[obj->Top] = obj->index;
}

int pop(StockSpanner* obj) {
    int p = obj->stack[obj->Top];
    obj->Top--;

    return p;
}

int stockSpannerNext(StockSpanner* obj, int price) {
    int a;
    obj->arr[obj->index] = price;
    if (obj->index == 0) {
        obj->span[obj->index] = 1;
    }
    if (obj->Top == -1) {
        push(obj);
    }
    else {
        while (obj->Top != -1 && obj->arr[obj->stack[obj->Top]] <= price) {
            pop(obj);
        }
        push(obj);
        obj->span[obj->index] = obj->index - obj->stack[obj->Top-1];
    }
    obj->index++;

    return 0;
}

void stockSpannerFree(StockSpanner* obj) {

}

int main() {
    StockSpanner* st = NULL;
    st = stockSpannerCreate();

    stockSpannerNext(st, 100);
    stockSpannerNext(st, 80);
    stockSpannerNext(st, 60);
    stockSpannerNext(st, 70);
    stockSpannerNext(st, 60);
    stockSpannerNext(st, 75);
    stockSpannerNext(st, 85);

    for (int i = 0;i < st->index;i++) {
        printf("%d", st->span[i]);
    }

}