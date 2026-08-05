#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int *arrcopy, int start, int mid, int end)
{
    printf("%d %d %d\n", start, mid, end);
    int i = start;
    int j = mid + 1;
    int count = start;
    while (i <= mid && j <= end)
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
    while (i <= mid)
    {
        arrcopy[count] = arr[i];
        i += 1;
        count++;
    }
    while (j <= end)
    {
        arrcopy[count] = arr[j];
        j += 1;
        count++;
    }
    for (int i = start; i <= end; i++)
    {
        arr[i] = arrcopy[i];
    }
    for (int i = start; i <= end; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    return;
}

void mergeSort(int *arr, int *arrcopy, int start, int end)
{
    // printf("%d\n", arr[start]);
    if (end > start)
    {
        int mid = (start + end) / 2;
        // printf("%d %d %d\n", start, end, mid);
        mergeSort(arr, arrcopy, start, mid);
        mergeSort(arr, arrcopy, mid + 1, end);
        merge(arr, arrcopy, start, mid, end);
    }
    return;
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
        printf("%d\n", arr[i]);
    }

    mergeSort(arr, arrcopy, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    return 0;
}