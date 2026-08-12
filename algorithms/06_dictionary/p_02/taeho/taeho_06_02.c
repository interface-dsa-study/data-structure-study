#include<stdio.h>
#include <stdlib.h>
int search(int *array,int left,int right,int k) {
    while (left<right-1) {
        int middle=(left+right)/2;
        if (array[middle]==k)return middle;
        if (array[middle]>k) right=middle;
        else left=middle;
    }
    return left;
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