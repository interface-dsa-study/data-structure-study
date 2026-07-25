#include <stdio.h>
#include <stdlib.h>
typedef struct queue {
    int size;
    int *queue;
    int front;
    int rear;
}Queue;
void queue_print(Queue *queue) {
    for (int *pointer=queue->queue;pointer<queue->queue+queue->size;pointer++) {
        printf(" %d",*pointer);
    }
    printf("\n");
}
void enqueue(Queue *queue,int value) {
    if (queue->front==queue->rear+1) {
        printf("overflow");
        queue_print(queue);
        exit(1);
    }
    queue->rear++;
    if (queue->rear==queue->size)queue->rear=0;
    *(queue->queue+queue->rear)=value;
}
void dequeue(Queue *queue) {
    if (queue->front==queue->rear) {
        printf("underflow");
        exit(1);
    }
    queue->front++;
    if (queue->front==queue->size)queue->front=0;
    *(queue->queue+queue->front)=0;
}
int main() {
    setbuf(stdout,NULL);
    Queue queue;
    scanf("%d",&queue.size);
    queue.queue=(int*)calloc(queue.size,sizeof(int));
    if (queue.queue==NULL) {
        fprintf(stderr,"queue calloc failed");
        exit(1);
    }
    queue.front=0;
    queue.rear=0;
    int calculate_time;
    scanf("%d",&calculate_time);
    for (int i=0;i<calculate_time;i++) {
        char input;
        scanf(" %c",&input);
        switch(input) {
            case 'I':
                int value;
                scanf("%d",&value);
                enqueue(&queue,value);
                break;
            case 'D':
                dequeue(&queue);
                break;
            case 'P':
                queue_print(&queue);
                break;
        }
    }
    free(queue.queue);
    return 0;
}