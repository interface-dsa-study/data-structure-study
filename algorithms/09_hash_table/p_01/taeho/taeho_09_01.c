#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    struct node *prev;
    int key;
    struct node *next;
}Node;
int m;
int hash(int key) {
    return key%m;
}
Node* create_node(Node *prev,int key,Node *next) {
    Node *node=malloc(sizeof(*node));
    if (!node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    node->prev=prev;
    node->key=key;
    node->next=next;
}
void  insert_item(Node **bucket,int key) {
    Node *last_node=bucket[hash(key)];
    bucket[hash(key)]=create_node(NULL,key,last_node);
    if (last_node)last_node->prev=last_node;
}
void print(Node **bucket) {
    for (Node **bucket_pointer=bucket;bucket_pointer<bucket+m;bucket_pointer++) {
        for (Node *pointer=*bucket_pointer;pointer;pointer=pointer->next) printf(" %d",pointer->key);
    }
}
int search_remove(Node **bucket,int key,int s_or_r) {
    Node *pointer=bucket[hash(key)];
    for (int i=1;pointer;i++,pointer=pointer->next) {
         if (pointer->key==key) {
             if (s_or_r){//탐색과 삭제가 거의 동일-> 통합 s_or_r:1->삭제
                 Node *target=pointer;
                 if (pointer->next)pointer->next->prev=pointer->prev;
                 if (i!=1)pointer->prev->next=pointer->next;
                 else bucket[hash(key)]=pointer->next;
                 free(target);
             }
             return i;
         }
    }
    return 0;
}
void free_bucket(Node **bucket) {
    for (Node **bucket_pointer=bucket;bucket_pointer<bucket+m;bucket_pointer++) {
        Node *node=*bucket_pointer;
        while (node) {
            Node *target=node;
            node=node->next;
            free(target);
        }
    }
    free(bucket);
}
int main() {
    scanf("%d",&m);
    Node **bucket=calloc(m,sizeof(*bucket));
    while (1) {
        char input;
        int key;
        scanf(" %c",&input);
        switch (input) {
            case 'i':
                scanf("%d",&key);
                insert_item(bucket,key);
                break;
            case 's':
                scanf("%d",&key);
                printf("%d",search_remove(bucket,key,0));
                break;
            case 'd':
                scanf("%d",&key);
                printf("%d",search_remove(bucket,key,1));
                break;
            case 'p':
                print(bucket);
                break;
        }
        if (input=='e') break;
    }
    free_bucket(bucket);
    return 0;
}