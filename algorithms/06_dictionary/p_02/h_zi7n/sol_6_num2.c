#include <stdio.h>
#include <stdlib.h>

typedef int key;

int main(void) {
    int N; key limit, value, search = 0; scanf("%d%d", &N, &limit); int* array;
    array = (int*)malloc(sizeof(int) * N);
    if (!array) {
        fprintf(stderr,"array malloc failed");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &value);
        *(array + i) = value;
    }
    for (int i = 0; i < N; i++) {
        if (*(array + i) >= limit || (array + i) == NULL) {search = i; break;}
        else {search = N;}
    }
    printf(" %d", search);
    free(array);
}