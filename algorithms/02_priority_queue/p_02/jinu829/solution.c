#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void inplacehamsu(int *arr, int n)//삽입 정렬을 수행하는 함수
{
    int tmp;
    //두 번째 원소부터 그 전에 앞에서 정렬된 원소들이랑 비교하며 내가 어느 위치에 들어가야 할지 찾아보기.
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            //첫 번째 원소부터 한칸씩 보며 만약 앞에 정렬된 원소 중 더 값이 큰 원소가 있다면 그 원소 앞에 위치될 수 있도록 함.
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