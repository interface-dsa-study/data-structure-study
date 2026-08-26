#include <stdio.h>
#include <stdlib.h>

typedef struct NodeToEdge
{
    struct Edge *edge;
    struct NodeToEdge *next;
} NodeToEdge;

typedef struct Node
{
    struct NodeToEdge *nodeToEdge;
    struct Node *next;
    int data;
    int isVisited;
} Node;

typedef struct Edge
{
    struct Node *smallNode;
    struct Node *bigNode;
    int isVisited;
} Edge;

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    NodeToEdge *new_nodeToEdge = (NodeToEdge *)malloc(sizeof(NodeToEdge));
    new_nodeToEdge->next = NULL;
    new_nodeToEdge->edge = NULL;
    new_node->nodeToEdge = new_nodeToEdge;
    new_node->data = data;
    new_node->isVisited = 0;
    return new_node;
}

void createEdge(Node *node1, Node *node2)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    NodeToEdge *new_nodeEdge = (NodeToEdge *)malloc(sizeof(NodeToEdge));
    NodeToEdge *new_nodeEdge2 = (NodeToEdge *)malloc(sizeof(NodeToEdge));
    NodeToEdge *placeNode = node1->nodeToEdge->next;
    NodeToEdge *placeNode2 = node2->nodeToEdge->next;
    NodeToEdge *prev = node1->nodeToEdge;
    Node *opposite;
    edge->smallNode = node1;
    edge->bigNode = node2;
    edge->isVisited = 0;
    new_nodeEdge->edge = edge;
    new_nodeEdge2->edge = edge;

    while (placeNode != NULL)
    {
        opposite = (placeNode->edge->bigNode == node1) ? placeNode->edge->smallNode : placeNode->edge->bigNode;
        if (opposite->data < node2->data)
        {
            prev = placeNode;
            placeNode = placeNode->next;
        }
        else
        {
            break;
        }
    }
    new_nodeEdge->next = prev->next;
    prev->next = new_nodeEdge;

    if (node1 != node2)
    {
        prev = node2->nodeToEdge;
        while (placeNode2 != NULL)
        {
            opposite = (placeNode2->edge->bigNode == node2) ? placeNode2->edge->smallNode : placeNode2->edge->bigNode;
            if (opposite->data < node1->data)
            {
                prev = placeNode2;
                placeNode2 = placeNode2->next;
            }
            else
            {
                break;
            }
        }
        new_nodeEdge2->next = prev->next;
        prev->next = new_nodeEdge2;
    }
}

void DFS(Node *node)
{
    NodeToEdge *placeNode = node->nodeToEdge->next;
    Node *oppositeNode;
    node->isVisited = 1;
    printf("%d\n", node->data);
    while (placeNode != NULL)
    {
        if (placeNode->edge->isVisited == 0)
        {
            oppositeNode = (placeNode->edge->bigNode == node) ? placeNode->edge->smallNode : placeNode->edge->bigNode;
            if (oppositeNode->isVisited == 0)
            {
                placeNode->edge->isVisited = 1;
                DFS(oppositeNode);
            }
        }
        placeNode = placeNode->next;
    }
}

int main()
{
    int n, m, s;
    int node1data, node2data;
    Node **nodeArray;
    scanf("%d %d %d", &n, &m, &s);
    nodeArray = (Node **)malloc(sizeof(Node *) * (n + 1));

    for (int i = 1; i < n + 1; i++)
    {
        nodeArray[i] = NULL;
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &node1data, &node2data);
        if (nodeArray[node1data] == NULL)
            nodeArray[node1data] = createNode(node1data);
        if (nodeArray[node2data] == NULL)
            nodeArray[node2data] = createNode(node2data);
        createEdge(nodeArray[node1data], nodeArray[node2data]);
    }

    DFS(nodeArray[s]);

    return 0;
}