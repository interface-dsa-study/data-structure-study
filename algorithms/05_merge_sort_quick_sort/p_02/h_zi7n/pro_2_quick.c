#include <stdio.h>
#include <stdlib.h>

int findPivot(int l, int r) {
    // 공식 작동 원리: 랜덤으로 하나 뽑고, 0부터 9까지면 10으로 나누어서 확정시키기.
    int pivot_index = l + rand() % (r - l + 1); // Ai한테 공식 물어봄.
    return pivot_index;
}

void quickSort(int array[], int l, int r) {
    if (l >= r) return; // 종료조건
    int pivot_index = findPivot(l, r);
    // 맨 처음에 맨 오른쪽 원소와 피벗 원소와 위치 교환.
    int temp = array[pivot_index];
    array[pivot_index] = array[r];
    array[r] = temp;
    // 처음에 피벗 인덱스랑 r위치의 원소를 교환했으므로, 피벗 인덱스를 바꾸어 줘야됨.
    pivot_index = r;
    // 처음 피벗 위치를 맨 뒤로 옮겼으니, 피벗이라는 변수로 비교 해야함.
    int Pivot = array[r];
    int swapped = l - 1;
    for (int swapping = l; swapping < r; swapping++) {
        if (array[pivot_index] > array[swapping]) { // 기준점보다 원소가 작으면?
            swapped++;
            int tmp = array[swapped];
            array[swapped] = array[swapping];
            array[swapping] = tmp;
        }
        else { // 기준점보다 크거나 같으면?
            continue;
        }
    }
    // 마지막에 피벗 인덱스 위치와, 바꾼 위치 + 1 위치까지 스왑 해주어야 구간이 나뉨.
    int tmp = array[swapped + 1];
    array[swapped + 1] = array[pivot_index];
    array[pivot_index] = tmp;
    // 피벗 기준, 더 작은 원소의 끝부분과 큰 원소의 시작점 새로 설정
    int LT_last = swapped, GT_start = swapped + 2;
    // 1. 왼쪽 재귀.
    quickSort(array, l, LT_last);
    // 2. 오른쪽 재귀.
    quickSort(array, GT_start, r);
}

int main(void) {
    int size; scanf("%d", &size);
    int* array = malloc(sizeof(*array)*size);
    for (int i = 0; i < size; i++) scanf("%d", &array[i]);
    quickSort(array,0,size - 1);
    for (int i = 0; i < size; i++) {
        printf(" %d", array[i]);
    }
    free(array);
}