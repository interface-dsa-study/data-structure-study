#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int *inplacehamsu(int *arr, int index, int n)
{
    if (n == 1)
    {
        return arr;
    }
    int count = 0;
    int tmp;
    for (int i = 0; i < index; i++)
    {
        if (arr[index] > arr[i])
        {
            count++;
        }
    }
    tmp = arr[index];
    for (int i = index; i > count; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[count] = tmp;
    return inplacehamsu(arr, index + 1, n - 1);
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
    arr = inplacehamsu(arr, 1, n);
    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    free(arr);
    return 0;
}