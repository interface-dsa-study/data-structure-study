#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int data;
    struct ListNode *next;
} ListNode;

void createNode(ListNode **phead)
{
    int data;
    scanf("%d", &data);
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->data = data;
    if (*phead == NULL)
    {
        *phead = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = *phead;
        *phead = newNode;
    }
}

void merge(ListNode **phead, ListNode *start, ListNode *middle, ListNode *end, int k)
{
    ListNode *front = start;
    ListNode *behind = middle->next;
    while (front != middle->next && behind != end->next)
        if (front->data > behind->data)
        {
        }
}

void mergeSort(ListNode **phead, ListNode *start, ListNode *end, int size)
{
    int k = size / 2;
    if (k != 0)
    {
        ListNode *midNode = *phead;
        for (int i = 1; i < k; i++)
        {
            midNode = midNode->next;
        }
        mergeSort(phead, start, midNode, k);
        mergeSort(phead, midNode->next, end, size - k);
        merge(phead, start, midNode, end, k);
    }
}

int main()
{
    ListNode *head = NULL;
    ListNode *endNode = NULL;
    ListNode *startNode = NULL;
    ListNode *midNode = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        createNode(&head);
    }
    // printf("%d", head->data);
    endNode = head;
    startNode = head;
    // printf("%d", endNode->data);

    for (int i = 0; i < n - 1; i++)
    {
        endNode = endNode->next;
    }
    // printf("%d", endNode->data);

    mergeSort(&head, startNode, endNode, n);

    for (int i = 0; i < n; i++)
    {
        printf(" %d", startNode->data);
        startNode = startNode->next;
    }

    return 0;
}