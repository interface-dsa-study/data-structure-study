#include <stdio.h>
#include <stdlib.h>
int main() {
    int height,width;
    scanf("%d %d",&height,&width);
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
    int *column_pointer=*row_pointer;
    for (int row=0,column=0;number<=height*width;) {
        row_pointer=arr+row;
        for (int c=column;c>=0&&row_pointer<arr+height;row_pointer++,c--) {
            *(*row_pointer+c)=number++;
        }
        if (column<width-1)column++;
        else row++;
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