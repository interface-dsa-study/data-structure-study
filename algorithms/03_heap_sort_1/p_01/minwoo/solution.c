#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int ArrayH[100];
int size = 0;

void upHeap(int index) {
    int temp, i = 0;
    if (index > 1) {
        for (i = (index / 2) ; i > 0; ) {
            if (ArrayH[i] < ArrayH[index]) {
                temp = ArrayH[i];
                ArrayH[i] = ArrayH[index];
                ArrayH[index] = temp;
                index = i;
            }
            if (index == 0) {
                break;
            }
            i /= 2;
        }
    }
    return;
}

void insertItem(int key) {
    size++;
    ArrayH[size] = key;
    upHeap(size);
    printf("0\n");
    return;
}

void downHeap(int index) {
    int temp;
    if (index > 1) {
        for (int i = 1;i <= index;) {
            if (ArrayH[i * 2] > ArrayH[(i * 2) + 1]) {
                if (ArrayH[i] < ArrayH[i * 2]) {
                    temp = ArrayH[i];
                    ArrayH[i] = ArrayH[i * 2];
                    ArrayH[i * 2] = temp;
                    i = i * 2;
                }
            }
            else if(ArrayH[i * 2] < ArrayH[(i * 2) + 1]){
                if (ArrayH[i] < ArrayH[(i * 2) + 1]) {
                    temp = ArrayH[i];
                    ArrayH[i] = ArrayH[(i * 2) + 1];
                    ArrayH[(i * 2) + 1] = temp;
                    i = (i * 2) + 1;
                }
            }
            i *= 2;
        }
    }
}

int removeMax() {
    int key;
    key = ArrayH[1];
    ArrayH[1] = ArrayH[size];
    size--;
    downHeap(size);
    return key;
}


void printHeap() {
    int i;
    for (i = 1;i <= size;i++) {
        printf(" %d", ArrayH[i]);
    }

}



int main() {
    int key;
    char massage;

    while (1) {
        scanf(" %c", &massage);

        if (massage == 'q') {
            break;
        }
        else if (massage == 'i') {
            scanf("%d", &key);
            insertItem(key);
        }
        else if (massage == 'd') {
            key = removeMax();
            printf("%d\n", key);
        }
        else {
            printHeap();
            printf("\n");
        }

    }

    return 0;
}