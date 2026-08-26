#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
    int key;
    int height;
} Node;

void create_external_node(Node *parent)
{
    Node *new_external_node = (Node *)malloc(sizeof(Node));
    new_external_node->parent = parent;
    new_external_node->leftChild = NULL;
    new_external_node->rightChild = NULL;
}

void create_internal_node(Node *parent, Node *leftChild, Node *rightChild, int key)
{
    Node *new_internal_node = (Node *)malloc(sizeof(Node));
    new_internal_node->parent = parent;
    new_internal_node->key = key;
    new_internal_node->leftChild = leftChild;
    new_internal_node->rightChild = rightChild;
}

int isExternal(Node *Node)
{
    if ((Node->leftChild == NULL) && (Node->rightChild == NULL))
        return 1;
    else
        return 0;
}

int isInternal(Node *Node)
{
    if (isExternal(Node) == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    int key;
    char input;

    while (1)
    {
        scanf(" %c", &input);
        if (input == 'i')
        {
            scanf("%d", &key);
        }
        else if (input == 's')
        {
        }
        else if (input == 'p')
        {
        }
        else if (input == 'q')
        {
            break;
        }
    }
    return 0;
}