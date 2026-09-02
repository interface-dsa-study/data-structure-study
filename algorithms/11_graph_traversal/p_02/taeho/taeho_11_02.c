#include <stdio.h>
#include <stdlib.h>
typedef struct vertex V;
typedef struct edge E;
struct vertex {
    V *next;
    int num;
    int visited;
};
struct edge {
    E *next;
    V *v1,*v2;
};
V* create_vertex(int num) {
    V *new_v=malloc(sizeof(*new_v));
    if (!new_v) {
        fprintf(stderr,"vertex malloc failed");
        exit(1);
    }
    new_v->next=NULL;
    new_v->num=num;
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
E* create_edge(V *vertex,E ***matrix,int n1,int n2) {
    E *new_e=malloc(sizeof(*new_e));
    new_e->v1=search_vertex(vertex,n1);
    new_e->v2=search_vertex(vertex,n2);
    if (!new_e->v1||!new_e->v2) {
        printf("-1");
        return NULL;
    }
    new_e->next=NULL;
    if (n1!=n2) matrix[n2-1][n1-1]=new_e;
    matrix[n1-1][n2-1]=new_e;
    return new_e;
}
void visit(V *vertex) {
    printf("%d\n",vertex->num);
}
void enqueue(V **queue,V *vertex, int *rear,int n) {
    vertex->visited=1;
    queue[*rear]=vertex;
    *rear=(*rear+1)%n;
}
V * dequeue(V **queue, int *front,int n) {
    V *target=queue[*front];
    queue[*front]=NULL;
    *front=(*front+1)%n;
    return target;
}
void bfs(V *vertex,E ***matrix,int n) {
    V **queue=calloc(n,sizeof(*queue));
    int *front=calloc(1,sizeof(*front));
    int *rear=calloc(1,sizeof(*rear));
    enqueue(queue,vertex,rear,n);
    while (*front!=*rear) {
        V *current=dequeue(queue,front,n);
        visit(current);
        for (E **column=matrix[current->num-1];column<matrix[current->num-1]+n;column++) {
            if (!*column)continue;
            V *searching=find_adjacent(*column,current);
            if (!searching->visited)enqueue(queue,searching,rear,n);
        }
    }
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
    int n,m,s;
    scanf("%d %d %d",&n,&m,&s);
    E ***matrix=malloc(n*sizeof(*matrix));//인접 행렬 구현
    for (E ***row=matrix;row<matrix+n;row++) *row=calloc(n,sizeof(*row));
    V *vertex=create_vertex(1);//헤더노드 없음
    V *v_pointer=vertex;
    for (int i=2;i<=n;i++,v_pointer=v_pointer->next) v_pointer->next=create_vertex(i);
    int n1,n2;
    scanf("%d %d",&n1,&n2);
    E *edge=create_edge(vertex,matrix,n1,n2);//헤더노드 없음
    E *e_pointer=edge;
    for (int i=1;i<m;i++,e_pointer=e_pointer->next) {
        scanf("%d %d",&n1,&n2);
        if (n1<1||n2<1||n1>n||n2>n) {
            printf("-1");
            return 0;
        }
        e_pointer->next=create_edge(vertex,matrix,n1,n2);
        if (!e_pointer->next) {
            printf("edge create failed");
            return 0;
        }
    }
    bfs(search_vertex(vertex,s),matrix,n);
    free_all(vertex,edge);
    for (E ***row=matrix;row<matrix+n;row++) free(*row);
    free(matrix);
    return 0;
}
