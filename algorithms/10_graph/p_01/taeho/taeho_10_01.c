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
V* create_vertex(V *prev,int num) {
    V *new_v=malloc(sizeof(*new_v));
    if (!new_v) {
        fprintf(stderr,"vertex malloc failed");
        exit(1);
    }
    new_v->prev=prev;
    if (prev)prev->next=new_v;
    new_v->next=NULL;
    new_v->num=num;
    new_v->i_header=create_incidence(NULL,NULL);
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
I* last_incidence(V *vertex) {
    if (!vertex) {
        printf("vertex not found");
        return NULL;
    }
    I *pointer=vertex->i_header;
    while (pointer&&pointer->next) pointer=pointer->next;
    if (pointer)return pointer;
    return NULL;
}
V* v_next(V *pointer,int time) {
    for (int i=0;pointer&&pointer->next&&i<time;i++) {
        pointer=pointer->next;
    }
    if (pointer)return pointer;
    return NULL;
}
E *e_next(E *pointer,int time) {
    for (int i=0;pointer&&pointer->weight&&i<time;i++) {
        pointer=pointer->next;
    }
    if (pointer&&pointer->weight)return pointer;
    return NULL;
}
void create_graph(V *v_header,E *e_header) {
    V *v_pointer=v_header;
    for (int j=1;j<=6;j++) {
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
    I *i_pointer=v_header->next->i_header;
    for (int i=0;i<4;i++) {
        i_pointer->next=create_incidence(i_pointer,e_pointer);
        I *l_i=NULL;
        switch (i) {
            case 0:
                l_i=last_incidence(v_next(v_header,2));
                break;
            case 1:
                l_i=last_incidence(v_next(v_header,3));
                break;
            case 2:
                l_i=last_incidence(v_next(v_header,4));
                break;
            case 3:
                l_i=last_incidence(v_next(v_header,6));
                break;
            default:
                return;
        }
        l_i->next=create_incidence(l_i,e_pointer);
        e_pointer=e_pointer->next;
        i_pointer=i_pointer->next;
    }
    last_incidence(v_next(v_header,2))->next=create_incidence(last_incidence(v_next(v_header,2)),e_pointer);
    last_incidence(v_next(v_header,3))->next=create_incidence(last_incidence(v_next(v_header,3)),e_pointer);
    e_pointer=e_pointer->next;
    last_incidence(v_next(v_header,3))->next=create_incidence(last_incidence(v_next(v_header,3)),e_pointer);
    last_incidence(v_next(v_header,5))->next=create_incidence(last_incidence(v_next(v_header,5)),e_pointer);
    e_pointer=e_pointer->next;
    last_incidence(v_next(v_header,5))->next=create_incidence(last_incidence(v_next(v_header,5)),e_pointer);
    e_pointer=e_pointer->next;
    last_incidence(v_next(v_header,5))->next=create_incidence(last_incidence(v_next(v_header,5)),e_pointer);
    last_incidence(v_next(v_header,6))->next=create_incidence(last_incidence(v_next(v_header,6)),e_pointer);
}
V* search_vertex(V *v_header,int num) {
    V *vertex=v_header->next;
    while (vertex&&vertex->num!=num&&vertex->next) vertex=vertex->next;
    if (vertex&&vertex->num==num)return vertex;
    return NULL;
}
V* find_adjacent(E *edge,int num) {
    if (!edge)return NULL;
    if (edge->v1->num==num)return edge->v2;
    return edge->v1;
}
void a(V *v_header,int num) {
    V *target=search_vertex(v_header,num);
    if (!target) {
        printf("-1");
        return;
    }
    I *i_pointer=target->i_header->next;
    while (i_pointer) {
        V *adjacent=find_adjacent(i_pointer->edge,num);
        if (!adjacent)return;
        printf(" %d %d",adjacent->num,i_pointer->edge->weight);
        i_pointer=i_pointer->next;
    }
}
E* search_edge(V *v1,V *v2) {
    I *v1_i=v1->i_header->next;
    if (!v1_i)return NULL;
    I *v2_i=v2->i_header->next;
    if (!v2_i)return NULL;
    while (v1_i) {
        while (v2_i) {
            if (find_adjacent(v1_i->edge,v1->num)==v2&&find_adjacent(v2_i->edge,v2->num)==v1)return v1_i->edge;
            v2_i=v2_i->next;
        }
        v2_i=v2->i_header->next;
        v1_i=v1_i->next;
    }
    return NULL;
}
I* search_incidence(V *vertex,E *edge) {
    I *v_i=vertex->i_header->next;
    while (v_i) {
        if (v_i->edge==edge)return v_i;
        v_i=v_i->next;
    }
    return NULL;
}
void free_incidence(I *target) {
    if (!target->edge)return;
    target->prev->next=target->next;
    if (target->next)target->next->prev=target->prev;
    free(target);
}
void delete_edge(V *v_header,int num1,int num2) {
    V *v1=search_vertex(v_header,num1);
    V *v2=search_vertex(v_header,num2);
    if (!v1||!v2) {
        printf("-1");
        return;
    }
    E *target=search_edge(v1,v2);
    if (!target) {
        printf("target edge not found");
        return;
    }
    if (v1!=v2) {
        I *v1_i=search_incidence(v1,target);
        if (!v1_i) {
            printf("vertex1 incidence not found");
            return;
        }
        v1_i->prev->next=v1_i->next;
        if (v1_i->next)v1_i->next->prev=v1_i->prev;
        free_incidence(v1_i);
    }
    I *v2_i=search_incidence(v2,target);
    if (!v2_i) {
        printf("vertex2 incidence not found");
        return;
    }
    v2_i->prev->next=v2_i->next;
    if (v2_i->next)v2_i->next->prev=v2_i->prev;
    free_incidence(v2_i);
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
I* in_order_incidence(V *vertex,int num) {
    I *pointer=vertex->i_header;
    while (pointer&&pointer->next&&find_adjacent(pointer->next->edge,vertex->num)->num<num) pointer=pointer->next;
    if (pointer)return pointer;
    return NULL;
}
void m(V *v_header,E *e_header,int num1,int num2,int w) {
    if (!w) {
        delete_edge(v_header,num1,num2);
        return;
    }
    V *v1=search_vertex(v_header,num1);
    V *v2=search_vertex(v_header,num2);
    if (!v1||!v2) {
        printf("-1");
        return;
    }
    E *target=search_edge(v1,v2);
    if (!target) {
        I *i1=in_order_incidence(v1,v2->num);
        I *i2=in_order_incidence(v2,v1->num);
        if (!i1||!i2) {
            printf("incidence not found");
            return;
        }
        target=create_edge(e_last(e_header),w,v1,v2);
        if (v1!=v2) {
            if (i1!=last_incidence(v1)) {
                I *li=i1->next;
                i1->next=create_incidence(i1,target);
                i1->next->next=li;
                li->prev=i1->next;
            }
            else i1->next=create_incidence(i1,target);
        }
        if (i2!=last_incidence(v2)) {
            I *li=i2->next;
            i2->next=create_incidence(i2,target);
            i2->next->next=li;
            li->prev=i2->next;
        }
        else i2->next=create_incidence(i2,target);
        return;
    }
    target->weight=w;
}
void free_all(V *v_header,E *e_header) {
    V *v_pointer=v_header;
    E *e_pointer=e_header;
    while (v_pointer) {
        I *i_pointer=v_pointer->i_header;
        I *i_target=i_pointer;
        while (i_pointer) {
            i_target=i_pointer;
            i_pointer=i_pointer->next;
            free(i_target);
        }
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
    create_graph(v_header,e_header);
    while (1) {
        char input;
        int num1=0,num2=0,w=0;
        scanf(" %c %d",&input,&num1);
        if (input=='a') {
            a(v_header,num1);
        }
        else if (input=='m') {
            scanf("%d %d",&num2,&w);
            m(v_header,e_header,num1,num2,w);
        }
        else break;
        printf("\n");
    }
    free_all(v_header,e_header);
    return 0;
}