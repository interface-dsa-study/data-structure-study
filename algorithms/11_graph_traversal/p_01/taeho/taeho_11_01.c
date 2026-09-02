#include <stdio.h>
#include <stdlib.h>
typedef struct vertex V;
typedef struct edge E;
typedef struct incidence I;
struct vertex {
    V *next;
    int num;
    I *i_header;
    int visited;
};
struct edge {
    E *next;
    V *v1,*v2;
};
struct incidence {
    I *next;
    E *edge;
};
I* create_incidence(E *edge) {
    I *new_i=malloc(sizeof(*new_i));
    if (!new_i) {
        fprintf(stderr,"incidence malloc failed");
        exit(1);
    }
    new_i->next=NULL;
    new_i->edge=edge;
    return new_i;
}
V* create_vertex(int num) {
    V *new_v=malloc(sizeof(*new_v));
    if (!new_v) {
        fprintf(stderr,"vertex malloc failed");
        exit(1);
    }
    new_v->next=NULL;
    new_v->num=num;
    new_v->i_header=create_incidence(NULL);
    new_v->visited=0;
    return new_v;
}
V* search_vertex(V *vertex,int n) {
    V *pointer=vertex;
    for (int i=0;pointer->next&&i<n-1;i++,pointer=pointer->next);
    if (pointer)return pointer;
    return NULL;
}
V* find_adjacent(E *edge,V *vertex) {
    if (edge->v1==vertex)return edge->v2;
    return edge->v1;
}
I* in_order_incidence(V *vertex,int num) {
    I *pointer=vertex->i_header;
    while (pointer&&pointer->next&&find_adjacent(pointer->next->edge,vertex)->num<num) pointer=pointer->next;
    if (pointer)return pointer;
    return NULL;
}
E* create_edge(V *vertex,int n1,int n2) {
    E *new_e=malloc(sizeof(*new_e));
    new_e->v1=search_vertex(vertex,n1);
    new_e->v2=search_vertex(vertex,n2);
    if (!new_e->v1||!new_e->v2) {
        printf("-1");
        return NULL;
    }
    new_e->next=NULL;
    I *prev=in_order_incidence(new_e->v1,new_e->v2->num);//v1의 incidence에 정렬해서 edge 삽입
    if (!prev) {
        printf("-1");
        return NULL;
    }
    I *new_i=create_incidence(new_e);
    new_i->next=prev->next;
    prev->next=new_i;
    if (n1!=n2) {
        prev=in_order_incidence(new_e->v2,new_e->v1->num);//v2의 incidence에 정렬해서 edge 삽입
        if (!prev) {
            printf("-1");
            return NULL;
        }
        new_i=create_incidence(new_e);
        new_i->next=prev->next;
        prev->next=new_i;
    }
    return new_e;
}
void visit(V *vertex) {
    vertex->visited=1;
    printf("%d\n",vertex->num);
}
void dfs(V *vertex) {
    visit(vertex);
    for (I *i_pointer=vertex->i_header->next;i_pointer;i_pointer=i_pointer->next) {
        V *searching_v=find_adjacent(i_pointer->edge,vertex);
        if (!searching_v->visited)dfs(searching_v);
    }
}
int main() {
    int n,m,s;
    scanf("%d %d %d",&n,&m,&s);
    V *vertex=create_vertex(1);//헤더노드 없음
    V *v_pointer=vertex;
    for (int i=2;i<=n;i++,v_pointer=v_pointer->next) v_pointer->next=create_vertex(i);
    int n1,n2;
    scanf("%d %d",&n1,&n2);
    E *edge=create_edge(vertex,n1,n2);//헤더노드 없음
    E *e_pointer=edge;
    for (int i=1;i<m;i++,e_pointer=e_pointer->next) {
        scanf("%d %d",&n1,&n2);
        e_pointer->next=create_edge(vertex,n1,n2);
        if (!e_pointer->next) {
            printf("edge create failed");
            return 0;
        }
    }
    dfs(search_vertex(vertex,s));
}