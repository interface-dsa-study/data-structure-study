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

int ismember(ListNode *set, int element)
{
    if (set == NULL)
        return 0;
    while (1)
    {
        if (set->data == element)
            return 1;
        else if (set->data > element)
            return 0;
        else if (set->data < element)
        {
            if (set->next == NULL)
                return 0;
            else
                set = set->next; // 이런 식으로 set.next를 시켜도 지역변수에만 적용되는 거겠지?
        }
    }
}

int subset(ListNode *set, ListNode *subset)
{
    int element;
    if (subset == NULL)
    {
        return 1;
    }
    while (1)
    {
        element = subset->data;
        if (ismember(set, element) == 1)
        {
            if (subset->next == NULL)
            {
                return 1; // 부분집합이다.
            }
            subset = subset->next; // 이런 식으로subset.next를 시켜도 지역변수에만 적용되는 거겠지?
        }
        else
            return 0;
    }
}

int main()
{
    int data;
    int size[2];
    ListNode **H = NULL;
    ListNode *new_node = NULL;
    ListNode *sset = NULL;
    int p;
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
    p = subset(H[1], H[0]); // H[0] - set, H[1] - subset
    sset = H[0]->next;
    if (p == 1)
        printf("0");
    else
    {
        while (1)
        {
            if (ismember(H[1], sset->data) == 0)
            {
                printf("%d", sset->data);
                break;
            }
            else
                sset = sset->next;
        }
    }
    return 0;
}