#include <stdio.h>
#include <stdlib.h>
void merge(int* array,int *sorted_array,int left,int middle,int right) {
    int *left_pointer=array+left;
    int *right_pointer=array+middle;
    int *sorted_pointer=sorted_array;
    while (left_pointer<array+middle&&right_pointer<array+right) {
        if (*left_pointer<*right_pointer) *sorted_pointer++=*left_pointer++;
        else if (*left_pointer>*right_pointer) *sorted_pointer++=*right_pointer++;
        else if (*left_pointer==*right_pointer) {
            *sorted_pointer++=*left_pointer++;
            *sorted_pointer++=*right_pointer++;
        }
    }
    while (left_pointer<array+middle) *sorted_pointer++=*left_pointer++;
    while (right_pointer<array+right) *sorted_pointer++=*right_pointer++;
    int *array_pointer=array+left;
    sorted_pointer=sorted_array;
    while (array_pointer<array+right) *array_pointer++=*sorted_pointer++;
}
void merge_sort(int *array,int *sorted_array,int left,int right) {//여기서 재귀를 써야 하는데...
    if (left+1>=right) {
        return;
    }
    int middle=(left+right+1)/2;
    merge_sort(array,sorted_array,left,middle);
    merge_sort(array,sorted_array,middle,right);
    merge(array,sorted_array,left,middle,right);
}
int main() {
    int size;
    scanf("%d",&size);
    int *array=(int*)malloc(size*sizeof(int));
    if (!array) {
        fprintf(stderr,"array malloc failed");
        exit(1);
    }
    for (int *pointer=array;pointer<array+size;pointer++) scanf("%d",pointer);
    int *sorted_array=(int*)malloc(size*sizeof(int));
    if (!sorted_array) {
        fprintf(stderr,"sorted array malloc failed");
        exit(1);
    }
    merge_sort(array,sorted_array,0,size);

    for (int *pointer=sorted_array;pointer<sorted_array+size;pointer++) {
        printf(" %d",*pointer);
    }
    free(array);
    free(sorted_array);
    return 0;
}