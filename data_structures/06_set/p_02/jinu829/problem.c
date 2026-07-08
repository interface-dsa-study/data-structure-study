#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct ListNode
{
    int data;
    struct ListNode *next;
} ListNode;

ListNode *insert_node(ListNode *head, ListNode *p, int data)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = data;
    new_node->next = p->next; // new_node의 next는 계속 0이 되도록
    p->next = new_node;
    return new_node;
}

ListNode *unionfunction(ListNode *A, ListNode *B)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (A == NULL && B == NULL)
    {
        return NULL;
    }

    if (A == NULL)
    {
        p->data = B->data;
        p->next = unionfunction(A, B->next);
    }
    else if (B == NULL)
    {
        p->data = A->data;
        p->next = unionfunction(A->next, B);
    }
    else
    {
        if (A->data > B->data)
        {
            p->data = B->data;
            p->next = unionfunction(A, B->next);
        }
        else if (A->data < B->data)
        {
            p->data = A->data;
            p->next = unionfunction(A->next, B);
        }
        else if (A->data == B->data)
        {
            p->data = A->data;
            p->next = unionfunction(A->next, B->next);
        }
    }
    return p;
}

ListNode *intersectfunction(ListNode *A, ListNode *B)
{
    if ((A == NULL) || (B == NULL))
    {
        return NULL;
    }
    if (A->data > B->data)
        return intersectfunction(A, B->next);
    else if (A->data < B->data)
        return intersectfunction(A->next, B);
    else if (A->data == B->data)
    {
        ListNode *p = (ListNode *)malloc(sizeof(ListNode));
        p->data = A->data;
        p->next = intersectfunction(A->next, B->next);
        return p;
    }
}

int main()
{
    int data;
    int size[2];
    ListNode **H = NULL;
    ListNode *new_node = NULL;
    ListNode *p = NULL;
    ListNode *q = (ListNode *)malloc(sizeof(ListNode));
    H = (ListNode **)malloc(sizeof(ListNode *));

    // 각 연결리스트 입력
    for (int i = 0; i < 2; i++)
    {
        H[i] = (ListNode *)malloc(sizeof(ListNode));
        H[i]->next = NULL;
        p = H[i]; // p의 초기 상태는 head로
        scanf("%d", &size[i]);
        for (int j = 0; j < size[i]; j++)
        {
            scanf("%d", &data);
            new_node = insert_node(H[i], p, data); // p = tail
            p = new_node;
            // printf("%d %d\n", p->data, i);
        }
    }

    // 합집합, 교집합 연산 시작
    p = unionfunction(H[0]->next, H[1]->next);
    if (H[0]->next == NULL && H[1]->next == NULL)
    {
        printf("0");
    }
    while (p != NULL)
    {
        printf(" %d", p->data);
        p = p->next;
    }
    printf("\n");
    q = intersectfunction(H[0]->next, H[1]->next);
    /*if (p == NULL) {
        printf("1");
    }*/
    // printf("%d", p->data);
    if (H[0]->next == NULL || H[1]->next == NULL)
    {
        printf("0\n");
    }
    while (q != NULL)
    {
        printf(" %d", q->data);
        q = q->next;
    }
    return 0;
}