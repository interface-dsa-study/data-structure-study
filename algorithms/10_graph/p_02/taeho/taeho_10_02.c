#include <stdio.h>
#include <stdlib.h>

#define vertex_amount 6
typedef struct vertex V;
typedef struct edge E;
struct vertex {
    V *next;
    int num;
};
struct edge {
    E *prev;
    E *next;
    int weight;
    V *v1,*v2;
};
V* create_vertex(V *prev,int num) {
    V *new_v=malloc(sizeof(*new_v));
    if (!new_v) {
        fprintf(stderr,"vertex malloc failed");
        exit(1);
    }
    if (prev)prev->next=new_v;
    new_v->next=NULL;
    new_v->num=num;
    return new_v;
}
E* create_edge(E *prev,int weight,V *v1,V *v2) {
    E *new_e=malloc(sizeof(*new_e));
    if (!new_e) {
        fprintf(stderr,"edge malloc failed");
        exit(1);
    }
    new_e->prev=prev;
    if (prev)prev->next=new_e;
    new_e->next=NULL;
    new_e->weight=weight;
    new_e->v1=v1;
    new_e->v2=v2;
    return new_e;
}
V* v_next(V *pointer,int time) {
    for (int i=0;pointer&&pointer->next&&i<time;i++) {
        pointer=pointer->next;
    }
    if (pointer)return pointer;
    return NULL;
}
void create_graph(V *v_header,E *e_header, E ***matrix) {
    V *v_pointer=v_header;
    for (int j=1;j<=vertex_amount;j++) {
        v_pointer->next=create_vertex(v_pointer,j);
        v_pointer=v_pointer->next;
    }
    E *e_pointer=e_header;
    e_pointer->next=create_edge(e_pointer,1,v_next(v_header,1),v_next(v_header,2));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,1,v_next(v_header,1),v_next(v_header,3));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,1,v_next(v_header,1),v_next(v_header,4));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,2,v_next(v_header,1),v_next(v_header,6));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,1,v_next(v_header,2),v_next(v_header,3));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,4,v_next(v_header,3),v_next(v_header,5));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,4,v_next(v_header,5),v_next(v_header,5));
    e_pointer=e_pointer->next;
    e_pointer->next=create_edge(e_pointer,3,v_next(v_header,5),v_next(v_header,6));
    e_pointer=e_header->next;
    matrix[0][1]=e_pointer;
    matrix[1][0]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[0][2]=e_pointer;
    matrix[2][0]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[0][3]=e_pointer;
    matrix[3][0]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[0][5]=e_pointer;
    matrix[5][0]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[1][2]=e_pointer;
    matrix[2][1]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[2][4]=e_pointer;
    matrix[4][2]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[4][4]=e_pointer;
    e_pointer=e_pointer->next;
    matrix[4][5]=e_pointer;
    matrix[5][4]=e_pointer;
}
V* search_vertex(V *v_header,int num) {
    V *vertex=v_header->next;
    while (vertex&&vertex->num!=num&&vertex->next) vertex=vertex->next;
    if (vertex&&vertex->num==num)return vertex;
    return NULL;
}
void a(int num,E ***matrix) {
    num--;
    if (num<0||num>=vertex_amount) {
        printf("-1");
        return;
    }
    for (int index=0;index<vertex_amount;index++) {
        if (matrix[num][index]) {
            printf(" %d %d",index+1,matrix[num][index]->weight);
        }
    }
}
void delete_edge(E ***matrix,int num1,int num2) {
    E *target=matrix[num1][num2];
    if (num1!=num2) matrix[num2][num1]=NULL;
    matrix[num1][num2]=NULL;
    target->prev->next=target->next;
    if (target->next)target->next->prev=target->prev;
    free(target);
}
E* e_last(E *e_header) {
    E *edge=e_header;
    while (edge&&edge->next)edge=edge->next;
    if (edge)return edge;
    return NULL;
}
void m(V *v_header,E *e_header,E ***matrix,int num1,int num2,int w) {
    num1--;
    num2--;
    if (num1<0||num2<0||num1>=vertex_amount||num2>=vertex_amount) {
        printf("-1");
        return;
    }
    if (!w) {
        delete_edge(matrix,num1,num2);
        return;
    }
    E *target=matrix[num1][num2];
    if (!target) {
        target=create_edge(e_last(e_header),w,search_vertex(v_header,num1+1),search_vertex(v_header,num2+1));
        if (num1!=num2) matrix[num2][num1]=target;
        matrix[num1][num2]=target;
        return;
    }
    target->weight=w;
}
void free_all(V *v_header,E *e_header) {
    V *v_pointer=v_header;
    E *e_pointer=e_header;
    while (v_pointer) {
        V *v_target=v_pointer;
        v_pointer=v_pointer->next;
        free(v_target);
    }
    while (e_pointer) {
        E *e_target=e_pointer;
        e_pointer=e_pointer->next;
        free(e_target);
    }
}
int main() {
    V *v_header=calloc(1,sizeof(*v_header));
    E *e_header=calloc(1,sizeof(*e_header));
    E ***matrix=calloc(vertex_amount,sizeof(*matrix));
    for (E ***row=matrix;row<matrix+vertex_amount;row++) *row=calloc(vertex_amount,sizeof(*row));
    create_graph(v_header,e_header,matrix);
    while (1) {
        char input;
        int num1=0,num2=0,w=0;
        scanf(" %c %d",&input,&num1);
        if (input=='a') {
            a(num1,matrix);
        }
        else if (input=='m') {
            scanf("%d %d",&num2,&w);
            m(v_header,e_header,matrix,num1,num2,w);
        }
        else break;
        printf("\n");
    }
    free_all(v_header,e_header);
    for (E ***row=matrix;row<matrix+vertex_amount;row++) free(*row);
    free(matrix);
    return 0;
}