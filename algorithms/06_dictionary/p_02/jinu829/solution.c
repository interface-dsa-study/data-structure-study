#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, k;
    int *arr;
    int first, last;
    int mid;
    int resultindex;
    scanf("%d %d", &n, &k);
    arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    first = 0;
    last = n-1;
    while (first <= last){
        mid = (first + last) / 2;
        if (arr[mid] == k){
            resultindex = mid; 
            break;
        }
        else if (arr[mid] > k){
            last = mid-1;
        }
        else if (arr[mid] < k){
            first = mid + 1;
        }
    }
    if (first > last){
        resultindex = first;
    }
    printf(" %d", resultindex);
    free(arr);
    return 0;
}