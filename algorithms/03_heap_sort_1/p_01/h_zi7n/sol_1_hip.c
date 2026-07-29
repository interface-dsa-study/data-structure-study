#include <stdio.h>

typedef int key; // 키 값 정수 이름.
typedef int index; // 인덱스 값 정수 이름.

int Heap[100]; // 힙
int n;  // 사이즈

// i == 1일 때는 루트. i가 1이 아닐 때 비교.
void upHeap(index i) {
    while (i > 1) {
        int parent = i / 2; // 부모 노드의 인덱스.
        if (Heap[i] > Heap[parent]) {
            int tmp = Heap[i];
            Heap[i] = Heap[parent];
            Heap[parent] = tmp;
            i = parent; // 교환 성공시 부모노드 인덱스로 이동.
        }
        else break;
    }
}

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

// 1. 삽입식 힙 생성 함수 구현 -- insertitem(key)
// 인자 : 정수 key. 함수 호출 --> i 입력.
void insertitem(key value) {
    if (n + 1 > 100) {
        return;
    }
    n += 1;
    Heap[n] = value;
    upHeap(n); // 함수 구현 및 사용
    printf("0\n");
    return;
}

int removeMax() {
    key value;
    value = Heap[1];
    Heap[1] = Heap[n];
    n -= 1;
    downHeap(1); // 함수 구현 및 사용
    printf("%d\n", value);
    return value;
}

void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", Heap[i]);
    }
    printf("\n");
}

int main() {
    char order; // 명령어 입력.
    int data; // 키 값 입력.
    while (1) {
        if (scanf(" %c", &order) != 1) break;
        if (order == 'q') break; // 종료조건.
        if (order == 'i') { // insert 명령일 때.
            scanf("%d", &data);
            insertitem(data);
        }
        if (order == 'd') { removeMax(); } // delete 명령일 때.
        if (order == 'p') { printHeap(); } // print 명령일 때.
    }
}