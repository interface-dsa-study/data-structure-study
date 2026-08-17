#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char ch;
    int a, b, N, i, m, k;

    scanf("%d %d %d", &a, &b, &N);

    for (i = 0;i < N;i++) {
        scanf(" %c", &ch);
        m = (a + b) / 2;
        if (ch == 'Y') {
            a = m + 1;
        }
        else {
            b = m;
        }
        if (a == b) {
            k = a;
            break;
        }
    }

    printf("%d", k);

    return 0;
}