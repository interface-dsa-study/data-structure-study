#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
    struct TreeNode *parent;
    int key;
} TreeNode;

void insertItem(int key, TreeNode *node)
{ // 삽입할 위치를 받아서 그 위치에 새로운 노드 삽입
    TreeNode *new_node;
    new_node->key = key;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;
}

TreeNode *treeSearch(int key, TreeNode *root)
{
    if (root->rightChild == NULL && root->leftChild == NULL)
    { // 루트가 외부노드일 경우
        root->key = key;
    }
    else if (root->key < key)
    {
        if (root->leftChild == NULL)
            return root->leftChild;
        else
            return treeSearch(key, root->leftChild); // 내부노드고 작은 원소가 있다 -> 작은 원소인 부트리에 대해 find
    }
    else if (root->key > key)
    {
        if (root->rightChild == NULL)
            return root->rightChild;
        else
            return treeSearch(key, root->rightChild);
    }
    else // root->key == key
        return root;
}

int main()
{
    TreeNode *root = NULL;
    char input;
    while (1)
    {
        scanf(" %c", &input);
        if (input == 'i')
        {
        }
        else if (input == 'd')
        {
        }
        else if (input == 's')
        {
        }
        else if (input == 'p')
        {
        }
        else
            break;
    }

    return 0;
}