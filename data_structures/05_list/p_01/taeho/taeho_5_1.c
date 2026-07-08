#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int coef;
    int exp;
    struct node *next;
}Node;
typedef struct list {
    Node *head;
}List;
Node* append_term(Node *trail_node,int coef,int exp);
List sum(List *l1,List *l2);
void print(List *list);
void free_list(Node *node);
int main() {
    List l1;
    l1.head=(Node*)malloc(sizeof(Node));
    if (l1.head==NULL) {
        fprintf(stderr,"list1 malloc failed");
        exit(-1);
    }
    l1.head->coef=0;
    l1.head->exp=0;
    l1.head->next=NULL;
    int f1_n;

    List l2;
    l2.head=(Node*)malloc(sizeof(Node));
    if (l2.head==NULL) {
        fprintf(stderr,"list2 malloc failed");
        free(l1.head);
        exit(-1);
    }
    l2.head->coef=0;
    l2.head->exp=0;
    l2.head->next=NULL;
    int f2_n;

    int coef,exp;
    scanf("%d",&f1_n);
    Node *trail_node=l1.head;
    for (int i=0;i<f1_n;i++) {
        scanf("%d %d",&coef,&exp);
        trail_node=append_term(trail_node,coef,exp);
    }
    scanf("%d",&f2_n);
    trail_node=l2.head;
    for (int i=0;i<f2_n;i++) {
        scanf("%d %d",&coef,&exp);
        trail_node=append_term(trail_node,coef,exp);
    }
    List l3=sum(&l1,&l2);
    print(&l3);
    free_list(l1.head);
    free_list(l2.head);
    free_list(l3.head);
    return 0;
}
Node* append_term(Node *trail_node,int coef,int exp) {
    trail_node->next=(Node*)malloc(sizeof(Node));
    if (trail_node->next==NULL) {
        fprintf(stderr,"malloc failed");
        exit(-1);
    }
    trail_node=trail_node->next;
    trail_node->coef=coef;
    trail_node->exp=exp;
    trail_node->next=NULL;
    return trail_node;
}
List sum(List *l1,List *l2) {
    List result;
    result.head=(Node*)malloc(sizeof(Node));
    if (result.head==NULL) {
        fprintf(stderr,"sum malloc failed");
        free_list(l1->head);
        free_list(l2->head);
        exit(-1);
    }
    result.head->coef=0;
    result.head->exp=0;
    result.head->next=NULL;
    Node *trail_node=result.head;
    Node *l1_pointer=l1->head->next;
    Node *l2_pointer=l2->head->next;

    while (l1_pointer!=NULL&&l2_pointer!=NULL) {
        if (l1_pointer->exp>l2_pointer->exp) {
            trail_node=append_term(trail_node,l1_pointer->coef,l1_pointer->exp);
            l1_pointer=l1_pointer->next;
        }
        else if (l1_pointer->exp==l2_pointer->exp) {
            if (l1_pointer->coef+l2_pointer->coef){
                trail_node=append_term(trail_node,l1_pointer->coef+l2_pointer->coef,l1_pointer->exp);
            }
            l1_pointer=l1_pointer->next;
            l2_pointer=l2_pointer->next;
        }
        else if (l1_pointer->exp<l2_pointer->exp) {
            trail_node=append_term(trail_node,l2_pointer->coef,l2_pointer->exp);
            l2_pointer=l2_pointer->next;
        }
    }
    for (;l2_pointer!=NULL;l2_pointer=l2_pointer->next) {
        trail_node=append_term(trail_node,l2_pointer->coef,l2_pointer->exp);
    }
    for (;l1_pointer!=NULL;l1_pointer=l1_pointer->next) {
        trail_node=append_term(trail_node,l1_pointer->coef,l1_pointer->exp);
    }
    return result;
}
void print(List *list) {
    Node *pointer=list->head->next;
    for (;pointer!=NULL;pointer=pointer->next) {
        printf("%dX^%d ",pointer->coef,pointer->exp);//원래는 숫자만 출력인데 알아보기 편하게 출력
    }
}
void free_list(Node *node) {
    if (node) {
        free_list(node->next);
        free(node);
    }
}