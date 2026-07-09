#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *next;
}Node;
typedef struct set {
    Node *header;
}Set;
Node *append_node(Node *trail_node,int value);
Set set_create(int set_size);
void set_union(Set *A,Set *B);
void set_intersect(Set *A,Set *B);
void free_set(Node *node);
int main() {
    int A_size,B_size;
    scanf("%d",&A_size);
    Set A=set_create(A_size);
    scanf("%d",&B_size);
    Set B=set_create(B_size);

    set_union(&A,&B);
    set_intersect(&A,&B);

    free_set(A.header->next);
    free_set(B.header->next);
    return 0;
}
Node *append_node(Node *trail_node,int value) {
    trail_node->next=(Node*)malloc(sizeof(Node));
    if (trail_node->next==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(-1);
    }
    trail_node=trail_node->next;
    trail_node->value=value;
    trail_node->next=NULL;
    return trail_node;
}
Set set_create(int set_size) {
    Set set;
    set.header=(Node*)malloc(sizeof(Node));
    if (set.header==NULL) {
        fprintf(stderr,"header malloc failed");
        exit(-1);
    }
    set.header->value=0;
    if (set_size) {
        Node *trail_node=set.header;
        int value;
        for (int i=0;i<set_size;i++) {
            scanf("%d",&value);
            trail_node=append_node(trail_node,value);
        }
    }
    return set;
}
void set_union(Set *A,Set *B) {
    Set result;
    result.header=(Node*)malloc(sizeof(Node));
    if (result.header==NULL) {
        fprintf(stderr,"header malloc failed");
        exit(-1);
    }
    result.header->value=0;
    Node *A_pointer=A->header->next;
    Node *B_pointer=B->header->next;
    Node *trail_node=result.header;
    while (A_pointer&&B_pointer) {
        if (A_pointer->value<B_pointer->value) {
            trail_node=append_node(trail_node,A_pointer->value);
            A_pointer=A_pointer->next;
        }
        else if (A_pointer->value>B_pointer->value) {
            trail_node=append_node(trail_node,B_pointer->value);
            B_pointer=B_pointer->next;
        }
        else {
            trail_node=append_node(trail_node,B_pointer->value);
            A_pointer=A_pointer->next;
            B_pointer=B_pointer->next;
        }
    }
    while (A_pointer) {
        trail_node=append_node(trail_node,A_pointer->value);
        A_pointer=A_pointer->next;
    }
    while (B_pointer) {
        trail_node=append_node(trail_node,B_pointer->value);
        B_pointer=B_pointer->next;
    }
    if (result.header->next==NULL)printf("0");
    for (Node *node=result.header->next;node;node=node->next)printf(" %d",node->value);
    printf("\n");
    free_set(result.header);
}
void set_intersect(Set *A,Set *B) {
    Set result;
    result.header=(Node*)malloc(sizeof(Node));
    if (result.header==NULL) {
        fprintf(stderr,"header malloc failed");
        exit(-1);
    }
    result.header->value=0;
    Node *A_pointer=A->header->next;
    Node *B_pointer=B->header->next;
    Node *trail_node=result.header;
    while (A_pointer&&B_pointer) {
        if (A_pointer->value<B_pointer->value) A_pointer=A_pointer->next;
        else if (A_pointer->value>B_pointer->value) B_pointer=B_pointer->next;
        else {
            trail_node=append_node(trail_node,B_pointer->value);
            A_pointer=A_pointer->next;
            B_pointer=B_pointer->next;
        }
    }
    if (result.header->next==NULL)printf("0");
    for (Node *node=result.header->next;node;node=node->next)printf(" %d",node->value);
    printf("\n");
    free_set(result.header);
}
void free_set(Node *node) {
    if (node) {
        free_set(node->next);
        free(node);
    }
}