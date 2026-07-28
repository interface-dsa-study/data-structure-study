#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
}Node;
typedef struct queue {
    Node **queue;
    int front;
    int rear;
}Queue;
Node* create_node(int data) {//트리 노드 생성
    Node *new_node=(Node *)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->data=data;
    new_node->left=NULL;
    new_node->right=NULL;
    return new_node;
}
Node* create_tree() {//임의 트리 생성, 트리 번호는 없음
    Node *loot_node=create_node(20);
    loot_node->left=create_node(30);
    loot_node->left->left=create_node(70);
    loot_node->left->right=create_node(90);
    loot_node->right=create_node(50);
    loot_node->right->right=create_node(120);
    loot_node->right->right->left=create_node(130);
    loot_node->right->right->right=create_node(80);
    return loot_node;
}
Queue* create_queue() {
    Queue *queue=(Queue*)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr,"queue malloc1 failed");
        exit(1);
    }
    queue->queue=(Node**)malloc(sizeof(Node*));//한 레벨에 얼마나 많은 노드가 있는지 모름-> 동적할당
    if (!queue->queue) {
        fprintf(stderr,"queue malloc2 failed");
        exit(1);
    }
    queue->front=0;
    queue->rear=0;
    return queue;
}
void enqueue(Queue *queue,Node *pointer) {
    queue->queue=(Node**)realloc(queue->queue,(++queue->rear)*sizeof(Node*));//큐 크기 재할당
    if (!queue->queue) {
        fprintf(stderr,"queue realloc failed");
        exit(1);
    }//예외처리
    queue->queue[queue->rear-1]=pointer;//큐 맨뒤에 포인터(노드 주소) 저장
}
Node* dequeue(Queue *queue) {//큐 맨앞 데이터(노드 주소) 추출
    if (queue->front==queue->rear) {
        fprintf(stderr,"empty queue exception");
        exit(1);
    }
    return queue->queue[queue->front++];
}
Node* search(int target,Node *loot_node) {//트리 레벨 순회 후 찾는 노드 반환
    if (loot_node) {
        if (!target)return loot_node;
        Queue *queue=create_queue();//레벨순회->큐 생성
        int index=0;
        Node *pointer=loot_node;
        enqueue(queue,loot_node);
        while (queue->front<queue->rear){
            pointer=dequeue(queue);//큐에 저장되어있던 주소 꺼내기
            if (index==target) {
                free(queue->queue);
                free(queue);
                return pointer;
            }
            index++;
            if (pointer->left) {
                enqueue(queue,pointer->left);
            }
            if (pointer->right) {
                enqueue(queue,pointer->right);
            }
        }
    free(queue->queue);
    free(queue);
    }
    return NULL;
}
void free_node(Node *node) {
    if (node) {
        free_node(node->left);
        free_node(node->right);
        free(node);
    }
}
int main() {
    Node *loot_node=create_tree();
    int target;//찾는 노드의 숫자
    scanf("%d",&target);
    target--;//찾는 노드번호->인덱스로 변환
    Node *target_node=search(target,loot_node);
    if (target_node) {
        printf("%d",target_node->data);
        if (target_node->left)printf(" %d",target_node->left->data);
        if (target_node->right)printf(" %d",target_node->right->data);
    }
    else  printf("-1");
    printf("\n");
    free_node(loot_node);
    return 0;
}