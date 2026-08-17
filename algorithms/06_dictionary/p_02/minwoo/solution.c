#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

void BST(int* Array, int left, int right, int key) {
    int k;
    int max = 0;
    while (1) {
        if (left > right) {
            if (Array[left]) {
                printf(" %d", left);
            }
            else {
                printf("%d", right);
            }
            break;
        }
        int mid = (left + right) / 2;
        if (Array[mid] == key) {
            printf(" %d", mid);
            return;
        }
        else if (Array[mid] > key) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }

    }
}

int main() {
    int* Arraylist = NULL;
    int N, key;

    scanf("%d %d", &N, &key);

    Arraylist = malloc(N * sizeof(int));

    for (int i = 0;i < N;i++) {
        scanf("%d", &Arraylist[i]);
    }

    BST(Arraylist, 0, N, key);

    free(Arraylist);

    return 0;
}