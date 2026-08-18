#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

int firsthx(int key, int M) {
    return key % M;
}

int secondhx(int key, int q) {
    return q - (key % q);
}

void intsert(int* hash, int firsth, int secondh, int key, int size) {
    int i = 0;
    for (i = (firsth + i) % size;; i += secondh) {
        if (hash[i] == 0) {
            printf("%d\n", i);
            hash[i] = key;
            break;
        }
        else {
            printf("C");
        }
    }
}

void search(int* hash, int firsth, int secondh, int key, int size) {
    int i = 0;
    for (i = (firsth + i) % size; ; i+=secondh) {
        if (hash[i] == key) {
            printf("%d %d\n", i, key);
            break;
        }
        if (hash[i] == 0) {
            printf("-1\n");
            break;
        }
    }
}

void print(int* hash, int size) {
    for (int i = 0;i < size;i++) {
        printf(" %d", hash[i]);
    }
    printf("\n");
}

int main() {
    int* hashtable = NULL;
    int size, max, k, firsth, secondh, q;
    char ch;

    scanf("%d %d %d", &size, &max, &q);

    hashtable = calloc(size, sizeof(int));

    while (1) {
        scanf(" %c", &ch);
        if (ch == 'e') {
            break;
        }
        else if (ch =='i') {
            scanf("%d", &k);
            firsth = firsthx(k, size);
            secondh = secondhx(k, q);
            intsert(hashtable, firsth, secondh, k, size);
        }
        else if(ch == 's') {
            scanf("%d", &k);
            firsth = firsthx(k, size);
            secondh = secondhx(k, q);
            search(hashtable, firsth, secondh, k, size);
        }
        else {
            print(hashtable, size);
        }
    }

    return 0;
}