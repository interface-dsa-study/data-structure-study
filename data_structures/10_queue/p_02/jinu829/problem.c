#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct ListNode
{
    int data;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

void add_front(ListNode **pf, ListNode **pr, int element)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = element;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (*pf == NULL)
    {
        *pf = new_node;
        *pr = new_node;
    }
    else
    {
        new_node->next = *pf;
        (*pf)->prev = new_node;
        *pf = new_node;
    }
}

void add_rear(ListNode **pf, ListNode **pr, int element)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = element;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (*pf == NULL)
    {
        *pf = new_node;
        *pr = new_node;
    }
    else
    {
        new_node->prev = *pr;
        (*pr)->next = new_node;
        *pr = new_node;
    }
}

void delete_front(ListNode **pf, ListNode **pr)
{
    if (*pf == NULL)
        printf("underflow");
    else
    {
        if ((*pf)->next == NULL)
        {
            // printf("1\n");
            *pf = NULL;
            *pr = NULL;
        }
        else
        {
            // printf("%d\n", (*pf)->next->data);
            *pf = (*pf)->next;
            (*pf)->prev = NULL;
        }
    }
}

void delete_rear(ListNode **pf, ListNode **pr)
{
    if (*pr == NULL)
        printf("underflow");
    else
    {
        if ((*pr)->prev == NULL)
        {
            *pf = NULL;
            *pr = NULL;
        }
        else
        {
            *pr = (*pr)->prev;
            (*pr)->next = NULL;
        }
    }
}

void print(ListNode **pf, ListNode **pr)
{
    ListNode *p = *pf;
    while (p != *pr)
    {
        printf(" %d", p->data);
        p = p->next;
    }
    printf(" %d\n", p->data);
}

int main()
{
    int n;
    int element;
    char str[3];

    ListNode *f = NULL;
    ListNode *r = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %s", str);
        // printf("%s", str);
        if (strcmp(str, "AF") == 0)
        {
            // printf("%s", str);
            scanf("%d", &element);
            // printf("%d", element);
            add_front(&f, &r, element);
            // printf("%d", f->data);
        }
        else if (strcmp(str, "AR") == 0)
        {
            scanf("%d", &element);
            add_rear(&f, &r, element);
        }
        else if (strcmp(str, "DF") == 0)
        {
            if (f == NULL)
            {
                delete_front(&f, &r);
                break;
            }
            else
                delete_front(&f, &r);
        }
        else if (strcmp(str, "DR") == 0)
        {
            if (r == NULL)
            {
                delete_rear(&f, &r);
                break;
            }
            else
                delete_rear(&f, &r);
        }
        else if (strcmp(str, "P") == 0)
        {
            // printf("1");
            print(&f, &r);
        }
    }

    return 0;
}