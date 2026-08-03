#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int id;
    int data;
    struct node *left;
    struct node *right;
}Node;
typedef struct queue {
    int size;
    Node **queue;
    int front;
    int rear;
}Queue;
Node* create_node(int data) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    new_node->id=0;
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
void visit(Node *node) {
    printf(" %d",node->data);
}
void order(int traversal,Node *node) {
    if (node) {
        if (traversal==1) visit(node);
        if (node->left) order(traversal,node->left);
        if (traversal==2) visit(node);
        if (node->right) order(traversal,node->right);
        if (traversal==3) visit(node);
    }
}
int is_queue_empty(Queue *queue) {
    return queue->front==queue->rear;
}
void enqueue(Queue *queue,Node *data) {
    queue->rear++;
    if (queue->rear+1==queue->size) {
        queue->size*=2;
        Node **temporary_queue=(Node**)realloc(queue->queue,queue->size*sizeof(Node*));
        if (!temporary_queue) {
            fprintf(stderr,"queue realloc failed");
            exit(1);
        }
        queue->queue=temporary_queue;
    }
    queue->queue[queue->rear]=data;
}
Node* dequeue(Queue *queue) {
    queue->front++;
    return queue->queue[queue->front];
}
Node* search(Node *loot_node,int id) {//트리 레벨 순회 후 노드에 id 삽입
    if (!loot_node)return NULL;
    int tree_id=1;
    Node *target_node=NULL;
    Queue queue;
    queue.size=2;
    queue.queue=(Node**)malloc(queue.size*sizeof(Node*));
    if (!queue.queue) {
        fprintf(stderr,"queue malloc failed");
        exit(1);
    }
    queue.front=0;
    queue.rear=0;
    enqueue(&queue,loot_node);
    while (!is_queue_empty(&queue)) {
        Node *node=dequeue(&queue);
        if (tree_id==id) target_node=node;
        node->id=tree_id++;
        if (node->left) enqueue(&queue,node->left);
        if (node->right) enqueue(&queue,node->right);
    }
    return target_node;
}
void free_binomial_tree_node(Node *node) {
    if (node->left) free_binomial_tree_node(node->left);
    if (node->right) free_binomial_tree_node(node->right);
    if (node) free(node);
}
int main() {
    Node *loot_node=create_tree();
    int traversal,id;
    scanf("%d %d",&traversal,&id);
    Node *searching_node=search(loot_node,id);
    if (!searching_node)printf("-1");
    else order(traversal,searching_node);
    free_binomial_tree_node(loot_node);
    return 0;
}