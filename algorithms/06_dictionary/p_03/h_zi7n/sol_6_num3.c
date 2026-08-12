#include <stdio.h>
#include <stdlib.h>

int okeydokeyYo(char *array, int a, int b, int i, int limit) {
    int m = (a + b) / 2;
    if (i == limit - 1) {
        if (*(array + i) == 'Y') return m + 1;
        else return m;
    }
    if (*(array + i) == 'Y') return okeydokeyYo(array, m + 1, b, i + 1, limit);
    if (*(array + i) == 'N') return okeydokeyYo(array, a, m, i + 1, limit);
}

int main(void) {
    int a, b, k, YN_cnt, i = 0; scanf("%d%d%d", &a, &b, &YN_cnt);
    char *array = (char*)malloc(sizeof(char) * YN_cnt);
    for (int i = 0; i < YN_cnt;i++) scanf(" %c", (array + i));
    k = okeydokeyYo(array, a, b, i, YN_cnt);
    printf("%d", k);
    free(array);
}