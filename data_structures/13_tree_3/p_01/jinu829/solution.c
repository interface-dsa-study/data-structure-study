#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int id;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 새로운 노드 생성
TreeNode *createNode(int id)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->id = id;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 트리에서 특정 id를 가진 노드 찾기
TreeNode *searchNode(TreeNode *root, int id)
{
    if (root == NULL)
        return NULL;
    if (root->id == id)
        return root;

    TreeNode *found = searchNode(root->left, id);
    if (found != NULL)
        return found;

    return searchNode(root->right, id);
}

int main()
{
    int n;
    TreeNode *root = NULL;

    // 1. 트리 구성
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int id, left_id, right_id;
        scanf("%d %d %d", &id, &left_id, &right_id);

        if (i == 0)
        { // 첫 번째 입력은 무조건 루트 노드
            root = createNode(id);
            if (left_id != 0)
                root->left = createNode(left_id);
            if (right_id != 0)
                root->right = createNode(right_id);
        }
        else
        {
            // 이후 입력은 이미 트리 안에 존재하는 부모 노드를 찾아서 자식 연결
            TreeNode *parent = searchNode(root, id);
            if (parent != NULL)
            {
                if (left_id != 0)
                    parent->left = createNode(left_id);
                if (right_id != 0)
                    parent->right = createNode(right_id);
            }
        }
    }

    // 2. 트리 탐색
    int s;
    scanf("%d", &s);
    for (int i = 0; i < s; i++)
    {
        char path[105];
        scanf("%s", path);

        TreeNode *curr = root;
        printf(" %d", curr->id); // 맨 앞 공백(□) 출력

        // 탐색 문자열을 따라가며 방문하는 노드 출력
        for (int j = 0; path[j] != '\0'; j++)
        {
            if (path[j] == 'L')
            {
                curr = curr->left;
            }
            else if (path[j] == 'R')
            {
                curr = curr->right;
            }
            if (curr != NULL)
            {
                printf(" %d", curr->id);
            }
        }
        printf("\n");
    }

    return 0;
}