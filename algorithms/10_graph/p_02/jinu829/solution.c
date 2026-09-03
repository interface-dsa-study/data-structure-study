#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
} Node;

typedef struct Edge
{
    struct Node *smallNode;
    struct Node *bigNode;
    int weight;
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
    return new_node;
}

void createEdge(int weight, Node *node1, Node *node2, AdjancyElement **adjancyMatrix, int node1index, int node2index)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->weight = weight;
    edge->smallNode = node1;
    edge->bigNode = node2;

    adjancyMatrix[node1index][node2index].isFilled = 1;
    adjancyMatrix[node2index][node1index].isFilled = 1;
    adjancyMatrix[node1index][node2index].edge = edge;
    adjancyMatrix[node2index][node1index].edge = edge;

    return;
}

void a(Node **nodeArray, AdjancyElement **adjancyMatrix, int node_data)
{
    if (node_data < 1 || node_data > 6)
    {
        printf("-1\n");
        return;
    }
    for (int i = 1; i < 7; i++)
    {
        if (adjancyMatrix[node_data][i].isFilled == 1)
        {
            printf(" %d %d", nodeArray[i]->data, adjancyMatrix[node_data][i].edge->weight);
        }
    }
    printf("\n");
    return;
}

void m(Node **nodeArray, AdjancyElement **adjancyMatrix, int node_data1, int node_data2, int weight)
{
    if ((node_data1 < 1 || node_data1 > 6) || (node_data2 < 1 || node_data2 > 6))
    {
        printf("-1\n");
        return;
    }
    if (weight == 0)
    {
        adjancyMatrix[node_data1][node_data2].isFilled = 0;
        adjancyMatrix[node_data2][node_data1].isFilled = 0;
        free(adjancyMatrix[node_data1][node_data2].edge);
        return;
    }
    if (adjancyMatrix[node_data1][node_data2].isFilled == 1)
    {
        adjancyMatrix[node_data1][node_data2].edge->weight = weight;
    }
    else if (adjancyMatrix[node_data1][node_data2].isFilled == 0)
    {
        createEdge(weight, nodeArray[node_data1], nodeArray[node_data2], adjancyMatrix, node_data1, node_data2);
    }
    return;
}

int main()
{
    AdjancyElement **adjacencyMatrix;
    Node *nodeArray[7] = {NULL};
    char input;
    int data, alpha, beta, weight;
    int node_number;
    int node_number2;

    adjacencyMatrix = (AdjancyElement **)malloc(sizeof(AdjancyElement *) * 7);

    for (int i = 0; i < 7; i++)
    {
        adjacencyMatrix[i] = (AdjancyElement *)malloc(sizeof(AdjancyElement) * 7);
        for (int j = 0; j < 7; j++)
        {
            adjacencyMatrix[i][j].isFilled = 0;
        }
    }
    nodeArray[1] = createNode(1);
    nodeArray[2] = createNode(2);
    nodeArray[3] = createNode(3);
    nodeArray[4] = createNode(4);
    nodeArray[5] = createNode(5);
    nodeArray[6] = createNode(6);

    createEdge(1, nodeArray[1], nodeArray[2], adjacencyMatrix, 1, 2);
    createEdge(2, nodeArray[1], nodeArray[6], adjacencyMatrix, 1, 6);
    createEdge(1, nodeArray[1], nodeArray[3], adjacencyMatrix, 1, 3);
    createEdge(1, nodeArray[1], nodeArray[4], adjacencyMatrix, 1, 4);
    createEdge(4, nodeArray[3], nodeArray[5], adjacencyMatrix, 3, 5);
    createEdge(3, nodeArray[5], nodeArray[6], adjacencyMatrix, 5, 6);
    createEdge(4, nodeArray[5], nodeArray[5], adjacencyMatrix, 5, 5);
    createEdge(1, nodeArray[2], nodeArray[3], adjacencyMatrix, 2, 3);

    while (1)
    {
        scanf(" %c", &input);
        if (input == 'a')
        {
            scanf("%d", &data);
            a(nodeArray, adjacencyMatrix, data);
        }
        else if (input == 'm')
        {
            scanf("%d %d %d", &alpha, &beta, &weight);
            m(nodeArray, adjacencyMatrix, alpha, beta, weight);
        }
        else if (input == 'q')
        {
            break;
        }
    }
    return 0;
}