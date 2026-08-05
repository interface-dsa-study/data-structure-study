#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int *arrcopy, int start, int mid, int end)
{
    int i = start;
    int j = mid;
    int count = 0;
    while (i < mid && j < end)
    {
        if (arr[i] > arr[j])
        {
            arrcopy[count] = arr[j];
            j += 1;
        }
        else if (arr[i] < arr[j])
        {
            arrcopy[count] = arr[i];
            i += 1;
        }
        else
        {
            arrcopy[count] = arr[i];
            i += 1;
            j += 1;
        }
        count++;
    }
    while (i < mid)
    {
        arrcopy[count] = arr[i];
        i += 1;
        count++;
    }
    while (j < end)
    {
        arrcopy[count] = arr[j];
        j += 1;
        count++;
    }
}

void mergeSort(int *arr, int *arrcopy, int start, int end)
{
    printf("%d\n", arr[0]);
    if (end > start)
    {
        int mid = (start + end) / 2;
        mergeSort(arr, arrcopy, start, mid);
        mergeSort(arr, arrcopy, mid, end);
        merge(arr, arrcopy, start, mid, end);
    }
}

int main()
{
    int n;
    int *arr;
    int *arrcopy;

    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int));
    arrcopy = (int *)malloc(sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    mergeSort(arr, arrcopy, 0, n);

    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    return 0;
}