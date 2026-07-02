#include <stdio.h>
#include <stdlib.h>
void change(int *arr);
int main() {
    int arr_length;
    scanf("%d",&arr_length);
    int *arr=(int*)calloc(arr_length,sizeof(int));
    if (arr==NULL) {
        fprintf(stderr,"calloc1 failed");
        return -1;
    }
    int *pointer=arr;
    for (;pointer<arr+arr_length;pointer++) {
        scanf("%d",pointer);
    }
    change(arr);
    for (pointer=arr;pointer<arr+arr_length;pointer++) {
        printf(" %d",*pointer);
    }
    free(arr);
    return 0;
}
void change(int *arr) {
    int change_length;
    scanf("%d",&change_length);
    int *change_index=(int*)calloc(change_length,sizeof(int));
    if (change_index==NULL) {
        fprintf(stderr,"calloc2 failed");
        free(arr);
        exit(-1);
    }
    int *cpointer=change_index;
    for (;cpointer<change_index+change_length;cpointer++) {
        scanf("%d",cpointer);
    }
    int tmp=*(arr+*change_index);
    for (cpointer--;cpointer>change_index;cpointer--) {
        *(arr+*cpointer)=*(arr+*(cpointer-1));
    }
    *(arr+*(cpointer+1))=tmp;
    free(change_index);
}