#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int e; int top;
}StockSpanner;

typedef struct {
    StockSpanner* next;
    StockSpanner* header;
}List;

StockSpanner* StockSpannerCreate() { // 새로운 스톡스패너 생성.
    StockSpanner* t = NULL;
    t->top += 1; // top위치 옮겨 주기.
    t = (StockSpanner*)malloc(sizeof(StockSpanner));
    return t;
}

int StockSpannerNext(StockSpanner* obj, int price) { // 이게 탑이랑 비교하는 문제 같은데.. 잘 모르겠음.
    obj->e = price;
    List* today = NULL;
    today->header = obj;
    if (today->header->e < obj->e) {

    }
}

void StockSpannerFree(StockSpanner* obj) { // 스택을 쌓인걸 초기화 해야함.

}

int main() {
    StockSpanner* k = NULL;
    k->top = -1;
    
}