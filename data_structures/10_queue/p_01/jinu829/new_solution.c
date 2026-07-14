#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int insertQueue(int *circularQueue, int data, int front, int rear, int q){ //rear값 하나 올리고, 만약 rear == front면 오류 상태니까 overflow, 아니면 rear칸에 data대입
    rear = (rear + 1) % q;
    if (rear == front){
        printf("overflow");
        for (int i = 0; i < q; i++){
            printf(" %d", circularQueue[i]);
        }
        return rear - 1;
    }
    circularQueue[rear] = data;
    return rear;
}

int deleteQueue(int *circularQueue, int front, int rear, int q){
    if (front == rear){
        printf("underflow");
        return front;
    }
    front = (front + 1) % q;
    circularQueue[front] = 0;
    return front;
}

void print(int *circularQueue, int q){
    for (int i = 0; i < q; i++){
        printf(" %d", circularQueue[i]);
    }
    printf("\n");
}

int main(){
    int *circularQueue;
    int q; //원형 배열 크기
    int n; //입력받을 횟수
    char calculation;
    int data; //원형 배열 안에 넣을 데이터
    int front = 0, rear = 0; //배열의 첫 번째 위치와 마지막 위치
    int rearPre, frontPre;
    scanf("%d", &q);
    scanf("%d", &n);
    circularQueue = (int *)malloc(sizeof(int) * q);

    for (int i = 0; i < q; i++){ //0으로 초기화
        circularQueue[i] = 0;
    }

    for (int i = 0; i < n; i++){
        scanf(" %c", &calculation);
        if (calculation == 'I'){
            scanf("%d", &data); 
            rearPre = rear;
            rear = insertQueue(circularQueue, data, front, rear, q); 
            if (rear == rearPre){ //오류 발생 시 rear값이 +1되지 않음. 그러면 break;
                free(circularQueue);
                break;
            }
        }
        else if (calculation == 'D'){
            frontPre = front;
            front = deleteQueue(circularQueue, front, rear, q);
            if (front == frontPre){
                free(circularQueue);
                break;
            }
        }
        else if (calculation == 'P'){
            print(circularQueue, q);
        }
    }
    return 0;
}