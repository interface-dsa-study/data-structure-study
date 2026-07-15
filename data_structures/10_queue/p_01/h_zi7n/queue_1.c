#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int size; int *data; int front, rear;
}Queue;

void initQueue(Queue* queue, int N) {
    queue->data = (int*)malloc(sizeof(int));
    queue->front = 0;
    queue->rear = 0;
    queue->size = N;
}

void push(Queue* q, int num) {
    if ((q->rear + 1) % q->size == q->front) {
        printf("overflow");
        for (int i = 0; i < q->size; i++) {
            printf(" %d", q->data[i]);
        }
        printf("\n");
        free(q->data);
        return;
    }
    q->rear = (q->rear + 1) % q->size;
    q->data[q->rear] = num;
}

void pop(Queue *q) {
    if (q->front == q->rear) {
        printf("underflow");
        free(q->data);
        return;
    }
    q->front = (q->front + 1) % q->size;
    q->data[q->front] = 0;
}

void PRINT(Queue *q) {
    for (int i = 0; i < q->size; i++) {
        printf(" %d", q->data[i]);
    }
    printf("\n");
}

int main(void) {
    int queue_size, order;
    Queue queue;
    scanf("%d%d", &queue_size, &order);
    initQueue(&queue, queue_size);
    char orderate;
    for (int i = 0; i < order; i++) {
        scanf(" %c", &orderate);
        if (strcmp(&orderate, "I") == 0) {
            int data; scanf("%d", &data);
            push(&queue, data);
        }
        else if (strcmp(&orderate, "D") == 0) {
            pop(&queue);
        }
        else if (strcmp(&orderate, "P") == 0) {
            PRINT(&queue);
        }
    }
    free(queue.data);
}