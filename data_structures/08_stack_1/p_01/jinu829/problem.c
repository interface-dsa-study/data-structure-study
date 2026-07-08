#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pop(int *top)
{
    if (*top == -1)
    {
        printf("Stack Empty\n");
    }
    else
    {
        (*top)--;
    }
}

void push(char *stack, int *top, int N, char c)
{
    if (*top == N - 1)
    {
        printf("Stack FULL\n");
    }
    else
    {
        stack[++(*top)] = c;
    }
}

void peek(char *stack, int top)
{
    if (top == -1)
    {
        printf("Stack Empty\n");
    }
    else
    {
        printf("%c\n", stack[top]);
    }
}

void dup(char *stack, int *top, int N)
{
    if (*top == N - 1)
    {
        printf("Stack FULL\n");
    }
    else if (*top >= 0)
    {
        stack[*top + 1] = stack[*top];
        (*top)++;
    }
}

void upr(char *stack, int top, int n)
{
    if (n <= top + 1 && n > 1)
    {
        char temp = stack[top];
        for (int j = top; j > top - n + 1; j--)
        {
            stack[j] = stack[j - 1];
        }
        stack[top - n + 1] = temp;
    }
}

void downr(char *stack, int top, int n)
{
    if (n <= top + 1 && n > 1)
    {
        char temp = stack[top - n + 1];
        for (int j = top - n + 1; j < top; j++)
        {
            stack[j] = stack[j + 1];
        }
        stack[top] = temp;
    }
}

void print(char *stack, int top)
{
    for (int j = top; j >= 0; j--)
    {
        printf("%c", stack[j]);
    }
    printf("\n");
}

int main()
{
    int N, M;
    if (scanf("%d", &N) != 1)
        return 0;
    if (scanf("%d", &M) != 1)
        return 0;

    char *stack = (char *)malloc(sizeof(char) * N);
    int top = -1;

    for (int i = 0; i < M; i++)
    {
        char cmd[10];
        scanf("%s", cmd);

        if (strcmp(cmd, "POP") == 0)
        {
            pop(&top);
        }
        else if (strcmp(cmd, "PUSH") == 0)
        {
            char c;
            scanf(" %c", &c);
            push(stack, &top, N, c);
        }
        else if (strcmp(cmd, "PEEK") == 0)
        {
            peek(stack, top);
        }
        else if (strcmp(cmd, "DUP") == 0)
        {
            dup(stack, &top, N);
        }
        else if (strcmp(cmd, "UpR") == 0)
        {
            int n;
            scanf("%d", &n);
            upr(stack, top, n);
        }
        else if (strcmp(cmd, "DownR") == 0)
        {
            int n;
            scanf("%d", &n);
            downr(stack, top, n);
        }
        else if (strcmp(cmd, "PRINT") == 0)
        {
            print(stack, top);
        }
    }

    free(stack);
    return 0;
}