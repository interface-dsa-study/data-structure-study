#include<stdio.h>
#include<stdlib.h>

int n;
int H[101];


void downHeap(int index, int max){
    int left = 0;
    int right = 0;
    int larger;
    int tmp;
    left = index * 2;
    right = index * 2 + 1;
    while (left <= max){
        larger = left;
        if (right <= max){
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

void printHeap(){
    for (int i = 1; i < n + 1; i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}

int main(){
    scanf("%d", &n);
    //printf("%d\n", n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &H[i]);
    }

    for (int i = n/2; i >= 1; i--){
        downHeap(i);
    }

    printHeap();
    return 0;
}