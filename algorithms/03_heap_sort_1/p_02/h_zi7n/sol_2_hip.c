#include <stdio.h>

typedef int key; // 키 값 정수 이름.
typedef int index; // 인덱스 값 정수 이름.

int Heap[100]; // 힙
int n = 0;  // 사이즈

// i == n일 때는 리프노드. i가 n이 아닐 때 비교.
void downHeap(index i) {
    while (i < n / 2) {
        int left = i * 2;
        int right = i * 2 + 1;
        int higher_leap_node = left;
        if (right <= n && Heap[right] > Heap[left]) {
            higher_leap_node = right;
        }
        if (Heap[i] < Heap[higher_leap_node]) {
            int tmp = Heap[i];
            Heap[i] = Heap[higher_leap_node];
            Heap[higher_leap_node] = tmp;
            i = higher_leap_node;
        }
        else break;
    }
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", Heap[i]);
    }
    printf("\n");
}

void rBuildHeap(index i) {
    if (i > n) return;
    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
    return;
}

int main() {
    int key_N; scanf("%d", &key_N);
    key value;
    for (int i = 0; i < key_N; i++) {
        scanf("%d", &value);
        Heap[i] = value;
    }
    rBuildHeap(1);
    printHeap(key_N);
    return 0;
}