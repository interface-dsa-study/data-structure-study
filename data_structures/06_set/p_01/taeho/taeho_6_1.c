#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *next;
}Node;
Node *add_node(Node *node) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"node mallod")
    }
    int value;
    scanf("%d",&value);
    return
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
    scanf("%d",&s1_size);
    for (int i=0;i<s1_size;i++) {
        s1=
    }
}