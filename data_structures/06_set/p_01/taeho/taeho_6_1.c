#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *next;
}Node;
Node* append_node(int set_size);
int subset(Node *A,Node *B);
void free_set(Node *node);
int main() {
    int A_size,B_size;
    scanf("%d",&A_size);
    Node *A=append_node(A_size);
    scanf("%d",&B_size);
    Node *B=append_node(B_size);

    int result=subset(A,B);
    printf("%d",result);

    free_set(A);
    free_set(B);
    return 0;
}

Node* append_node(int set_size) {
    if (set_size==0) {
        return NULL;
    }
    Node *set=(Node*)malloc(sizeof(Node));
    if (set==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(-1);
    }
    scanf("%d",&set->value);
    set->next=NULL;
    Node *trail_node=set;
    for (int i=0;i<set_size-1;i++) {
        trail_node->next=(Node*)malloc(sizeof(Node));
        if (trail_node->next==NULL) {
            fprintf(stderr,"node malloc failed");
            exit(-1);
        }
        trail_node=trail_node->next;
        scanf("%d",&trail_node->value);
        trail_node->next=NULL;
    }
    return set;
}
int subset(Node *A,Node *B) {
    Node *A_pointer=A;
    Node *B_pointer=B;
    while (A_pointer&&B_pointer) {
        if (A_pointer->value>B_pointer->value) {
            B_pointer=B_pointer->next;
        }
        else if (A_pointer->value<B_pointer->value) {
            return A_pointer->value;
        }
        else {
            A_pointer=A_pointer->next;
            B_pointer=B_pointer->next;
        }
    }
    if (A_pointer) {
        return A_pointer->value;
    }
    return 0;
}
void free_set(Node *node) {
    if (node) {
        free_set(node->next);
        free(node);
    }
}