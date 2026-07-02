#include <stdio.h>
#include <stdlib.h>
int main() {
    int arr_size;
    scanf("%d",&arr_size);
    int **arr=(int**)calloc(arr_size,sizeof(int*));
    if (arr==NULL) {
        fprintf(stderr,"calloc failed");
        return -1;
    }
    int **arrp=arr;
    int n=1,column_cnt=0;
    for (;arrp<arr+arr_size;arrp++,column_cnt++) {
        *arrp=(int*)calloc(arr_size,sizeof(int));
        if (*arrp==NULL) {
            fprintf(stderr,"calloc failed");
            for (int **q=arr;q<arrp;q++) {
                free(*q);
            }
            free(arr);
            return -1;
        }
        if (column_cnt%2) {
            for (int *p=*arrp+arr_size-1;p>=*arrp;p--) {
                *p=n++;
            }
        }
        else {
            for (int *p=*arrp;p<*arrp+arr_size;p++) {
                *p=n++;
            }
        }
    }
    for (arrp=arr;arrp<arr+arr_size;arrp++) {
        for (int *p=*arrp;p<*arrp+arr_size;p++) {
            printf(" %d",*p);
        }
        printf("\n");
    }
    for (arrp=arr;arrp<arr+arr_size;arrp++) {
        free(*arrp);
    }
    free(arr);
    return 0;
}