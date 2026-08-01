#include<stdio.h>
#include<stdlib.h>

int H[1000];
int n = 0;

void upHeap(int index){
    int tmp;
    while (index != 1){
        if (H[index/2] < H[index]){
            tmp = H[index];
            H[index] = H[index/2];
            H[index/2] = tmp;
        }
        index /= 2;
    }
}

void insertItem(int key){
    n = n + 1;
    H[n] = key;
    upHeap(n);
    printf("%d\n", 0);
}

void downHeap(int index){
    int left = 0;
    int right = 0;
    int larger;
    int tmp;
    left = index * 2;
    right = index * 2 + 1;
    while (left <= n){
        larger = left;
        if (right <= n){
            larger = H[left] > H[right] ? left : right;
        }
        if (H[larger] < H[index]){
            return;
        }
        tmp = H[larger];
        H[larger] = H[index];
        H[index] = tmp;
        index = larger;
        left = index * 2;
        right = index * 2 + 1;
    }
}

int removeMax(){
    int key = H[1];
    H[1] = H[n];
    n = n - 1;
    downHeap(1);
    return key;
}

void printHeap(){
    for (int i = 1; i < n + 1; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}

int main(){
    char mode;
    int key;
    while (1){
        scanf(" %c", &mode);
        //printf("%c", mode);
        if (mode == 'i'){
            scanf("%d", &key);
            getchar();
            insertItem(key);
        }
        else if (mode == 'd'){
            printf("%d\n", removeMax());
        }
        else if (mode == 'p'){
            printHeap();
        }
        else if (mode == 'q'){
            break;
        }
    }
    return 0;
}