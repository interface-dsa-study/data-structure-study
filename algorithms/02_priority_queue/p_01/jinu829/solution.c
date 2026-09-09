#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void inplacehamsu(int *arr, int n)
{
    int max;
    int maxindex;
    int tmp;
    for (int i = n-1; i > 0; i--){
        max = 0;
        maxindex = 0;
        for (int j = 0; j <= i; j++){
            if (arr[j] > max){
                max = arr[j];
                maxindex = j;
            }
        }
        tmp = arr[i];
        arr[i] = arr[maxindex];
        arr[maxindex] = tmp;
    }
}

int main()
{
    int n;
    int *arr = NULL;
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL)
    {
        printf("잘못된 공간에 접속하였습니다.");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    inplacehamsu(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    free(arr);
    return 0;
}