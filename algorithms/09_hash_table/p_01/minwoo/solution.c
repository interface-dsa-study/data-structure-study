#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

typedef struct Hash {
    int key;
    struct Hash* link;
}Hash;

int hx(int key, int M) {
    return key % M;
}

void intsert(Hash** node, int key) {
    Hash* newnode = malloc(sizeof(Hash));
    newnode->key = key;
    newnode->link = NULL;
    if (*node == NULL) {
        *node = newnode;
    }
    else {
        newnode->link = *node;
        *node = newnode;
    }
}

Hash* search(Hash* node, int key) {
    int rank = 1;
    if (node == NULL) {
        printf("0\n");
        return NULL;
    }
    else {
        Hash* temp = node;
        while (temp) {
            if (temp->key == key) {
                printf("%d\n", rank);
                return temp;
            }
            temp = temp->link;
            rank++;
        }
        if (temp == NULL) {
            printf("0\n");
            return NULL;
        }
    }
}

void delete(Hash** startnode, Hash* deletenode) {
    if (deletenode == NULL) {
        return;
    }
    else if ((*startnode) == deletenode) {
        (*startnode) = deletenode->link;
        free(deletenode);
        return;
    }
    else {
        Hash* temp = *startnode;
        while (temp) {
            if (temp->link == deletenode) {
                temp->link = deletenode->link;
                free(deletenode);
                return;
            }
            temp = temp->link;
        }
    }

}

void print(Hash** table, int M) {
    for (int i = 0;i < M;i++) {
        Hash* temp = table[i];
        if (temp != NULL) {
            while (temp) {
                printf(" %d", temp->key);
                temp = temp->link;
            }
        }
    }
}

int main() {
    Hash** Hashtable = NULL;
    Hash* deletenode;
    int N, key, h;
    char ch;

    scanf("%d", &N);

    Hashtable = malloc(N * sizeof(Hash*));

    for (int i = 0;i < N;i++) {
        Hashtable[i] = NULL;
    }

    while (1) {
        scanf(" %c", &ch);
        if (ch == 'e') {
            break;
        }
        else if (ch == 'i') {
            scanf("%d", &key);
            h = hx(key, N);
            intsert(&Hashtable[h], key);
        }
        else if (ch == 's') {
            scanf("%d", &key);
            h = hx(key, N);
            search(Hashtable[h], key);
        }
        else if (ch == 'd') {
            scanf("%d", &key);
            h = hx(key, N);
            deletenode = search(Hashtable[h], key);
            delete(&Hashtable[h], deletenode);
        }
        else if (ch == 'p') {
            print(Hashtable, N);
            printf("\n");
        }
    }

    return 0;
}