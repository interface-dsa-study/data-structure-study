#include <stdio.h>
#include <stdlib.h>
void swap(int *a,int *b) {
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
int find_pivot(int left,int right) {
    return rand()%(right-left)+left;
}
void quick_sort(int *array,int left,int right) {
    if (left>=right) return;
    int pivot=find_pivot(left,right);
    swap(array+pivot,array+right-1);
    pivot=right-1;
    int index_a=left-1;
    int index_b=left;
    while (index_b<right-1) {
        if (array[index_b]<array[pivot]) {
            index_a++;
            swap(array+index_a,array+index_b);
        }
        index_b++;
    }
    index_a++;
    swap(array+index_a,array+index_b);
    quick_sort(array,left,index_a);
    quick_sort(array,index_a,right);
}
int main() {
    int size;
    scanf("%d",&size);
    int *array=malloc(sizeof(*array)*size);
    if (!array) {
        fprintf(stderr,"array malloc failed");
        exit(1);
    }
    for (int *pointer=array;pointer<array+size;pointer++) scanf("%d",pointer);
    quick_sort(array,0,size);
    for (int *pointer=array;pointer<array+size;pointer++) printf(" %d",*pointer);
    free(array);
    return 0;
}