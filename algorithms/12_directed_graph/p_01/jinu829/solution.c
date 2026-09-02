#include <stdio.h>
#include <stdlib.h>

typedef struct inEdges
{ // 들어오는 edge들을 가리키는 인접리스트
    struct Edge *edge;
    struct inEdges *next;
} inEdges;

typedef struct outEdges
{ // 나가는 edge들을 가리키는 인접리스트
    struct Edge *edge;
    struct outEdges *next;
} outEdges;

typedef struct vertex
{ // 정점
    char name;
    struct inEdges *inEdge;
    struct outEdges *outEdge;
    int inDegree;
} vertex;

typedef struct Edge // 간선
{
    struct vertex *origin;
    struct vertex *destination;
} Edge;

typedef struct Node
{
    struct vertex *vertex;
    struct Node *next;
} Node;

int index(char name, int n, vertex **vertexArray)
{
    for (int i = 1; i < n + 1; i++)
    {
        if (vertexArray[i]->name == name)
        {
            return i;
        }
    }
    return 0; // [수정] 반환값 누락 방지
}

void insertVertex(char name, int i, vertex **vertexArray)
{
    vertexArray[i]->name = name;
    vertexArray[i]->outEdge = (outEdges *)malloc(sizeof(outEdges));
    vertexArray[i]->outEdge->next = NULL;

    vertexArray[i]->inEdge = (inEdges *)malloc(sizeof(inEdges));
    vertexArray[i]->inEdge->next = NULL;

    vertexArray[i]->inDegree = 0;
    return;
}

void insertDirectedEdge(char outVertexName, char inVertexName, vertex **vertexArray, int n)
{
    outEdges *new_outEdge = (outEdges *)malloc(sizeof(outEdges));
    inEdges *new_inEdge = (inEdges *)malloc(sizeof(inEdges));
    Edge *new_Edge = (Edge *)malloc(sizeof(Edge));

    int u = index(outVertexName, n, vertexArray);
    int w = index(inVertexName, n, vertexArray);

    new_inEdge->edge = new_Edge;
    new_outEdge->edge = new_Edge;

    new_Edge->origin = vertexArray[u];      // G.edges[i].origin ← u
    new_Edge->destination = vertexArray[w]; // G.edges[i].destination ← w

    new_outEdge->next = vertexArray[u]->outEdge->next; // addFirst(G.vertices[u].outEdges, i)
    vertexArray[u]->outEdge->next = new_outEdge;       // [수정] vertexArray[w] -> vertexArray[u]로 변경

    new_inEdge->next = vertexArray[w]->inEdge->next; // addFirst(G.vertices[w].inEdges, i)
    vertexArray[w]->inEdge->next = new_inEdge;

    vertexArray[w]->inDegree += 1;

    return;
}

int isEmpty(Node **phead)
{
    return *phead == NULL;
}

void enqueue(Node **phead, vertex *vertex)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->vertex = vertex;

    new_node->next = *phead;
    *phead = new_node;
}

vertex *dequeue(Node **phead)
{
    Node *remove_node = *phead;
    Node *prev;
    vertex *vertex;
    if (remove_node == NULL)
        return NULL;
    while (remove_node->next != NULL)
    {
        prev = remove_node;
        remove_node = remove_node->next;
    }
    if ((*phead)->next == NULL)
    {
        *phead = NULL; // [수정] *phead == NULL; 비교문에서 대입문으로 수정
        vertex = remove_node->vertex;
        free(remove_node);
        return vertex;
    }
    prev->next = remove_node->next;
    vertex = remove_node->vertex;
    free(remove_node);
    return vertex;
}

int main()
{
    vertex **vertexArray;
    vertex **topOrder;
    vertex *v, *w;
    outEdges *outedgeinmain;
    int n, m, t;
    char name;            // [수정] int -> char 타입으로 변경
    char inName, outName; // [수정] int -> char 타입으로 변경
    int count = 0;
    int *in;
    Node *head = NULL;
    scanf("%d", &n);
    vertexArray = (vertex **)malloc(sizeof(vertex *) * (n + 1));

    for (int i = 1; i < n + 1; i++)
    {
        vertexArray[i] = (vertex *)malloc(sizeof(vertex));
        scanf(" %c", &name);
        insertVertex(name, i, vertexArray);
    }

    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        scanf(" %c %c", &outName, &inName);
        insertDirectedEdge(outName, inName, vertexArray, n);
    }
    // 여기까지가 그래프 세팅

    in = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 1; i < n + 1; i++)
    {
        in[i] = vertexArray[i]->inDegree;
        if (in[i] == 0)
            enqueue(&head, vertexArray[i]);
    }

    t = 1;

    topOrder = (vertex **)malloc(sizeof(vertex *) * (n + 1));

    while (!isEmpty(&head))
    {
        v = dequeue(&head);
        topOrder[t] = v;
        t += 1;

        outedgeinmain = v->outEdge->next;
        while (outedgeinmain != NULL)
        {
            w = outedgeinmain->edge->destination;
            int w_idx = index(w->name, n, vertexArray); // [수정] w의 배열 인덱스 탐색
            in[w_idx] -= 1;                             // [수정] vertex 차수 대신 in 배열 값 갱신
            if (in[w_idx] == 0)                         // [수정] in 배열 검사
                enqueue(&head, w);
            outedgeinmain = outedgeinmain->next; // [수정] 다음 진출간선으로 이동(무한루프 방지)
        }
    }

    if (t <= n)
        printf("0");
    else
    {
        for (int i = 1; i < n + 1; i++)
        {
            printf("%c ", topOrder[i]->name);
        }
    }

    return 0;
}