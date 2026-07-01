#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct ListNode
{
    int coef;
    int exp;
    struct ListNode *next;
} ListNode;

ListNode *appendTerm(ListNode *p, int coef, int exp)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->coef = coef;
    new_node->exp = exp;

    new_node->next = NULL;
    p->next = new_node;
    p = new_node;
    return new_node;
}

ListNode *addPoly(ListNode *head1, ListNode *head2)
{
    int sum;
    ListNode *result = (ListNode *)malloc(sizeof(ListNode));
    ListNode *i = head1->next;
    ListNode *j = head2->next;

    result->next = NULL;

    ListNode *k = result;
    while ((i != NULL) && (j != NULL))
    {
        if (i->exp > j->exp)
        {
            k = appendTerm(k, i->coef, i->exp);
            i = i->next;
        }
        else if (i->exp < j->exp)
        {
            k = appendTerm(k, j->coef, j->exp);
            j = j->next;
        }
        else
        {
            sum = i->coef + j->coef;
            if (sum != 0)
                k = appendTerm(k, sum, i->exp);
            i = i->next;
            j = j->next;
        }
    }
    while (i != NULL)
    {
        k = appendTerm(k, i->coef, i->exp);
        i = i->next;
    }
    while (j != NULL)
    {
        k = appendTerm(k, j->coef, j->exp);
        j = j->next;
    }
    return result;
}

int main()
{
    int N;
    int hang;
    int coef, exp;

    ListNode **H; // ListNode*가 원소여야 될 것 같아서 이중 포인터로 선언.

    ListNode *new_node = NULL;
    ListNode *p = NULL;

    ListNode *result = NULL;
    H = (ListNode **)malloc(2 * sizeof(ListNode *));
    for (int i = 0; i < 2; i++)
    {
        H[i] = (ListNode *)malloc(sizeof(ListNode));
        ListNode *head = (ListNode *)malloc(sizeof(ListNode));
        H[i]->next = head;
        p = head;
        scanf("%d", &hang);
        for (int i = 0; i < hang; i++)
        {
            scanf("%d %d", &coef, &exp);

            new_node = appendTerm(p, coef, exp);
            p = new_node;
        }
    }
    result = addPoly(H[0], H[1]); // 함수 안에서 malloc해주기에 malloc따로 필요없음.
    result = result->next;        // head벗어나기
    while (result != NULL)
    {
        printf(" %d %d", result->coef, result->exp);
        result = result->next;
    }
    return 0;
}