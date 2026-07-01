#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct time {
    int h,m,s;
}t;
int main() {
    t a,b;
    scanf("%d %d %d",&a.h,&a.m,&a.s);
    scanf("%d %d %d",&b.h,&b.m,&b.s);
    int as=a.h*3600+a.m*60+a.s;
    int bs=b.h*3600+b.m*60+b.s;
    int ts=bs-as;
    t c;
    c.h=ts/3600;
    ts%=3600;
    c.m=ts/60;
    ts%=60;
    c.s=ts;
    printf("%d %d %d",c.h,c.m,c.s);
    return 0;
}