#include <stdio.h>
#include <stdlib.h>

int n;
int rangearr[2];

int findPivot(int *arr, int l, int r)
{
    return arr[(l + r) / 2];
}

void inPlacePartition(int *arr, int l, int r, int pivot)
{
    int *LT = (int *)malloc(sizeof(int) * n);
    int *EQ = (int *)malloc(sizeof(int) * n);
    int *GT = (int *)malloc(sizeof(int) * n);

    int LTline = 0;
    int GTline = 0;
    int EQline = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < pivot)
        {
            LT[LTline++] = arr[i];
        }
        else if (arr[i] > pivot)
        {
            GT[GTline++] = arr[i];
        }
        else
        {
            EQ[EQline++] = arr[i];
        }
    }

    for (int i = 0; i < LTline; i++)
    {
        arr[i] = LT[i];
    }
    for (int i = 0; i < EQline; i++)
    {
        arr[LTline + i] = EQ[i];
    }
    for (int i = 0; i < GTline; i++)
    {
        arr[LTline + EQline + i] = GT[i];
    }

    /*for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");*/

    rangearr[0] = LTline;
    rangearr[1] = LTline + EQline - 1;

    // printf("%d %d\n", rangearr[0], rangearr[1]);
}

void inPlaceQuickSort(int *arr, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int pivot = findPivot(arr, l, r);
    inPlacePartition(arr, l, r, pivot);
    inPlaceQuickSort(arr, l, rangearr[0] - 1);
    inPlaceQuickSort(arr, rangearr[1] + 1, r);
}

int main()
{
    int *arr;
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    inPlaceQuickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }

    return 0;
}