#include <stdio.h>
#include<stdlib.h>
int max(int*,int);
int main() {
    int arr_length;
    scanf("%d",&arr_length);
    int *arr=(int*)calloc(arr_length,sizeof(int));
    if (arr==NULL) {
        printf("calloc failed");
        return -1;
    }
    for (int *arr_pointer=arr;arr_pointer<arr+arr_length;arr_pointer++) {
        scanf("%d",arr_pointer);
    }
    int max_value=max(arr,arr_length);
    printf("%d",max_value);
    free(arr);
    return 0;
}
int max(int *arr,int arr_size) {///this was quite hard
    if (arr_size==1)return *arr;
    int max_value=max(arr,arr_size-1);
    if (max_value>*(arr+arr_size-1))return max_value;
    else return *(arr+arr_size-1);
}
