#include<stdio.h>
#include <stdlib.h>
int search(int *array,int left,int right,int k) {
    if (left>=right-1) {
        if (array[left]<=k) return left;
        return 0;
    }
    int middle=(left+right)/2;
    int left_result=search(array,left,middle,k);
    int right_result=search(array,middle,right,k);
    if (right_result!=0) return right_result;
    else return left_result;
}
int main() {
    int n,k;
    scanf("%d %d",&n,&k);
    int *array=malloc(sizeof(*array)*n);
    if (!array) {
        fprintf(stderr,"array malloc failed");
        exit(1);
    }
    for (int *pointer=array;pointer<array+n;) scanf("%d",pointer++);
    int index=search(array,0,n,k);
    printf(" %d",index);
    free(array);
    return 0;
}