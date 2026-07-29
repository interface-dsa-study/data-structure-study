#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    scanf("%d",&n);
    int *array=(int*)malloc(n*sizeof(int));
    if (array==NULL) {
        fprintf(stderr,"array malloc failed");
        exit(1);
    }
    int *pointer=array;
    for (;pointer<array+n;pointer++) {
        scanf("%d",pointer);
    }
    for (int i=n;i>1;i--) {
        int max=array[0];
        int max_index=0;
        for (pointer=array;pointer<array+i;pointer++) {
            if (*pointer>max) {
                max=*pointer;
                max_index=pointer-array;
            }
        }
        int tmp=array[i-1];
        array[i-1]=array[max_index];
        array[max_index]=tmp;
    }
    for (pointer=array;pointer<array+n;pointer++) {
        printf(" %d",*pointer);
    }
    free(array);
}