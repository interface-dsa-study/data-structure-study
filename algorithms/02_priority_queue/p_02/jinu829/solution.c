#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void inplacehamsu(int *arr, int n)
{
    int tmp;
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            if (arr[i] < arr[j]){
                tmp = arr[i];
                for (int k = i - 1; k >= j; k--){
                    arr[k + 1] = arr[k];
                }
                arr[j] = tmp;
                break;
            }
        }
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