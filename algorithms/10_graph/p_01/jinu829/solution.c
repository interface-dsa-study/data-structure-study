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
} Node;

typedef struct Edge
{
    struct Node *smallNode;
    struct Node *bigNode;
    int weight;
} Edge;

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    NodeToEdge *new_nodeToEdge = (NodeToEdge *)malloc(sizeof(NodeToEdge));
    new_nodeToEdge->next = NULL;
    new_nodeToEdge->edge = NULL;
    new_node->nodeToEdge = new_nodeToEdge;
    new_node->data = data;
    return new_node;
}

void createEdge(int weight, Node *node1, Node *node2)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    NodeToEdge *nodeToEdge1 = (NodeToEdge *)malloc(sizeof(NodeToEdge));
    NodeToEdge *nodeToEdge2 = (NodeToEdge *)malloc(sizeof(NodeToEdge));
    edge->weight = weight;
    edge->smallNode = node1;
    edge->bigNode = node2;
    if (node1 == node2)
    {
        free(nodeToEdge2);
        nodeToEdge1->next = node1->nodeToEdge->next;
        node1->nodeToEdge->next = nodeToEdge1;
        nodeToEdge1->edge = edge;
        return;
    }
    nodeToEdge1->next = node1->nodeToEdge->next;
    node1->nodeToEdge->next = nodeToEdge1;
    nodeToEdge2->next = node2->nodeToEdge->next;
    node2->nodeToEdge->next = nodeToEdge2;
    nodeToEdge1->edge = edge;
    nodeToEdge2->edge = edge;
    return;
}

void a(Node *node)
{
    int arr[6][2];
    int count = 0;
    int tmp;
    NodeToEdge *placeNode = node->nodeToEdge->next;
    while (placeNode != NULL)
    {
        if (node == placeNode->edge->bigNode)
        {
            arr[count][0] = placeNode->edge->smallNode->data;
            arr[count][1] = placeNode->edge->weight;
        }
        else if (node == placeNode->edge->smallNode)
        {
            arr[count][0] = placeNode->edge->bigNode->data;
            arr[count][1] = placeNode->edge->weight;
        }
        count++;
        placeNode = placeNode->next;
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j][0] > arr[j + 1][0])
            {
                tmp = arr[j][0];
                arr[j][0] = arr[j + 1][0];
                arr[j + 1][0] = tmp;
                tmp = arr[j][1];
                arr[j][1] = arr[j + 1][1];
                arr[j + 1][1] = tmp;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        printf(" %d %d", arr[i][0], arr[i][1]);
    }
    printf("\n");
}

void m(Node *node1, Node *node2, int weight)
{
    NodeToEdge *placeNode = node1->nodeToEdge->next;
    NodeToEdge *placeNode2 = node2->nodeToEdge->next;
    NodeToEdge *prev = node1->nodeToEdge;
    NodeToEdge *prev2 = node2->nodeToEdge;
    while (placeNode != NULL)
    {
        if (node1 == placeNode->edge->bigNode)
        {
            if (placeNode->edge->smallNode == node2)
            {
                if (weight == 0)
                {
                    prev->next = placeNode->next;
                    if (node1 != node2)
                    {
                        while (placeNode2->edge->bigNode != node1)
                        {
                            prev2 = placeNode2;
                            placeNode2 = placeNode2->next;
                        }
                        prev2->next = placeNode2->next;
                        free(placeNode2);
                    }

                    free(placeNode->edge);
                    free(placeNode);
                    return;
                }
                else
                {
                    placeNode->edge->weight = weight;
                    return;
                }
            }
        }
        else if (node1 == placeNode->edge->smallNode)
        {
            if (placeNode->edge->bigNode == node2)
            {
                if (weight == 0)
                {
                    prev->next = placeNode->next;
                    if (node1 != node2)
                    {
                        while (placeNode2->edge->smallNode != node1)
                        {
                            prev2 = placeNode2;
                            placeNode2 = placeNode2->next;
                        }
                        prev2->next = placeNode2->next;
                        free(placeNode2);
                    }

                    free(placeNode->edge);
                    free(placeNode);
                    return;
                }
                else
                {
                    placeNode->edge->weight = weight;
                    return;
                }
            }
        }
        prev = placeNode;
        placeNode = placeNode->next;
    }

    if (weight != 0)
        createEdge(weight, node1, node2);
    return;
}

int main()
{
    Node *nodeArray[7] = {NULL};
    char input;
    int node_number;
    int node_number2;
    int weight;

    nodeArray[1] = createNode(1);
    nodeArray[2] = createNode(2);
    nodeArray[3] = createNode(3);
    nodeArray[4] = createNode(4);
    nodeArray[5] = createNode(5);
    nodeArray[6] = createNode(6);

    createEdge(1, nodeArray[1], nodeArray[2]);
    createEdge(2, nodeArray[1], nodeArray[6]);
    createEdge(1, nodeArray[1], nodeArray[3]);
    createEdge(1, nodeArray[1], nodeArray[4]);
    createEdge(4, nodeArray[3], nodeArray[5]);
    createEdge(3, nodeArray[5], nodeArray[6]);
    createEdge(4, nodeArray[5], nodeArray[5]);
    createEdge(1, nodeArray[2], nodeArray[3]);

    while (1)
    {
        scanf(" %c", &input);
        if (input == 'a')
        {
            scanf("%d", &node_number);
            if ((node_number > 6) || (node_number < 1))
                printf("-1\n");
            else
                a(nodeArray[node_number]);
        }
        else if (input == 'm')
        {
            scanf("%d %d %d", &node_number, &node_number2, &weight);
            if (((node_number > 6) || (node_number < 1)) || ((node_number2 > 6) || (node_number2 < 1)))
                printf("-1\n");
            else
                m(nodeArray[node_number], nodeArray[node_number2], weight);
        }
        else if (input == 'q')
        {
            break;
        }
    }
    return 0;
}