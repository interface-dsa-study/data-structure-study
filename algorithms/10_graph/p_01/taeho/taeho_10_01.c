#include <stdio.h>
#include <stdlib.h>
typedef struct vertex V;
typedef struct edge E;
typedef struct incidence I;
struct vertex {
    V *prev;
    V *next;
    int num;
    I *i_header;
};
struct edge {
    E *prev;
    E *next;
    int weight;
    V *v1,*v2;
};
struct incidence {
    I *prev;
    I *next;
    E *edge;
};
V **vertices=NULL;
E **edges=NULL;
I* create_incidence(I *prev,E *edge) {
    I *new_i=malloc(sizeof(*new_i));
    if (!new_i) {
        fprintf(stderr,"incidence malloc failed");
        exit(1);
    }
    new_i->prev=prev;
    if (prev)prev->next=new_i;
    new_i->next=NULL;
    new_i->edge=edge;
    return new_i;
}
V* create_vertex(V *prev,int num,V *next) {
    V *new_v=malloc(sizeof(*new_v));
    if (!new_v) {
        fprintf(stderr,"vertex malloc failed");
        exit(1);
    }
    new_v->num=num;
    new_v->next=next;
    new_v->prev=prev;
    if (prev)prev->next=new_v;
    new_v->i_header=create_incidence(NULL,NULL);
    return new_v;
}
E* create_edge(int weight,E *prev,V *v1,V *v2) {
    E *new_e=malloc(sizeof(new_e));
    new_e->weight=weight;
    new_e->prev=prev;
    if (prev)prev->next=new_e;
    new_e->next=NULL;
    new_e->v1=v1;
    new_e->v2=v2;
    return new_e;
}
void make_graph() {
    *vertices=create_vertex(NULL,1,NULL);
    V **v_pointer=vertices;
    for (int j=2;j<=6;j++,v_pointer++) {
        (*v_pointer)->next=create_vertex(*v_pointer,j,NULL);
    }
    E **e_pointer=edges;
    *e_pointer=create_edge(1,NULL,*vertices,*vertices+1);
    (*e_pointer)->next=create_edge(1,*e_pointer,*vertices,*vertices+2);
    e_pointer++;
    (*e_pointer)->next=create_edge(1,*e_pointer,*vertices,*vertices+3);
    e_pointer++;
    (*e_pointer)->next=create_edge(2,*e_pointer,*vertices,*vertices+5);
    e_pointer++;
    (*e_pointer)->next=create_edge(1,*e_pointer,*vertices,*vertices+2);
    e_pointer++;
    (*e_pointer)->next=create_edge(4,*e_pointer,*vertices,*vertices+4);
    e_pointer++;
    (*e_pointer)->next=create_edge(4,*e_pointer,*vertices+4,*vertices+4);
    e_pointer++;
    (*e_pointer)->next=create_edge(3,*e_pointer,*vertices+4,*vertices+5);
    e_pointer=edges;
    I *i_pointer=(*vertices)->i_header;
    for (int i=0;i<4;i++) {
        i_pointer->next=create_incidence(i_pointer,*e_pointer);
        e_pointer++;
        i_pointer++;
    }
    (*(vertices+1))->i_header->next=create_incidence((*(vertices+1))->i_header,*e_pointer);
    e_pointer++;
    (*(vertices+2))->i_header->next=create_incidence((*(vertices+2))->i_header,*e_pointer);
    e_pointer++;
    (*(vertices+4))->i_header->next=create_incidence((*(vertices+4))->i_header,*e_pointer);
    e_pointer++;
    (*(vertices+4))->i_header->next->next=create_incidence((*(vertices+4))->i_header->next,*e_pointer);
    e_pointer++;
}
V* search_vertex(int num) {
    V **pointer=vertices;
    while (pointer&&(*pointer)->num!=num) pointer++;
    if (pointer)return *pointer;
    return NULL;
}
void a(int num) {
    V *target=search_vertex(num);
    if (!target) {
        printf("-1");
        return;
    }
    I *i_pointer=target->i_header->next;
    while (i_pointer) {
        V *adjacent=find_adjacent(i_pointer->)
        printf(" %d %d",)
    }
}
void free_all() {

}
int main() {
    make_graph();
    while (1) {
        char input=0;
        int num1=0,num2=0,num3=0;
        scanf(" %c",&input);
        if (input=='a') {
            scanf("%d",&num1);
            a(num);
        }
        else if (input=='m') {
            scanf("%d %d %d",&num1,&num2,&num3);

        }
        else break;
    }
    free_all();
    return 0;
}