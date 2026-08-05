#include <stdio.h>
#include <stdlib.h>
int* merge(int* array,int *sorted_array,int left,int middle,int right) {//left랑 right랑 인덱스로 써서 해야 함
    int *left_pointer=array+left;
    int *right_pointer=array+middle+1;
    int *sorted_pointer=sorted_array;
    while (left_pointer<array+middle&&right_pointer<array+right) {
        if (*left_pointer<*right_pointer) *sorted_pointer++=*left_pointer++;
        else if (*left_pointer>*right_pointer) *sorted_pointer++=*right_pointer++;
        else if (*left_pointer==*right_pointer) {
            *sorted_pointer++=*right_pointer++;
            *sorted_pointer++=*left_pointer++;
        }
    }
    while (left_pointer<array+middle) *sorted_pointer++=*left_pointer++;
    while (right_pointer<array+right) *sorted_pointer++=*right_pointer++;
    return sorted_array;
}
int* merge_sort(int *array,int *sorted_array,int size) {//여기서 재귀를 써야 하는데...
    int left=0;
    int middle=size/2;
    int right=size;
    sorted_array=merge_sort(array+middle,sorted_array+middle,size/2)
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
    array=merge_sort(array,sorted_array,size);

    for (int *pointer=array;pointer<array+size;pointer++) {
        printf(" %d",*pointer);
    }
    free(array);
    return 0;
}