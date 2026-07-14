#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct queue {
    int* q;
    int front;
    int rear;
}queue;

void init(queue* que, int N) {
    que->q = (int*)malloc(N * sizeof(int));
    que->front = 0;
    que->rear = 0;
    for (int i = 0;i < N;i++) {
        que->q[i] = 0;
    }
}

int Insert(queue* que, int N, int size) {
    if ((que->rear + 1) % size == que->front) {
        printf("overflow");
        for (int i = 0; i < size;i++) {
            printf(" %d", que->q[i]);
        }
        return 0;
    }
    que->rear++;
    que->rear = (que->rear + size) % size;
    que->q[que->rear] = N;
    return 1;
}

int Delete(queue* que, int size) {
    if (que->rear  == que->front) {
        printf("underflow");
        return 0;
    }
    que->front++;
    que->front = (que->front + size) % size;
    que->q[que->front] = 0;
    return 1;
}

void Print(queue que, int size) {
    for (int i = 0;i < size;i++) {
        printf(" %d", que.q[i]);
    }
    printf("\n");
}

int main() {
    queue qu;
    int N, i, num, size, a;
    char ch;

    scanf("%d", &size);

    init(&qu, size);

    scanf("%d", &N);

    for (i = 0;i < N;i++) {
        scanf(" %c", &ch);
        if (ch == 'I') {
            scanf("%d", &num);
            a = Insert(&qu, num, size);
            if (a == 0) {
                break;
            }
        }
        else if (ch == 'D') {
            a = Delete(&qu, size);
            if (a == 0) {
                break;
            }
        }
        else {
            Print(qu, size);
        }
    }

    free(qu.q);

    return 0;
}