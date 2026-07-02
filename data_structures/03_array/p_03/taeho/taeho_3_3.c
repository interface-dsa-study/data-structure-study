#include <stdio.h>
#include <stdlib.h>
int main() {
    int arr_size;
    scanf("%d",&arr_size);
    int **height=(int**)calloc(arr_size,sizeof(int*));
    if (height==NULL) {
        fprintf(stderr,"calloc failed");
        return -1;
    }
    int **arr=height;
    int **pointer_height=arr;
    int n=1;
    for (;pointer_height<arr+arr_size;pointer_height++) {
        int *arr=(int*)calloc(arr_size,sizeof(int));
        *pointer_height=arr;
        if ((arr-pointer_height)%2) {
            for (int *p=*pointer_height+n-1;p>=*pointer_height;p--) {
                *p=n++;
            }
        }
        else {
            for (int *p=*pointer_height;p<*pointer_height+n;p++) {
                *p=n++;
            }
        }
    }
    for ()
}