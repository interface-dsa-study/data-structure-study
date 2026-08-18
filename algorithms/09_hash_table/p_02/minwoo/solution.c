#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

int hx(int key, int M) {
    return key % M;
}

void search(int* hash, int index, int size, int key) {
    int i;
    for (i = 0;;i++) {
        if (hash[(index + i) % size] == key) {
            printf("%d %d\n", (index + i) % size, key);
            break;
        }
        if (hash[(index + i) % size] == 0) {
            printf("-1\n");
            break;
        }
    }
}

void insert(int* hash, int index, int size, int key) {
    int i;
    for (i = 0;;i++) {
        if (hash[(index+i)%size] == 0) {
            hash[(index + i) % size] = key;
            printf("%d\n", (index + i) % size);
            break;
        }
        else {
            printf("C");
        }
    }
}

int main() {
    int* hashtable = NULL;
    int size, max, k, h;
    char ch;

    scanf("%d %d", &size, &max);

    hashtable = calloc(size, sizeof(int));

    while (1) {
        scanf(" %c", &ch);
        if (ch == 'e') {
            break;
        }
        else if (ch =='i') {
            scanf("%d", &k);
            h = hx(k, size);
            insert(hashtable, h, size, k);
        }
        else {
            scanf("%d", &k);
            h = hx(k, size);
            search(hashtable, h, size, k);
        }
    }

    return 0;
}