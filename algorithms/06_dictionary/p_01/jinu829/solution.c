#include<stdio.h>
#include<stdlib.h>

int binarySearch(int k, int *arr, int first, int last){
    if (first > last){
        return last;
    }
    int mid;
    mid = (first + last) / 2;
    //printf("%d\n", mid);
    if (arr[mid] == k)
        return mid;
    else if (arr[mid] < k){
        return binarySearch(k, arr, mid + 1, last);
    }
    else if (arr[mid] > k){
        return binarySearch(k, arr, first, mid - 1);
    }
}

int main(){
    int n;
    int *arr;
    int k;
    scanf("%d", &n);
    scanf("%d", &k);
    arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    printf(" %d", binarySearch(k, arr, 0, n-1));
    return 0;
}