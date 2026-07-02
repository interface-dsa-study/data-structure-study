#include <stdio.h>
#include <stdlib.h>
void flip(int *a,int range);
int main() {
    int arr_length;
    scanf("%d",&arr_length);
    int *arr=(int*)calloc(arr_length,sizeof(int));
    int *arr_pointer=arr;
    for (;arr_pointer<arr_pointer+arr_length;arr_pointer++) {
        scanf("%d",arr_pointer);
    }
    int flip_time;
    scanf("%d",&flip_time);
    for (int i=0;i<flip_time;i++) {
        int a,b;
        scanf("%d %d",&a,&b);
        flip(arr+a,b-a);
    }
}
void flip(int *a,int range) {
    for (int *p=a+range;a<a+(range+1)/2;a++) {

    }
}