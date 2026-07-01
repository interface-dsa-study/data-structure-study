#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef char element;
typedef int rank;
typedef struct ListNode
{
    element data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

void initialize(ListNode *head, ListNode *trailer)
{
    trailer->data = '~';
    head->next = trailer;
    trailer->prev = head;
    head->prev = NULL;
    trailer->next = NULL;
}

void add(ListNode *head, rank r, element e)
{
    ListNode *p = head;

    for (int i = 1; i < r; i++)
    { // 삽입할 위치의 바로 앞 노드까지만
        if (p->data == '~')
        {
            printf("invalid position\n");
            return;
        }
        p = p->next;
    }
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = e;
    // 사이에 끼워넣기
    new_node->next = p->next;   // new_node의 next를 원래 p의 next로
    (p->next)->prev = new_node; // 원래 p 다음에 있던 노드의 prev를 new node로
    p->next = new_node;
    new_node->prev = p;
}

void delete(ListNode *head, rank r)
{
    ListNode *p = head;

    for (int i = 1; i < r; i++)
    { // 삭제할 위치의 바로 앞 노드까지만
        p = p->next;
        if (p->data == '~')
        {
            printf("invalid position\n");
            return;
        }
    }

    if (p->next->data == '~')
    {
        printf("invalid position\n");
        return;
    }
    ListNode *remove = p->next;
    p->next = p->next->next;
    p->next->prev = p;

    free(remove);
}

element get(ListNode *head, rank r)
{
    ListNode *p = head;

    for (int i = 1; i < r; i++)
    { // 삭제할 위치의 바로 앞 노드까지만
        p = p->next;
        if (p->data == '~')
        {
            printf("invalid position");
            return ' ';
        }
    }

    if (p->next->data == '~')
    {
        printf("invalid position");
        return ' ';
    }

    return p->next->data;
}

void print(ListNode *head)
{
    ListNode *p = head->next;
    while (p->data != '~')
    {
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    ListNode *head = NULL;
    ListNode *trailer = NULL;
    head = (ListNode *)malloc(sizeof(ListNode));
    trailer = (ListNode *)malloc(sizeof(ListNode));
    int N;
    char choice;
    rank r;
    element e;

    initialize(head, trailer);

    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; i++)
    {
        scanf(" %c", &choice);
        if (choice == 'A')
        {
            scanf("%d %c", &r, &e);
            // printf("%c %d %c", choice, r, e);
            add(head, r, e);
        }
        else if (choice == 'D')
        {
            scanf("%d", &r);
            delete(head, r);
        }
        else if (choice == 'G')
        {
            scanf("%d", &r);
            // printf("%d", r);
            printf("%c\n", get(head, r));
        }
        else if (choice == 'P')
        {
            print(head);
        }
    }
    return 0;
}