#include <stdio.h>
#include <stdlib.h>
int main() {
    int height,width;
    scanf("%d %d",&height,&width);
    int heightb=height;
    int widthr=width;
    int heightt=0;
    int widthl=0;
    int number=1;

    int **arr=(int**)calloc(height,sizeof(int*));
    if (arr==NULL) {
        fprintf(stderr,"calloc failed");
        return -1;
    }
    int **row_pointer=arr;
    for (;row_pointer<arr+height;row_pointer++) {
        *row_pointer=(int*)calloc(width,sizeof(int));
        if (*row_pointer==NULL) {
            fprintf(stderr,"calloc failed");
            for (int **p=arr;p<row_pointer;p++) {
                free(*p);
            }
            free(arr); 
        }
    }
    row_pointer=arr;
    int *column_pointer;
    while (number<=height*width) {
        for (column_pointer=*row_pointer+widthl;column_pointer<*row_pointer+widthr;column_pointer++) {
            *column_pointer=number++;
        }
        if (number>height*width)break;
        heightt++;
        for (row_pointer=arr+heightt;row_pointer<arr+heightb;row_pointer++) {
            column_pointer=*row_pointer+widthr-1;
            *column_pointer=number++;
        }
        if (number>height*width)break;
        widthr--;
        row_pointer--;
        for (column_pointer=*row_pointer+widthr-1;column_pointer>=*row_pointer+widthl;column_pointer--) {
            *column_pointer=number++;
        }
        if (number>height*width)break;
        heightb--;
        for (row_pointer=arr+heightb-1;row_pointer>=arr+heightt;row_pointer--) {
            column_pointer=*row_pointer+widthl;
            *column_pointer=number++;
        }
        widthl++;
        row_pointer++;
    }
    for (row_pointer=arr;row_pointer<arr+height;row_pointer++) {
        for (column_pointer=*row_pointer;column_pointer<*row_pointer+width;column_pointer++) {
            printf(" %2d",*column_pointer);
        }
        printf("\n");
    }
    for (row_pointer=arr;row_pointer<arr+height;row_pointer++) {
        free(*row_pointer);
    }
    free(arr);
    return 0;
}