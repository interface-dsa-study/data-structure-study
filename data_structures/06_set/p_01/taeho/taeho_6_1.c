#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *next;
}Node;
Node *add_node(Node *node) {
    node->next=(Node*)malloc(sizeof(Node));
    if (node->next==NULL) {
        fprintf(stderr,"node mallod failed");
        exit(-1);
    }
    int value;
    scanf("%d",&value);
    node->next->value=value;
    node=node->next;
    node->next=NULL;
    return node;
}
int main() {
    Node *s1,*s2;
    s1=(Node*)malloc(sizeof(Node));
    if (s1==NULL) {
        fprintf(stderr,"list1 malloc failed");
        exit(-1);
    }
    s1->next=NULL;
    s2=(Node*)malloc(sizeof(Node));
    if (s2==NULL) {
        fprintf(stderr,"list2 malloc failed");
        free(s1);
        exit(-1);
    }
    s2->next=NULL;

    int s1_size,s2_size;
    Node *trail_node=s1;
    scanf("%d",&s1_size);
    for (int i=0;i<s1_size;i++) {
        trail_node=add_node(trail_node);
    }
    trail_node=s1;
    scanf("%d",&s2_size);
    for (int i=0;i<s1_size;i++) {
        trail_node=add_node(trail_node);
    }
    
}