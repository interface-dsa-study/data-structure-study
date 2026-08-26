

typedef struct
{
    int A[10 ^ 4]; // 그 전에 가지고 있던 최대 값의 인덱스값
    int x[10 ^ 4]; // 그 전에 가지고 있던 최대 값
    int n;         // 인덱스값
    int nx;        // X, I배열의 인덱스값.
} StockSpanner;

StockSpanner *stockSpannerCreate()
{
    StockSpanner s;
    s.n = -1;
    s.nx = -1;
    return &s;
}

int stockSpannerNext(StockSpanner *obj, int price)
{ // 기간을 반환하는 함수
    while (obj->x[obj->nx] < price && obj->nx >= 0)
        {
            obj->nx = obj->nx - 1;
        }
        if (obj->nx == 0)
        {
            obj->n += 1;
            return obj->n;
        }
        else
        {
            return obj.
        }
    
}

void stockSpannerFree(StockSpanner *obj)
{ // 공간 해제
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);

 * stockSpannerFree(obj);
*/