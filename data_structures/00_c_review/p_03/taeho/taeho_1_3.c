#include <stdio.h>
#include <stdlib.h>
void swap(int *p,int *q);
int main() {
    int n;
    scanf("%d",&n);
    int *arr=(int*)malloc(n*sizeof(int));
    if (arr==NULL) {
        printf("malloc failed");
        return -1;
    }
    int *p=arr;
    for (;p<arr+n;p++) {
        scanf("%d",p);
    }
    int a,b;
    scanf("%d %d",&a,&b);
    swap(arr+a,arr+b);
    for (p=arr;p<arr+n;p++) {
        printf(" %d",*p);
    }
    free(arr);
    return 0;
}
void swap(int *p,int *q) {
    int tmp=*p;
    *p=*q;
    *q=tmp;
}