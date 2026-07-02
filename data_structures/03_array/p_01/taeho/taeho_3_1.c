#include <stdio.h>
#include <stdlib.h>
void flip(int *arr);
int main() {
    int arr_length;
    scanf("%d",&arr_length);
    int *arr=(int*)calloc(arr_length,sizeof(int));
    if (arr==NULL) {
        printf("calloc failed");
        return -1;
    }
    int *arr_pointer=arr;
    for (;arr_pointer<arr+arr_length;arr_pointer++) {
        scanf("%d",arr_pointer);
    }
    int flip_time;
    scanf("%d",&flip_time);
    for (int i=0;i<flip_time;i++) {
        flip(arr);
    }
    for (arr_pointer=arr;arr_pointer<arr+arr_length;arr_pointer++) {
        printf(" %d",*arr_pointer);
    }
    free(arr);
    return 0;
}
void flip(int *arr) {
    int a,b;
    scanf("%d %d",&a,&b);
    int range=b-a;
    for (int *p=arr+a,*q=arr+b;p<arr+(a+b+1)/2;p++,q--) {
        int tmp=*p;
        *p=*q;
        *q=tmp;
    }
}