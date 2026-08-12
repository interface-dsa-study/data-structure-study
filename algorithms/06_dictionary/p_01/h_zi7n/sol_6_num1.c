#include <stdio.h>
#include <stdlib.h>

typedef int key;

int BST(int *array, key limit, int i) {
    if (*(array + i) > limit || (array+i) == NULL) return i - 1;
    else {
        i++;
        BST(array, limit, i);
    }
}

int main(void) {
    int N; key limit, value; scanf("%d%d", &N, &limit); int* array;
    array = (int*)malloc(sizeof(int) * N);
    if (!array) {
        fprintf(stderr,"array malloc failed");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &value);
        *(array + i) = value;
    }
    int i = 0;
    printf(" %d", BST(array, limit, i));
    free(array);
}