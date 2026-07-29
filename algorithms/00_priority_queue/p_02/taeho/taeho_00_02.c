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
    for (pointer=array+1;pointer<array+n;pointer++) {
        for (int *sort_pointer=pointer-1;sort_pointer>=array;sort_pointer--) {
            if (*sort_pointer>*(sort_pointer+1)) {
                int tmp=*sort_pointer;
                *sort_pointer=*(sort_pointer+1);
                *(sort_pointer+1)=tmp;
            }
        }
    }
    for (pointer=array;pointer<array+n;pointer++) {
        printf(" %d",*pointer);
    }
    free(array);
}