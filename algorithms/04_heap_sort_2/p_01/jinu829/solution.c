#include<stdio.h>
#include<stdlib.h>

int H[1000];
int n = 0;

void downHeap(int index, int max){
    int left = 0;
    int right = 0;
    int larger;
    int tmp;
    while (left <= max){
        left = index * 2;
        right = index * 2 + 1;
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
    }
}

int main(){
    int tmp;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &H[i]);
    }

    for (int i = n/2; i >= 1; i--){
        downHeap(i, n);
    }

    for (int i = 1; i <= n; i++){
        printf(" %d", H[i]);
    }

    for (int i = n; i >= 2; i--){
        tmp = H[i];
        H[i] = H[1];
        H[1] = tmp;
        downHeap(1, i-1);
    }

    for (int i = 1; i <= n; i++){
        printf(" %d", H[i]);
    }
    return 0;
}