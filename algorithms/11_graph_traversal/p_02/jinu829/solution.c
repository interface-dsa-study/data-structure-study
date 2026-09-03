#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int isFresh;
    int data;
} Node;

typedef struct QueueNode
{
    int number;
    struct QueueNode *next;
} QueueNode;

typedef struct Edge
{
    struct Node *smallNode;
    struct Node *bigNode;
    int isFresh;
} Edge;

typedef struct AdjancyElement
{
    int isFilled;
    struct Edge *edge;
} AdjancyElement;

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->isFresh = 1;
    return new_node;
}

void createEdge(Node *node1, Node *node2, AdjancyElement **adjancyMatrix, int node1index, int node2index)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->smallNode = node1;
    edge->bigNode = node2;
    edge->isFresh = 1;

    adjancyMatrix[node1index][node2index].isFilled = 1;
    adjancyMatrix[node2index][node1index].isFilled = 1;
    adjancyMatrix[node1index][node2index].edge = edge;
    adjancyMatrix[node2index][node1index].edge = edge;

    return;
}

void insertNodeToQueue(QueueNode **phead, int number)
{
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    new_node->next = *phead;
    new_node->number = number;
    *phead = new_node;
}

void removeNodeToQueue(QueueNode **phead, int count)
{
    QueueNode *removeNode = *phead;
    QueueNode *prev = NULL; /* [수정] prev 초기화 */
    for (int i = 1; i < count; i++)
    {
        prev = removeNode;
        removeNode = removeNode->next;
    }
    if (count == 1)
    {
        *phead = NULL;
        free(removeNode);
        return;
    }
    prev->next = NULL;
    free(removeNode);
}

void BFS(Node **nodeArray, AdjancyElement **adjancyMatrix, int node_number, int n)
{
    int count = 0;
    int number = node_number; /* [수정] 시작 정점 번호(node_number)로 초기화 */
    QueueNode *head = NULL;
    QueueNode *countNode;
    Node *opposite;

    /* [수정] 시작 정점 방문 처리 및 출력 */
    nodeArray[node_number]->isFresh = 0;
    printf("%d\n", nodeArray[node_number]->data);

    insertNodeToQueue(&head, number);
    count++;

    while (head != NULL)
    {
        /* [수정] 큐의 맨 뒤(가장 먼저 들어온 정점)를 꺼내어 현재 탐색 정점 number로 설정 */
        countNode = head;
        while (countNode->next != NULL)
        {
            countNode = countNode->next;
        }
        number = countNode->number;
        removeNodeToQueue(&head, count);
        count--;

        for (int j = 1; j < n + 1; j++)
        {
            if (adjancyMatrix[number][j].isFilled == 1)
            {
                if (adjancyMatrix[number][j].edge->isFresh == 1)
                {
                    opposite = adjancyMatrix[number][j].edge->bigNode == nodeArray[number] ? adjancyMatrix[number][j].edge->smallNode : adjancyMatrix[number][j].edge->bigNode;
                    if (opposite->isFresh == 1)
                    {
                        /* [수정] 방문하지 않은 인접 정점 방문 처리 후 큐에 삽입 및 출력 */
                        nodeArray[j]->isFresh = 0;
                        printf("%d\n", nodeArray[j]->data);
                        adjancyMatrix[number][j].edge->isFresh = 0;
                        insertNodeToQueue(&head, j);
                        count++;
                    }
                    else
                    {
                        adjancyMatrix[number][j].edge->isFresh = 0;
                    }
                }
            }
        }
    }
}

int main()
{
    int n, m, s;
    int node_number1, node_number2;
    AdjancyElement **adjacencyMatrix;
    Node **nodeArray;

    scanf("%d %d %d", &n, &m, &s);
    adjacencyMatrix = (AdjancyElement **)malloc(sizeof(AdjancyElement *) * (n + 1));
    for (int i = 1; i < n + 1; i++)
    {
        adjacencyMatrix[i] = (AdjancyElement *)malloc(sizeof(AdjancyElement) * (n + 1));
        for (int j = 1; j < n + 1; j++)
        {
            adjacencyMatrix[i][j].isFilled = 0;
        }
    }
    nodeArray = (Node **)malloc(sizeof(Node *) * (n + 1));
    for (int i = 1; i < n + 1; i++)
    {
        nodeArray[i] = createNode(i); /* [수정] 1번부터 n번까지의 모든 정점을 미리 생성 */
    }

    for (int i = 0; i < m; i++)
    { /* [수정] 9가 아닌 입력받은 간선 수 m만큼 반복 */
        scanf("%d %d", &node_number1, &node_number2);
        createEdge(nodeArray[node_number1], nodeArray[node_number2], adjacencyMatrix, node_number1, node_number2);
    }

    BFS(nodeArray, adjacencyMatrix, s, n);

    return 0;
}