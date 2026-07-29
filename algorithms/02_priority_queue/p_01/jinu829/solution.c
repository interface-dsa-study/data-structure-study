#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int *inplacehamsu(int *arr, int n)
{
    if (n == 1)
    {
        return arr;
    }
    int max = 0;
    int maxindex;
    int tmp;
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
            maxindex = i;
        }
    }
    tmp = arr[n - 1];
    arr[n - 1] = arr[maxindex];
    arr[maxindex] = tmp;
    return inplacehamsu(arr, n - 1);
}

int main()
{
    int n;
    int *arr = NULL;
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int));
    if (arr == NULL)
    {
        printf("잘못된 공간에 접속하였습니다.");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    arr = inplacehamsu(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    free(arr);
    return 0;
}